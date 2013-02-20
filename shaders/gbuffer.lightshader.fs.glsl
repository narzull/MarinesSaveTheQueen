#version 330

// Uniforms : data shared by every shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 vertexColor;

//Texture
uniform bool hasUvs;
uniform bool hasTexture;
uniform bool hasNormalMap;
uniform bool hasSpecularMap;
uniform sampler2D textureUnitDiffuse;
uniform sampler2D normalUnitDiffuse;
uniform sampler2D specularUnitDiffuse;
   

// Varyings : data receved and interpolated from the vertex shaders
in vec3 position;
in vec3 normal;
in vec2 uvs;
in vec3 localColor;

// Final output
out vec4 Color;
out vec4 Normal;

void main()
{

  vec3 fDiffuse = localColor;
  float fSpec = 0;
  vec3 fNormal = normalize(normal);
  if(hasUvs){
	  if(hasTexture){
	    fDiffuse = texture2D(textureUnitDiffuse, uvs).rgb;
	  }
	  if(hasNormalMap){
	    //fNormal = vec3(0.01, 0.01, 0.01) * normalize(texture2D(normalUnitDiffuse, uvs).rgb * 2.0 - 1.0);
	  }
	  if(hasSpecularMap){
	    //fSpec = texture2D(specularUnitDiffuse, uvs).r;
	  }
  }
  Color = vec4(fDiffuse, fSpec);
  Normal = vec4(fNormal, fSpec);
}
