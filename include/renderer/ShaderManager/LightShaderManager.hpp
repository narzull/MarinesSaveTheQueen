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
	glm::vec3 m_Color;
	float m_Power;
	//Constructor
	Light(glm::vec3 pos, glm::vec3 color, float power):m_Pos(pos), m_Color(color), m_Power(power){};
};
	
//Shader that handle lighting and texturing
class LightShaderManager : public SimpleShaderManager{
public:
	LightShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~LightShaderManager(){};
	//Setters
	void setEyeInShader(const glm::vec3 & eye)const;
	void setLightInShader(const Light & light)const;
	void setObjectTextureInShader(TexturedObject * object);
	
private:
	//Private Attribute
	//Eye
	GLint m_EyeUniformLocation;
	//Light
	GLint m_LightPosUniformLocation;
	GLint m_LightPowerUniformLocation;
	GLint m_LightColorUniformLocation;
	//Texture
	GLint m_HasUvsUniformLocation;
	GLint m_HasTextureUniformLocation;
	GLint m_HasNormalMapUniformLocation;
	GLint m_HasSpecularMapUniformLocation;
	GLint m_TextureDiffuseUniformLocation;
	GLint m_TextureNormalUniformLocation;
	GLint m_TextureSpecularUniformLocation;
};
}

#endif //simpleshadermanager.hpp