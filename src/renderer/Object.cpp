#include "renderer/Object.hpp"
#include <iostream>
namespace renderer{
	Object::Object(){
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBOVertices);
		glBindVertexArray(0);
	}
	
	Object::~Object(){
		glDeleteBuffers(1, &m_VBOVertices);
		glDeleteVertexArrays(1, &m_VAO);
		std::cout << "Object deleted" << std::endl;
	}
}