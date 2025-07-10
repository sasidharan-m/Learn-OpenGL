#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

out vec3 LightingColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    vec3 Normal = aNormal;

    // ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos -  FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // calculate final lighting color
    LightingColor = ambient + diffuse + specular;

}
