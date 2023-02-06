#version 410 core
out vec4 FragColor;

in vec4 LightingColor; 
in vec2 TexCoords;
in vec3 FragPos;

struct Material {
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};

struct Fog {
    vec3 color;
    float density;
};

uniform Material material;

uniform Fog fog;
uniform vec3 viewPos;


void main()
{
    float factor = length(viewPos - FragPos) / 1000 * fog.density;
    float alpha = 1 / exp(factor * factor);
    vec4 color = LightingColor * texture(material.diffuse0, TexCoords);
    FragColor = vec4(mix(fog.color, color.rgb, alpha), 1.0);
}