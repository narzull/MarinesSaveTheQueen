#include "renderer/ShaderManager/LaccumLightShaderManager.hpp"
#include "api/Tools.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

namespace renderer{
//Constructor
LaccumLightShaderManager::LaccumLightShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile):BaseShaderManager(vertexShaderFile, fragmentShaderFile){
    //Eye
    m_EyeUniformLocation = glGetUniformLocation(m_ShaderProgram, "eye");
    if(m_EyeUniformLocation < 0) throw std::runtime_error("No uniform variable called eye in the shader");
    
    //Light
    m_LightPosUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.position");
    if(m_LightPosUniformLocation < 0) throw std::runtime_error("No uniform variable called light.position in the shader");
    
    m_LightColorUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.color");
    if(m_LightColorUniformLocation < 0) throw std::runtime_error("No uniform variable called light.color in the shader");

    m_LightPowerUniformLocation = glGetUniformLocation(m_ShaderProgram, "light.power");
    if(m_LightPowerUniformLocation < 0) throw std::runtime_error("No uniform variable called light.power in the shader");
    
    //Matrix
    m_InverseMatrixUniformLocation = glGetUniformLocation(m_ShaderProgram, "inverseViewProjection");
    if(m_InverseMatrixUniformLocation < 0) throw std::runtime_error("No uniform variable called inverseViewProjection in the shader");
    
    //Textures
    m_TextureDiffuseUniformLocation = glGetUniformLocation(m_ShaderProgram, "textureDiffuse");	
    if(m_TextureDiffuseUniformLocation < 0) throw std::runtime_error("No uniform variable called textureDiffuse in the shader");
    m_TextureNormalUniformLocation = glGetUniformLocation(m_ShaderProgram, "textureNormal");
    if(m_TextureNormalUniformLocation < 0) throw std::runtime_error("No uniform variable called textureNormal in the shader");
    m_TextureDepthUniformLocation = glGetUniformLocation(m_ShaderProgram, "textureDepth");
    if(m_TextureDepthUniformLocation < 0) throw std::runtime_error("No uniform variable called textureDepth in the shader");
}

void LaccumLightShaderManager::setEyeInShader(const glm::vec3 & eye)const{
	glUniform3f(m_EyeUniformLocation, eye.x, eye.y, eye.z);
}

void LaccumLightShaderManager::setLightInShader(const Light & light)const{
	glUniform4f(m_LightPosUniformLocation, light.m_Pos.x, light.m_Pos.y, light.m_Pos.z, light.m_Pos.w);
	glUniform3f(m_LightColorUniformLocation, light.m_Color.x, light.m_Color.y, light.m_Color.z);
	glUniform1f(m_LightPowerUniformLocation, light.m_Power);
}

void LaccumLightShaderManager::setInvMatrixInShader(const glm::mat4 & invMatrix)const{
	GLfloat invMat[16];
	tools::transformToTable(invMat, invMatrix);
	glUniformMatrix4fv(m_InverseMatrixUniformLocation, 1, false, invMat);
}

void LaccumLightShaderManager::setTextureInShaderFromGBuffer(const FramebufferGL & gbuffer)const{
        glUniform1i(m_TextureDiffuseUniformLocation, 0);
        glUniform1i(m_TextureNormalUniformLocation, 1);
        glUniform1i(m_TextureDepthUniformLocation, 2);
	//Color Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gbuffer.colorTexId[0]);        
        //Normal Unit 1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gbuffer.colorTexId[1]);    
        //Depth Unit 2
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gbuffer.depthTexId); 
}
}
