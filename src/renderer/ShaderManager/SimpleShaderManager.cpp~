#include "renderer/ShaderManager/SimpleShaderManager.hpp"
#include "api/Tools.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

namespace renderer{
//Constructor
SimpleShaderManager::SimpleShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile){

	//Creating shader
    m_ShaderProgram = loadProgram(vertexShaderFile, fragmentShaderFile);
    if(!m_ShaderProgram) throw std::runtime_error("Program loading has failed");
    
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

void SimpleShaderManager::set3DMatrixInShader(const glm::mat4 & modelMat, const glm::mat4 & viewMat, const glm::mat4 & projectionMat)const{
	GLfloat model[16];
	GLfloat view[16];
	GLfloat projection[16];
	tools::transformToTable(model, modelMat);
	tools::transformToTable(view, viewMat);
	tools::transformToTable(projection, projectionMat);
	glUniformMatrix4fv(m_ModelUniformLocation, 1, false, model);
	glUniformMatrix4fv(m_ViewUniformLocation, 1, false, view);
	glUniformMatrix4fv(m_ProjectionUniformLocation, 1, false, projection);
}
	
//Private methods
const char* SimpleShaderManager::readFile(const char* filePath) {
	std::ifstream file(filePath);

    if (!file) {
        return 0;
    }

    file.seekg(0, std::ios_base::end);
    size_t length = file.tellg();
    file.seekg(0);

    char* src = new char[length];
    file.read(src, length);
    src[length - 1] = '\0';

    return src;
}

GLuint SimpleShaderManager::loadProgram(const char* vertexShaderFile, const char* fragmentShaderFile) {
    const char* vertexShaderSource = readFile(vertexShaderFile);
    if(!vertexShaderSource) {
        std::cerr << "Unable to load " << vertexShaderFile << std::endl;
        return 0;
    }

    const char* fragmentShaderSource = readFile(fragmentShaderFile);
    if(!fragmentShaderSource) {
        std::cerr << "Unable to load " << fragmentShaderFile << std::endl;
        return 0;
    }

    // Creation d'un Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Spécification du code source
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);

    // Compilation du shader
    glCompileShader(vertexShader);

    /// Vérification que la compilation a bien fonctionnée (très important !)
    GLint compileStatus;

    // Récupération du status de compilation
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE) {
        // Si echec, récupération de la taille du log de compilation
        GLint logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caractère suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetShaderInfoLog(vertexShader, logLength, 0, log);
        std::cerr << "Vertex Shader error:" << log << std::endl;
        std::cerr << vertexShaderSource << std::endl;

        delete [] log;
        return 0;
    }

    // Creation d'un Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Spécification du code source
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);

    // Compilation du shader
    glCompileShader(fragmentShader);

    /// Vérification que la compilation a bien fonctionnée (très important !)

    // Récupération du status de compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE) {
        // Si echec, récupération de la taille du log de compilation
        GLint logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caractère suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetShaderInfoLog(fragmentShader, logLength, 0, log);
        std::cerr << "Fragment Shader error:" << log << std::endl;
        std::cerr << fragmentShaderSource << std::endl;

        delete [] log;
        return 0;
    }

    GLuint program;

    // Creation d'un programme
    program = glCreateProgram();

    // Attachement des shaders au programme
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Désallocation des shaders: ils ne seront réellement supprimés que lorsque le programme sera supprimé
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Edition de lien
    glLinkProgram(program);

    /// Vérification que l'édition de liens a bien fonctionnée (très important aussi !)
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE) {
        // Si echec, récupération de la taille du log de link
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caractère suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetProgramInfoLog(program, logLength, 0, log);
        std::cerr << "Program link error:" << log << std::endl;

        delete [] log;
        return 0;
    }

    delete [] vertexShaderSource;
    delete [] fragmentShaderSource;

	std::cout << "Loaded " << vertexShaderFile << " and " << fragmentShaderFile << " Program ID = " << program << std::endl;
    return program;
}

}
