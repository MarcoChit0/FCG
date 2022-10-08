#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
// FONTE https://learnopengl.com/Advanced-OpenGL/Cubemaps

void main()
{    
    FragColor = texture(skybox, TexCoords);
}