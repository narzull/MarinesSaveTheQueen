#ifndef __SIMPLESHADERMANAGER_HPP__
#define __SIMPLESHADERMANAGER_HPP__

#include "../Color.hpp"
#include "./BaseShaderManager.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace renderer{
class SimpleShaderManager : public BaseShaderManager{
public:
	SimpleShaderManager(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~SimpleShaderManager(){};
	//Setters
	void setColorInShader(const Color & col)const;
	void setCameraMatrixInShader(const glm::mat4 & view, const glm::mat4 & projection)const;
	void setModelMatrixInShader(const glm::mat4 & modelMat)const;
protected:
	
	//Private Attribute
	GLint m_ColorUniformLocation;
	GLint m_ModelUniformLocation;
	GLint m_ViewUniformLocation;
	GLint m_ProjectionUniformLocation;
};
}
#endif //simpleshadermanager.hpp