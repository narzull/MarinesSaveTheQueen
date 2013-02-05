#include "renderer/ShaderManager/LightShaderManager.hpp"
#include "api/Tools.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

namespace renderer{
//Constructor
LightShaderManager::LightShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile):SimpleShaderManager(vertexShaderFile, fragmentShaderFile){
	
    //Eye
    m_EyeUniformLocation = glGetUniformLocation(m_ShaderProgram, "eye");
    //if(m_EyeUniformLocation < 0) throw std::runtime_error("No uniform variable called eye in the shader");
    
    //Light
    m_LightPosUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.position");
    //if(m_LightPosUniformLocation < 0) throw std::runtime_error("No uniform variable called light.position in the shader");
    
    m_LightColorUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.color");
    //if(m_LightColorUniformLocation < 0) throw std::runtime_error("No uniform variable called light.color in the shader");

    m_LightPowerUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.power");
    //if(m_LightPowerUniformLocation < 0) throw std::runtime_error("No uniform variable called light.power in the shader");

    
    //Texture
    m_HasUvsUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasUvs");
    //if(m_HasUvsUniformLocation < 0) throw std::runtime_error("No uniform variable called hasUvs in the shader");
    
    m_HasTextureUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasTexture");
    //if(m_HasTextureUniformLocation < 0) throw std::runtime_error("No uniform variable called hasTexture in the shader");
	
    m_HasNormalMapUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasNormalMap");
    //if(m_HasNormalMapUniformLocation < 0) throw std::runtime_error("No uniform variable called hasNormalMap in the shader");
    
    m_HasSpecularMapUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasSpecularMap");
    //if(m_HasSpecularMapUniformLocation < 0) throw std::runtime_error("No uniform variable called hasSpecularMap in the shader");
    
    m_TextureDiffuseUniformLocation = glGetUniformLocation(m_ShaderProgram, "textureUnitDiffuse");
    //if(m_TextureDiffuseUniformLocation < 0) throw std::runtime_error("No uniform variable called textureUnitDiffuse in the shader");
	    
    m_TextureNormalUniformLocation = glGetUniformLocation(m_ShaderProgram, "normalUnitDiffuse");
    //if(m_TextureNormalUniformLocation < 0) throw std::runtime_error("No uniform variable called normalUnitDiffuse in the shader");
    
    m_TextureSpecularUniformLocation = glGetUniformLocation(m_ShaderProgram, "specularUnitDiffuse");
    //if(m_TextureSpecularUniformLocation < 0) throw std::runtime_error("No uniform variable called specularUnitDiffuse in the shader");
}

	void LightShaderManager::setEyeInShader(const glm::vec3 & eye)const{
		glUniform3f(m_EyeUniformLocation, eye.x, eye.y, eye.z);
	}
	
	void LightShaderManager::setLightInShader(const Light & light)const{
		glUniform4f(m_LightPosUniformLocation, light.m_Pos.x, light.m_Pos.y, light.m_Pos.z, 1.0);
		glUniform3f(m_LightColorUniformLocation, light.m_Color.x, light.m_Color.y, light.m_Color.z);
		glUniform1f(m_LightPowerUniformLocation, light.m_Power);
	}
	
	
	void LightShaderManager::setObjectTextureInShader(TexturedObject * object){
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
