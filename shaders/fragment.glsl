#version 330 core
out vec3 color;

in vec3 FragPos;
in vec2 Uv;
in vec3 Normal;

uniform sampler2D texSampler;

uniform vec3 LightPos;

void main(){
    vec3 ambient = vec3(0.3, 0.3, 0.3);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    vec3 lightColor = vec3(1, 1, 1);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * texture( texSampler, Uv ).rgb;

    color = vec3(result);
}