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
    float shininess = 200;
    vec3 ambient = vec3(0.1, 0.1, 0.1);
    vec3 lightColor = vec3(1, 1, 1);

    vec3 norm = normalize(Normal);

    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(CameraPos - FragPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(1, 1, 1);

    color = vec3(result);
}