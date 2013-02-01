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
    if(m_EyeUniformLocation < 0) throw std::runtime_error("No uniform variable called eye in the shader");
    
    //Light
    m_LightPosUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.position");
    if(m_LightPosUniformLocation < 0) throw std::runtime_error("No uniform variable called light.position in the shader");

    m_LightPowerUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.power");
    if(m_LightPowerUniformLocation < 0) throw std::runtime_error("No uniform variable called light.power in the shader");

    //Material
    m_MaterialAmbiantUniformLocation = glGetUniformLocation(m_ShaderProgram, "material.ambient");
    if(m_MaterialAmbiantUniformLocation < 0) throw std::runtime_error("No uniform variable called material.ambient in the shader");
    
    m_MaterialDiffuseUniformLocation = glGetUniformLocation(m_ShaderProgram, "material.diffuse");
    if(m_MaterialDiffuseUniformLocation < 0) throw std::runtime_error("No uniform variable called material.diffuse in the shader");
    
    m_MaterialSpecularUniformLocation = glGetUniformLocation(m_ShaderProgram, "material.specular");
    if(m_MaterialSpecularUniformLocation < 0) throw std::runtime_error("No uniform variable called material.specular in the shader");
    
    m_MaterialKAUniformLocation = glGetUniformLocation(m_ShaderProgram, "material.ka");
    if(m_MaterialKAUniformLocation < 0) throw std::runtime_error("No uniform variable called material.ka in the shader");
    
    m_MaterialKDUniformLocation = glGetUniformLocation(m_ShaderProgram, "material.kd");
    if(m_MaterialKDUniformLocation < 0) throw std::runtime_error("No uniform variable called material.kd in the shader");
    
    m_MaterialKSUniformLocation = glGetUniformLocation(m_ShaderProgram, "material.ks");
    if(m_MaterialKSUniformLocation < 0) throw std::runtime_error("No uniform variable called material.ks in the shader");
    
    m_MaterialShininessUniformLocation = glGetUniformLocation(m_ShaderProgram, "material.shininess");
    if(m_MaterialShininessUniformLocation < 0) throw std::runtime_error("No uniform variable called material.shininess in the shader");
    
//     Texture
    m_HasUvsUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasUvs");
    if(m_HasUvsUniformLocation < 0) throw std::runtime_error("No uniform variable called hasUvs in the shader");
    
    m_HasTextureUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasTexture");
    if(m_HasTextureUniformLocation < 0) throw std::runtime_error("No uniform variable called hasTexture in the shader");
	
	m_HasNormalMapUniformLocation = glGetUniformLocation(m_ShaderProgram, "hasNormalMap");
	if(m_HasNormalMapUniformLocation < 0) throw std::runtime_error("No uniform variable called hasNormalMap in the shader");
	
	m_TextureDiffuseUniformLocation = glGetUniformLocation(m_ShaderProgram, "textureUnitDiffuse");
	if(m_TextureDiffuseUniformLocation < 0) throw std::runtime_error("No uniform variable called textureUnitDiffuse in the shader");
		
	m_TextureNormalUniformLocation = glGetUniformLocation(m_ShaderProgram, "normalUnitDiffuse");
	if(m_TextureNormalUniformLocation < 0) throw std::runtime_error("No uniform variable called normalUnitDiffuse in the shader");
}

	void LightShaderManager::setEyeInShader(const glm::vec3 & eye)const{
		glUniform4f(m_EyeUniformLocation, eye.x, eye.y, eye.z, 1.0);
	}
	
	void LightShaderManager::setLightInShader(const Light & light)const{
		glUniform4f(m_LightPosUniformLocation, light.m_Pos.x, light.m_Pos.y, light.m_Pos.z, 1.0);
		glUniform1f(m_LightPowerUniformLocation, light.m_Power);
	}
	
	void LightShaderManager::setMaterialInShader(const Material & material)const{
		glUniform4f(m_MaterialAmbiantUniformLocation, material.m_Ambiant.m_R, material.m_Ambiant.m_G, material.m_Ambiant.m_B, 1.0);
		glUniform4f(m_MaterialDiffuseUniformLocation, material.m_Diffuse.m_R, material.m_Diffuse.m_G, material.m_Diffuse.m_B, 1.0);
		glUniform4f(m_MaterialSpecularUniformLocation, material.m_Specular.m_R, material.m_Specular.m_G, material.m_Specular.m_B, 1.0);
		glUniform1f(m_MaterialKAUniformLocation, material.m_Ka);
		glUniform1f(m_MaterialKDUniformLocation, material.m_Kd);
		glUniform1f(m_MaterialKSUniformLocation, material.m_Ks);
		glUniform1f(m_MaterialShininessUniformLocation, material.m_Shininess);
	}
	
	void LightShaderManager::setObjectTextureInShader(TexturedObject * object){
		glUniform1i(m_HasUvsUniformLocation, object->hasUvs());
		glUniform1i(m_HasTextureUniformLocation, object->hasTexture());
		glUniform1i(m_HasNormalMapUniformLocation, object->hasNormalMap());
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
	}

}
