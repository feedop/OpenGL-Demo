#version 410 core

in vec2 TexCoords;

out vec4 FragColor;

struct Material {
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};

uniform Material material;

void main()
{
    FragColor = texture(material.diffuse0, TexCoords);
}