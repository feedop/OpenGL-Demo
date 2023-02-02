#version 410 core
out vec4 FragColor;

in vec4 LightingColor; 
in vec2 TexCoords;

struct Material {
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};

uniform Material material;

void main()
{
   FragColor = LightingColor * texture(material.diffuse0, TexCoords);
}