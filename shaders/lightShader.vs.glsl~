#version 330

struct Light
{
    vec4 position;
    float power;
};

struct Material
{
 vec4 ambient;
 vec4 diffuse;
 vec4 specular;
 float ka;
 float kd;
 float ks;
 float shininess;  
};

// Uniforms : data shared by every shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 eye;
uniform vec3 vertexColor;
uniform Light light;
uniform Material material;

//Texture
uniform bool hasUvs;
uniform bool hasTexture;
uniform bool hasNormalMap;
uniform sampler2D textureUnitDiffuse;
uniform sampler2D normalUnitDiffuse;

// Attributes : per vertex data
layout(location = 0)in vec4 vertexPosition;
layout(location = 1)in vec4 vertexNormal;
layout(location = 2)in vec2 vertexUvs;

// Varyings : data to transmit to fragments
smooth out vec4 position;
smooth out vec4 normal;
smooth out vec2 uvs;
smooth out vec4 localColor;

void main()
{
     position = model * vertexPosition;
     normal = model * vertexNormal;
	 if(hasUvs)uvs = vertexUvs;
     localColor = vec4(vertexColor, 1.0);

    gl_Position = projection * view * model * vertexPosition;
}
