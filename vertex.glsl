#version 450 core
layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
  
out vec3 fragPos;
out vec3 normal;
out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragPos = vec3(model * vec4(aPos, 1.0));
    normal = aNormal;
    color = aColor;
    gl_Position = projection * view * vec4(fragPos, 1.0);
}       