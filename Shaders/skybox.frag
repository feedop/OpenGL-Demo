#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

struct Fog {
    vec3 color;
    float density;
};

uniform Fog fog;

void main()
{    
    FragColor = vec4(mix(texture(skybox, TexCoords).rgb, fog.color, fog.density), 1.0);
}