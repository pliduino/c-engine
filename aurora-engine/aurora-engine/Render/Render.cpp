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
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <aurora-engine/Objects/Scene.h>
#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/BaseComponents/ModelRenderer.h>
#include <aurora-engine/BaseComponents/Transform.h>
#include <aurora-engine/Reading/BmpLoader.h>
#include <aurora-engine/Reading/ObjReader.h>
#include <aurora-engine/BaseGameObjects/Camera.h>

static inline glm::mat4 CalcMVP(const CTransform *transform);
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
    Render *render = (Render *)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Position.x -= 0.3;
    }

    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Position.x += 0.3;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Position.y += 0.3;
    }

    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Position.y -= 0.3;
    }

    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Position.z += 0.3;
    }

    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Position.z -= 0.3;
    }

    const float rotSpeed = 0.1;

    if (key == GLFW_KEY_Q && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(0, -rotSpeed, 0);
    }

    if (key == GLFW_KEY_E && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(0, +rotSpeed, 0);
    }

    if (key == GLFW_KEY_F && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(-rotSpeed, 0, 0);
    }

    if (key == GLFW_KEY_R && action == GLFW_REPEAT)
    {
        render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(+rotSpeed, 0, 0);
    }
}

static void error_callback(int error, const char *description)
{
    std::cerr << "Error: " << description;
}

void Render::render(Scene *scn)
{
    this->scene = scn;
    CTransform *transformToMove = scn->mainCamera->Transform;

    Init();

    glfwSetWindowUserPointer(window, this);

    GenBuffers();

    // Textures
    BmpLoader loader;
    loader.LoadFile("textures/w.bmp");

    int width, height, channels;
    unsigned char *img = stbi_load("textures/w.bmp", &width, &height, &channels, 0);

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    // Texture filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Ties to monitor refresh rate
    glfwSwapInterval(1);

    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
    while (!glfwWindowShouldClose(window))
    {
        auto lastNow = std::chrono::high_resolution_clock::now();

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        // Draw(scene->mainCamera, scene->objects[0]->GetComponent<Transform>());
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGUI(transformToMove);

        Draw(scene->mainCamera, scene->mainCamera->Transform);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        scene->Update();

        glfwPollEvents();
        mspf = ((std::chrono::duration<double, std::milli>)(std::chrono::high_resolution_clock::now() - lastNow)).count();
        glfwSwapBuffers(window);
        fps = (1000 / ((std::chrono::duration<double, std::milli>)(std::chrono::high_resolution_clock::now() - lastNow)).count());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return;
}

static inline glm::mat4 CalcMVP(const CTransform *transform)
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z));
    glm::mat4 rotate = glm::toMat4(glm::quat(transform->Rotation.w, transform->Rotation.x, transform->Rotation.y, transform->Rotation.z));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(transform->Scale.x, transform->Scale.y, transform->Scale.z));

    return translate * scale * rotate;
}

static inline GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
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
        printf("Could not open %s.\n", vertex_file_path);
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
    glGenBuffers(1, &vbo);
    glGenFramebuffers(1, &depthMapFBO);
}

inline void Render::Draw(GCamera *camera, CTransform *transform)
{
    glm::vec3 lookVector = glm::rotate(glm::quat(transform->Rotation.w, transform->Rotation.x, transform->Rotation.y, transform->Rotation.z),
                                       glm::vec3(0, 0, 1)) +
                           glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z);

    glm::mat4 view = glm::lookAt(
        glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z),
        lookVector,
        glm::vec3(0, 1, 0));

    glm::mat4 projection = glm::perspective(camera->Fov, 4.0f / 3.0f, camera->Near, camera->Far);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (auto &object : scene->objects)
    {
        CModelRenderer *modelRenderer = object->GetComponent<CModelRenderer>();
        if (modelRenderer == NULL)
        {
            continue;
        }
        RenderObject(modelRenderer, view, projection);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
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
    window = glfwCreateWindow(1280, 720, "Aura", NULL, NULL);
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

    // Initializing IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Depth culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

inline void Render::ImGUI(CTransform *&transformToMove)
{
    static int tab = 0;
    ImGui::Begin("Scene");

    ImGui::SameLine();
    if (ImGui::Button("Scene"))
    {
        tab = 0;
    }
    ImGui::SameLine();
    if (ImGui::Button("Debug"))
    {
        tab = 1;
    }

    // Scene
    if (tab == 0)
    {
        for (int i = 0; i < scene->objects.size(); i++)
        {
            if (ImGui::Button(scene->objects[i]->Name.c_str()))
            {
                auto newTransform = scene->objects[i]->GetComponent<CTransform>();
                if (newTransform != NULL)
                {
                    transformToMove = newTransform;
                }
                else
                {
                    std::cout << "This object has no transform" << std::endl;
                }
            }
            for (auto component : scene->objects[i]->GetComponents())
            {
                ImGui::Text("  - %s", component->GetName().c_str());
            }
        }
    }

    // Debug
    if (tab == 1)
    {
        if (showFps)
        {
            ImGui::Text("FPS: %.2f", fps);
        }
        ImGui::Text("Ms: %.2f", mspf);
    }

    ImGui::End();
}

inline void Render::RenderObject(CModelRenderer *modelRenderer, glm::mat4 view, glm::mat4 projection)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, modelRenderer->Model->vertexData.size() * sizeof(float), &modelRenderer->Model->vertexData[0], GL_STATIC_DRAW);

    glm::mat4 model = CalcMVP(modelRenderer->Transform);

    // Using Shader
    unsigned int programId;
    if (!modelRenderer->Material->IsLoaded)
    {
        programId = LoadShaders(modelRenderer->Material->VertexShader.c_str(), modelRenderer->Material->FragmentShader.c_str());
        modelRenderer->Material->IsLoaded = true;
        modelRenderer->Material->Id = programId;
    }
    else
    {
        programId = modelRenderer->Material->Id;
    }

    glUseProgram(programId);
    GLuint MatrixModelID = glGetUniformLocation(programId, "model");
    glUniformMatrix4fv(MatrixModelID, 1, GL_FALSE, &model[0][0]);
    GLuint MatrixViewID = glGetUniformLocation(programId, "view");
    glUniformMatrix4fv(MatrixViewID, 1, GL_FALSE, &view[0][0]);
    GLuint MatrixProjectionID = glGetUniformLocation(programId, "projection");
    glUniformMatrix4fv(MatrixProjectionID, 1, GL_FALSE, &projection[0][0]);

    GLuint LightPosID = glGetUniformLocation(programId, "LightPos");
    TVector3 light = scene->objects[0]->GetComponent<CTransform>()->Position;
    glm::vec3 pos = glm::vec3(light.x, light.y, light.z);
    glUniform3fv(LightPosID, 1, &pos[0]);

    GLuint CameraPosID = glGetUniformLocation(programId, "CameraPos");
    TVector3 cameraPosition = scene->mainCamera->Transform->Position;
    glm::vec3 cameraPos = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3fv(CameraPosID, 1, &cameraPos[0]);

    // Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    // UVs
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void *)(3 * sizeof(GL_FLOAT)));
    // Normals
    glVertexAttribPointer(
        2,                             // attribute
        3,                             // size
        GL_FLOAT,                      // type
        GL_TRUE,                       // normalized?
        8 * sizeof(float),             // stride
        (void *)(0 * sizeof(GL_FLOAT)) // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, modelRenderer->Model->vertexData.size() / 8);
}