#ifndef __SIMPLESHADERMANAGER_HPP__
#define __SIMPLESHADERMANAGER_HPP__

#include "../Color.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace renderer{
class SimpleShaderManager{
public:
	SimpleShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~SimpleShaderManager(){};
	//Setters
	void setColorInShader(const Color & col)const;
	void set3DMatrixInShader(const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection)const;
	//Getters
	GLuint getShaderID()const{return m_ShaderProgram;};
protected:
	//Private Methods
	static const char* readFile(const char* filePath);
	GLuint loadProgram(const char* vertexShaderFile, const char* fragmentShaderFile);
	
	//Private Attribute
    GLuint m_ShaderProgram;
    GLint m_ColorUniformLocation;
	GLint m_ModelUniformLocation;
	GLint m_ViewUniformLocation;
	GLint m_ProjectionUniformLocation;
};
}
#endif //simpleshadermanager.hpp