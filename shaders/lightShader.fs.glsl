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
   

// Varyings : data receved and interpolated from the vertex shaders
in vec3 position;
in vec3 normal;
in vec2 uvs;
in vec3 localColor;

// Final output
out vec4 fragColor;

vec3 computePointLightLighting(in vec3 lPosition, in vec3 lColor, in float lIntensity, in float kAttenuation, vec3 fDiffuse, vec3 fNormal, float fSpec){
	vec3 l = lPosition - position;
	vec3 v = position - eye;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(fNormal, l), 0, 1.0);
	float n_dot_h = clamp(dot(fNormal, h), 0, 1.0);
	
	float d = distance(l, position);
	float attenuation = clamp(1.0/(1.00 + kAttenuation * d * d), 0.0, 1.0);
	
	return attenuation * lColor * lIntensity * (fDiffuse * n_dot_l + fSpec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, fSpec * 100.0));	
}

vec3 computeDirectionnalLightLighting(in vec3 lPosition, in vec3 lColor, in float lIntensity, in float kAttenuation, vec3 fDiffuse, vec3 fNormal, float fSpec){
	vec3 l =  normalize(-lPosition);
	vec3 v = position - eye;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(fNormal, l), 0, 1.0);
	float n_dot_h = clamp(dot(fNormal, h), 0, 1.0);

	return lColor * lIntensity * (fDiffuse * n_dot_l + fSpec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, fSpec * 100.0));
}

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
	    //fNormal = vec3(0.2, 0.2, 0.2) * normalize(texture2D(normalUnitDiffuse, uvs).rgb * 2.0 - 1.0);
	  }
	  if(hasSpecularMap){
	    //fSpec = texture2D(specularUnitDiffuse, uvs).r;
	  }
  }

  //fragColor = vec4(computePointLightLighting(light.position.xyz, light.color, light.power, 0.2, fDiffuse, fNormal, fSpec), 1.0);
  fragColor = vec4(computeDirectionnalLightLighting(light.position.xyz, light.color, light.power, 0.5, fDiffuse, fNormal, fSpec), 1.0);
}
