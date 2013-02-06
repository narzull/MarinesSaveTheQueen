#ifndef __BASESHADERMANAGER_HPP__
#define __BASESHADERMANAGER_HPP__

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace renderer{
class BaseShaderManager{
public:
	BaseShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~BaseShaderManager(){};
	//Getters
	GLuint getShaderID()const{return m_ShaderProgram;};
protected:
	//Private Methods
	static const char* readFile(const char* filePath);
	GLuint loadProgram(const char* vertexShaderFile, const char* fragmentShaderFile);
	
	//Private Attribute
	GLuint m_ShaderProgram;
};
}
#endif //simpleshadermanager.hpp