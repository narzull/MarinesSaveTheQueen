#include "renderer/ShaderManager/SimpleShaderManager.hpp"
#include "api/Tools.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

namespace renderer{
//Constructor
SimpleShaderManager::SimpleShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile):BaseShaderManager(vertexShaderFile, fragmentShaderFile){
  
    //Color
    m_ColorUniformLocation = glGetUniformLocation(m_ShaderProgram, "vertexColor");
    if(m_ColorUniformLocation < 0) throw std::runtime_error("No uniform variable called localColor in the shader");
    
    //For 3D rendering
    m_ModelUniformLocation = glGetUniformLocation(m_ShaderProgram, "model");
    if(m_ModelUniformLocation < 0) throw std::runtime_error("No uniform variable called model in the shader");

    m_ViewUniformLocation = glGetUniformLocation(m_ShaderProgram, "view");
    if(m_ViewUniformLocation < 0) throw std::runtime_error("No uniform variable called view in the shader");

    m_ProjectionUniformLocation = glGetUniformLocation(m_ShaderProgram, "projection");
    if(m_ProjectionUniformLocation < 0) throw std::runtime_error("No uniform variable called projection in the shader");
}

//Setters
void SimpleShaderManager::setColorInShader(const Color & col)const{
	glUniform3f(m_ColorUniformLocation, col.m_R, col.m_G, col.m_B);
}

void SimpleShaderManager::setCameraMatrixInShader(const glm::mat4 & viewMat, const glm::mat4 & projectionMat)const{
	GLfloat view[16];
	GLfloat projection[16];
	tools::transformToTable(view, viewMat);
	tools::transformToTable(projection, projectionMat);
	glUniformMatrix4fv(m_ViewUniformLocation, 1, false, view);
	glUniformMatrix4fv(m_ProjectionUniformLocation, 1, false, projection);
}

void SimpleShaderManager::setModelMatrixInShader(const glm::mat4 & modelMat)const{
	GLfloat model[16];
	tools::transformToTable(model, modelMat);
	glUniformMatrix4fv(m_ModelUniformLocation, 1, false, model);
}
}
