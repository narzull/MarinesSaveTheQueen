#version 330

// Uniforms : data shared by every shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Varyings : data receved and interpolated from the vertex shaders
smooth in vec4 localColor;

// Final output
out vec4 fragColor;

void main()
{
    fragColor = localColor;
}
