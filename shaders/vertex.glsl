#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUv;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec2 Uv;
out vec3 Normal;

void main(){
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);

    FragPos = vec3(model * vec4(vertexPosition, 1.0));
    Uv = vertexUv;
    Normal = vertexNormal;
}