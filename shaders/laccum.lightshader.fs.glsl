#version 330
struct Light
{
    vec4 position;
    vec3 color;
    float power;
};

// Uniforms : data shared by every shader
uniform vec3 eye;
uniform Light light;
uniform mat4 inverseViewProjection;

//Texture
uniform sampler2D textureDiffuse;
uniform sampler2D textureNormal;
uniform sampler2D textureDepth;
   
// Varyings : data receved and interpolated from the vertex shaders
in vec2 uvs;

// Final output
out vec4 Color;

vec3 computePointLightLighting(in vec3 lPosition, in vec3 lColor, in float lIntensity, in float kAttenuation, in vec3 fPosition, in vec3 fDiffuse, in vec3 fNormal, in float fSpec){
	vec3 l = lPosition - fPosition;
	vec3 v = fPosition - eye;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(fNormal, l), 0, 1.0);
	float n_dot_h = clamp(dot(fNormal, h), 0, 1.0);
	
	float d = distance(l, fPosition);
	float attenuation = clamp(1.0/(1.00 + kAttenuation * d * d), 0.0, 1.0);
	
	return attenuation * lColor * lIntensity * (fDiffuse * n_dot_l + fSpec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, fSpec * 100.0));	
	//return vec3(n_dot_l, n_dot_l, n_dot_l);
	//return vec3(d,d,d);
	
}

vec3 computeDirectionnalLightLighting(in vec3 lPosition, in vec3 lColor, in float lIntensity, in float kAttenuation, in vec3 fPosition, in vec3 fDiffuse, in vec3 fNormal, in float fSpec){
	vec3 l =  normalize(-lPosition);
	vec3 v = fPosition - eye;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(fNormal, l), 0, 1.0);
	float n_dot_h = clamp(dot(fNormal, h), 0, 1.0);

	return lColor * lIntensity * (fDiffuse * n_dot_l + fSpec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, fSpec * 100.0));
	//return fPosition;
}

void main()
{

  vec4  material = texture(textureDiffuse, uvs).rgba;
  vec3  normal = texture(textureNormal, uvs).rgb;
  float depth = texture(textureDepth, uvs).r;
  
  vec2  xy = uvs * 2.0 -1.0;
  vec4  wPosition =  inverseViewProjection * vec4(xy, depth * 2.0 -1.0, 1.0);
  vec3  position = vec3(wPosition/wPosition.w)/2.0;
  
  vec3 fDiffuse = material.rgb;
  float fSpec = material.a;
  vec3 fNormal = normalize(normal);
  
  if(light.position.w == 1.0){
    Color = vec4(computePointLightLighting(light.position.xyz, light.color, light.power, 2.0, position, fDiffuse, fNormal, fSpec), 1.0);
  }
  else{
    Color = vec4(computeDirectionnalLightLighting(light.position.xyz, light.color, light.power, 0.5, position, fDiffuse, fNormal, fSpec), 1.0);
  }
  //Color = vec4(eye,1.0);
}
