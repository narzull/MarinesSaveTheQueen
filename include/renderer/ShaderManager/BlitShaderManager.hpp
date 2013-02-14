#ifndef __BLITSHADERMANAGER_HPP__
#define __BLITSHADERMANAGER_HPP__

#include "BaseShaderManager.hpp"

namespace renderer{
	
//Shader to display a simple 2D textured board on screen
class BlitShaderManager : public BaseShaderManager{
public:
	BlitShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~BlitShaderManager(){};
	void setTextureInShader(GLuint textureID)const;
	
private:
	//Private Attribute
	//Texture
	GLint m_TextureDiffuseUniformLocation;
};
}

#endif //simpleshadermanager.hpp