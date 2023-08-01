#include "Render.h"
#define NDEBUG 1
#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"

#include "Camera.h"
#include "Scene.h"
#include "GameObject.h"
#include "ModelRenderer.h"
#include "Transform.h"
#include "BmpLoader.h"

static const inline glm::mat4 CalcMVP(const Transform *transform);

static GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

Render::Render(/* args */)
{
}

Render::~Render()
{
}

Render *Render::ShowFps()
{
    this->showFps = true;
    return this;
}

Render *Render::HideFps()
{
    this->showFps = false;
    return this;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Scene *scene = (Scene *)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
    {
        scene->mainCamera->transform->position.x -= 0.3;
    }

    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
    {
        scene->mainCamera->transform->position.x += 0.3;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT)
    {
        scene->mainCamera->transform->position.y += 0.3;
    }

    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_REPEAT)
    {
        scene->mainCamera->transform->position.y -= 0.3;
    }

    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
    {
        scene->mainCamera->transform->position.z += 0.3;
    }

    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
    {
        scene->mainCamera->transform->position.z -= 0.3;
    }
}

static void error_callback(int error, const char *description)
{
    std::cerr << "Error: " << description;
}

void Render::render(Scene *scene)
{
    Init();

    glfwSetWindowUserPointer(window, scene);

    GenBuffers();

    // Textures
    BmpLoader loader;
    loader.LoadFile("textures/w.bmp");

    int width, height, channels;
    unsigned char *img = stbi_load("textures/w.bmp", &width, &height, &channels, 0);

    // Texture filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Ties to monitor refresh rate
    glfwSwapInterval(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8, (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8, (void *)3);
    glVertexAttribPointer(
        2,        // attribute
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        8,        // stride
        (void *)6 // array buffer offset
    );

    while (!glfwWindowShouldClose(window))
    {
        auto lastNow = std::chrono::high_resolution_clock::now();

        glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto camera = scene->mainCamera;

        glm::mat4 view = glm::lookAt(
            glm::vec3(camera->transform->position.x, camera->transform->position.y, camera->transform->position.z), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0),                                                                                     // and looks at the origin
            glm::vec3(0, 1, 0));

        glm::mat4 projection = glm::perspective(camera->fov, 4.0f / 3.0f, camera->near, camera->far);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        for (auto &object : scene->objects)
        {
            ModelRenderer *modelRenderer = object->GetComponent<ModelRenderer>();
            if (modelRenderer == NULL)
            {
                continue;
            }
            RenderObject(modelRenderer, view, projection);
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glfwSwapBuffers(window);

        scene->Update();
        glfwPollEvents();

        if (showFps)
        {
            std::cout << "FPS: " << 1000 / ((std::chrono::duration<double, std::milli>)(std::chrono::high_resolution_clock::now() - lastNow)).count() << "\n";
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return;
}

static const inline glm::mat4 CalcMVP(const Transform *transform)
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(transform->position.x, transform->position.y, transform->position.z));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(transform->scale.x, transform->scale.y, transform->scale.z));

    return translate * scale * rotate;
}

static GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

inline void Render::GenBuffers()
{
    glGenBuffers(1, &vertex_buffer);
}

inline void Render::Init()
{
    // Initializing GLFW
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        std::cerr << "GLFW init error";
        return;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // MSAA Anti Aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initializing Window
    window = glfwCreateWindow(640, 480, "Title", NULL, NULL);
    if (!window)
    {
        std::cerr << "Window creation error";
        glfwTerminate();
        return;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    // Initializing GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW";
        return;
    }

    // Depth culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Render::RenderObject(ModelRenderer *modelRenderer, glm::mat4 view, glm::mat4 projection)
{
    // glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    // glBufferData(GL_ARRAY_BUFFER, modelRenderer->normalData.size() * sizeof(float), &modelRenderer->normalData[0], GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    // glBufferData(GL_ARRAY_BUFFER, modelRenderer->textureData.size() * sizeof(float), &modelRenderer->textureData[0], GL_STATIC_DRAW);
    // Vertex should always go last for glDrawArrays
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, modelRenderer->vertexData.size() * sizeof(float), &modelRenderer->vertexData[0], GL_STATIC_DRAW);

    glm::mat4 model = CalcMVP(modelRenderer->transform);

    // Using Shader
    unsigned int programId;
    auto iterId = programIds.find(modelRenderer->fragShader);
    if (iterId == programIds.end())
    {
        programId = LoadShaders(modelRenderer->shader.c_str(), modelRenderer->fragShader.c_str());
        programIds[modelRenderer->fragShader] = programId;
    }
    else
    {
        programId = iterId->second;
    }

    glUseProgram(programId);
    GLuint MatrixModelID = glGetUniformLocation(programId, "model");
    glUniformMatrix4fv(MatrixModelID, 1, GL_FALSE, &model[0][0]);
    GLuint MatrixViewID = glGetUniformLocation(programId, "view");
    glUniformMatrix4fv(MatrixViewID, 1, GL_FALSE, &view[0][0]);
    GLuint MatrixProjectionID = glGetUniformLocation(programId, "projection");
    glUniformMatrix4fv(MatrixProjectionID, 1, GL_FALSE, &projection[0][0]);
    GLuint MatrixLightPosID = glGetUniformLocation(programId, "LightPos");
    glm::vec3 pos = glm::vec3(0.0, 2.0, 0.0);
    glUniform3fv(MatrixLightPosID, 1, &pos[0]);

    glDrawArrays(GL_TRIANGLES, 0, modelRenderer->vertexData.size() / 3);
}