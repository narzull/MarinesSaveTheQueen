#ifndef __LACCUMLIGHTSHADERMANAGER_HPP__
#define __LACCUMLIGHTSHADERMANAGER_HPP__

#include "BaseShaderManager.hpp"
#include "../FramebufferGL.hpp"
#include <glm/glm.hpp>

namespace renderer{
	
//Light struct
struct Light{
	glm::vec4 m_Pos;
	glm::vec3 m_Color;
	float m_Power;
	//Constructor
	Light(glm::vec4 pos, glm::vec3 color, float power):m_Pos(pos), m_Color(color), m_Power(power){};
};
	
//Shader that handle lighting and texturing
class LaccumLightShaderManager : public BaseShaderManager{
public:
	LaccumLightShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~LaccumLightShaderManager(){};
	//Setters
	void setEyeInShader(const glm::vec3 & eye)const;
	void setLightInShader(const Light & light)const;
	void setInvMatrixInShader(const glm::mat4 & inMatrix)const;
	void setTextureInShaderFromGBuffer(const FramebufferGL & gbuffer)const;
	
private:
	//Private Attribute
	//Eye
	GLint m_EyeUniformLocation;
	//Light
	GLint m_LightPosUniformLocation;
	GLint m_LightPowerUniformLocation;
	GLint m_LightColorUniformLocation;
	//Matrix
	GLint m_InverseMatrixUniformLocation;
	//Texture
	GLint m_TextureDiffuseUniformLocation;
	GLint m_TextureNormalUniformLocation;
	GLint m_TextureDepthUniformLocation;
};
}

#endif //simpleshadermanager.hpp