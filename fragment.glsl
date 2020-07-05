#version 450 core

out vec4 fragColor;  

in vec3 ourColor;
in vec3 fragPos;
in vec3 normal;

uniform vec3 lightColor;
uniform vec3 lightPos;
  
void main()
{
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambient + diffuse) * ourColor;
    fragColor = vec4(result, 1.0);
}