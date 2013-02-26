#ifndef __GBUFFERLIGHTSHADERMANAGER_HPP__
#define __GBUFFERLIGHTSHADERMANAGER_HPP__

#include "SimpleShaderManager.hpp"
#include "../Color.hpp"
#include "../TexturedObject.hpp"
#include <glm/glm.hpp>

namespace renderer{
	
//Shader that handle lighting and texturing
class GBufferLightShaderManager : public SimpleShaderManager{
public:
	GBufferLightShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~GBufferLightShaderManager(){};
	//Setters
	void setObjectTextureInShader(const TexturedObject * object);
	
private:
	//Private Attribute
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