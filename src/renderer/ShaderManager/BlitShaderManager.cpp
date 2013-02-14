#include "renderer/ShaderManager/BlitShaderManager.hpp"

#include <stdexcept>

namespace renderer{
//Constructor
BlitShaderManager::BlitShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile):BaseShaderManager(vertexShaderFile, fragmentShaderFile){
    m_TextureDiffuseUniformLocation = glGetUniformLocation(m_ShaderProgram, "diffuseTexture");
    if(m_TextureDiffuseUniformLocation < 0) throw std::runtime_error("No uniform variable called diffuseTexture in the shader");
}
	
void BlitShaderManager::setTextureInShader(GLuint textureID)const{
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(m_TextureDiffuseUniformLocation, 0);
  glBindTexture(GL_TEXTURE_2D, textureID);
}
}
