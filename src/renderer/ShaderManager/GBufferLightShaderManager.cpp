#include "renderer/ShaderManager/GBufferLightShaderManager.hpp"
#include "api/Tools.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

namespace renderer{
//Constructor
GBufferLightShaderManager::GBufferLightShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile):SimpleShaderManager(vertexShaderFile, fragmentShaderFile){
    //Texture
    m_HasUvsUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasUvs");
    if(m_HasUvsUniformLocation < 0) throw std::runtime_error("No uniform variable called hasUvs in the shader");
    
    m_HasTextureUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasTexture");
    if(m_HasTextureUniformLocation < 0) throw std::runtime_error("No uniform variable called hasTexture in the shader");
	
    m_HasNormalMapUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasNormalMap");
    //if(m_HasNormalMapUniformLocation < 0) throw std::runtime_error("No uniform variable called hasNormalMap in the shader");
    
    m_HasSpecularMapUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasSpecularMap");
    //if(m_HasSpecularMapUniformLocation < 0) throw std::runtime_error("No uniform variable called hasSpecularMap in the shader");
    
    m_TextureDiffuseUniformLocation = glGetUniformLocation(m_ShaderProgram, "textureUnitDiffuse");
    if(m_TextureDiffuseUniformLocation < 0) throw std::runtime_error("No uniform variable called textureUnitDiffuse in the shader");
	    
    m_TextureNormalUniformLocation = glGetUniformLocation(m_ShaderProgram, "normalUnitDiffuse");
    //if(m_TextureNormalUniformLocation < 0) throw std::runtime_error("No uniform variable called normalUnitDiffuse in the shader");
    
    m_TextureSpecularUniformLocation = glGetUniformLocation(m_ShaderProgram, "specularUnitDiffuse");
    //if(m_TextureSpecularUniformLocation < 0) throw std::runtime_error("No uniform variable called specularUnitDiffuse in the shader");
}
	
void GBufferLightShaderManager::setObjectTextureInShader(TexturedObject * object){
	glUniform1i(m_HasUvsUniformLocation, object->hasUvs());
	glUniform1i(m_HasTextureUniformLocation, object->hasTexture());
	glUniform1i(m_HasNormalMapUniformLocation, object->hasNormalMap());
	glUniform1i(m_HasSpecularMapUniformLocation, object->hasSpecularMap());
	if(object->hasUvs() && object->hasTexture()){
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_TextureDiffuseUniformLocation, 0);
		glBindTexture(GL_TEXTURE_2D, object->getTextureID());
	}
	if(object->hasUvs() && object->hasNormalMap()){
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(m_TextureNormalUniformLocation, 1);
		glBindTexture(GL_TEXTURE_2D, object->getNormalMapID());
	}
	if(object->hasUvs() && object->hasSpecularMap()){
		glActiveTexture(GL_TEXTURE2);
		glUniform1i(m_TextureSpecularUniformLocation, 2);
		glBindTexture(GL_TEXTURE_2D, object->getSpecularMapID());
	}
}

}
