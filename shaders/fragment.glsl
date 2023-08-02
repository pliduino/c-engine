#version 330 core
out vec3 color;

in vec3 FragPos;
in vec2 Uv;
in vec3 Normal;

uniform sampler2D texSampler;

uniform vec3 LightPos;
uniform vec3 CameraPos;

void main(){
    float specularStrength = 0.5;
    vec3 ambient = vec3(0.1, 0.1, 0.1);
    vec3 lightColor = vec3(1, 1, 1);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 lightDir = normalize(LightPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse + specular) * texture( texSampler, Uv ).rgb;

    color = vec3(result);
}