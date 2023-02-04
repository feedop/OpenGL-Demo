#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 u_model;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * u_model * vec4(aPos, 1.0);
    Normal = mat3(transpose(inverse(u_model))) * aNormal;
    FragPos = vec3(u_model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
     
} 