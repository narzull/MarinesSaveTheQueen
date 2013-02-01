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
   

// Varyings : data receved and interpolated from the vertex shaders
smooth in vec4 position;
smooth in vec4 normal;
smooth in vec2 uvs;
smooth in vec4 localColor;

// Final output
out vec4 fragColor;

void main()
{
	vec4 diffuseColorMix;
	vec4 localNormal = normal;
	if(hasUvs && hasTexture){
		diffuseColorMix = (1.0/light.power) * vec4(texture2D(textureUnitDiffuse, uvs).rgb, 1.0);
		if(hasNormalMap){
			localNormal += normalize(vec4(texture2D(normalUnitDiffuse, uvs).rgb * 2.0 - 1.0, 0.0));
		}
	}
	else{
		diffuseColorMix=mix(localColor, material.diffuse, 0.3);
	}
	vec4 L=normalize(light.position); // Direction of light from fragment -> light.position[3]==0.0 : Directional light
	if (light.position.w==1.0) L=normalize(light.position-position); //   -> light.position[3]==1.0 : Point light
	vec4 V=normalize(eye-position); // Direction from fragment to eye
	vec4 R=normalize(reflect(-L, localNormal)); // Direction of reflected light beam, from fragment
	vec4 N=normalize(localNormal); // Normal

	float ambientValue=light.power;
	float diffuseValue=light.power * max( dot(N, L), 0.0);
	float specularValue=light.power * pow(max(dot(R, V), 0.0), material.shininess);
	vec4 ambientContribution=vec4(ambientValue*material.ka*material.ambient.rgb, material.ambient.a);
	vec4 diffuseContribution=vec4(diffuseValue*material.kd*diffuseColorMix.rgb, diffuseColorMix.a);
	vec4 specularContribution=vec4(specularValue*material.ks*material.specular.rgb, material.specular.a);

	fragColor = ambientContribution + diffuseContribution + specularContribution;
}
