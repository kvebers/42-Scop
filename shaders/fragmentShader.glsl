#version 330 core

uniform sampler2D textureSampler; // Uniform to hold the texture sampler

// Input from the vertex shader
in vec2 TexCoord;

// Output color to the framebuffer
out vec4 FragColor;

void main() 
{
    // Sample the texture at the interpolated texture coordinates and output the color
    FragColor = texture(textureSampler, TexCoord);
}