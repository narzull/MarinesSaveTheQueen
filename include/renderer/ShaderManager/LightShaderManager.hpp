#ifndef __LIGHTSHADERMANAGER_HPP__
#define __LIGHTSHADERMANAGER_HPP__

#include "SimpleShaderManager.hpp"
#include "../Color.hpp"
#include "../TexturedObject.hpp"
#include <glm/glm.hpp>

namespace renderer{
	
//Light struct
struct Light{
	glm::vec3 m_Pos;
	float m_Power;
	//Constructor
	Light(glm::vec3 pos, float power):m_Pos(pos), m_Power(power){};
};

//Material struct
struct Material{
	Color m_Ambiant;
	Color m_Diffuse;
	Color m_Specular;
	float m_Ka;
	float m_Kd;
	float m_Ks;
	float m_Shininess;
	//Constructor
	Material(Color ambiant, Color diffuse, Color specular, float ka, float kd, float ks, float shininess):m_Ambiant(ambiant), m_Diffuse(diffuse), m_Specular(specular), m_Ka(ka), m_Kd(kd), m_Ks(ks), m_Shininess(shininess){};
};
	
//Shader that handle lighting and texturing
class LightShaderManager : public SimpleShaderManager{
public:
	LightShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~LightShaderManager(){};
	//Setters
	void setEyeInShader(const glm::vec3 & eye)const;
	void setLightInShader(const Light & light)const;
	void setMaterialInShader(const Material & material)const;
	void setObjectTextureInShader(TexturedObject * object);
	
private:
	//Private Attribute
	//Eye
	GLint m_EyeUniformLocation;
	//Light
	GLint m_LightPosUniformLocation;
	GLint m_LightPowerUniformLocation;
	//Material
	GLint m_MaterialAmbiantUniformLocation;
	GLint m_MaterialDiffuseUniformLocation;
	GLint m_MaterialSpecularUniformLocation;
	GLint m_MaterialKAUniformLocation;
	GLint m_MaterialKDUniformLocation;
	GLint m_MaterialKSUniformLocation;
	GLint m_MaterialShininessUniformLocation;
	//Texture
	GLint m_HasUvsUniformLocation;
	GLint m_HasTextureUniformLocation;
	GLint m_HasNormalMapUniformLocation;
	GLint m_TextureDiffuseUniformLocation;
	GLint m_TextureNormalUniformLocation;
};
}

#endif //simpleshadermanager.hpp