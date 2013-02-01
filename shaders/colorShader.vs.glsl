#version 330

// Uniforms : data shared by every shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 vertexColor;

// Attributes : per vertex data
in vec4 vertexPosition;

// Varyings : data to transmit to fragments
smooth out vec4 localColor;

void main()
{
    localColor = vec4(vertexColor, 1.0f);
    gl_Position = projection * view * model * vertexPosition;
}

