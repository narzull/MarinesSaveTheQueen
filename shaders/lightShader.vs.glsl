#version 330

struct Light
{
    vec4 position;
    vec3 color;
    float power;
};

// Uniforms : data shared by every shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 eye;
uniform vec3 vertexColor;
uniform Light light;

//Texture
uniform bool hasUvs;
uniform bool hasTexture;
uniform bool hasNormalMap;
uniform bool hasSpecularMap;
uniform sampler2D textureUnitDiffuse;
uniform sampler2D normalUnitDiffuse;
uniform sampler2D specularUnitDiffuse;

// Attributes : per vertex data
layout(location = 0)in vec4 vertexPosition;
layout(location = 1)in vec4 vertexNormal;
layout(location = 2)in vec2 vertexUvs;

// Varyings : data to transmit to fragments
out vec3 position;
out vec3 normal;
out vec2 uvs;
out vec3 localColor;

void main()
{
     position = vec3(model * vertexPosition);
     normal = vec3(model * vertexNormal);
     uvs = vertexUvs;
     localColor = vertexColor;

    gl_Position = projection * view * model * vertexPosition;
}
