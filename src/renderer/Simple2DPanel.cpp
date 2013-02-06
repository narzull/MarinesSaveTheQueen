#include "renderer/Simple2DPanel.hpp"
#include <iostream>
namespace renderer{
	Simple2DPanel::Simple2DPanel(){
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBOVertices);
		glGenBuffers(1, &m_VBOIndices);
		glBindVertexArray(0);
		
		//Setting the data
		int indices[] = {0, 1, 2, 2, 1, 3}; 
		float vertices[] =  {-1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
		
		//Filling the data
		glBindVertexArray(m_VAO);
		// Bind indices and upload data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBOIndices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// Bind vertices and upload data
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
		glEnableVertexAttribArray(m_POSITION_ATTRIB_LOCATION);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Unbind everything. Potentially illegal on some implementations
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	Simple2DPanel::~Simple2DPanel(){
		glDeleteBuffers(1, &m_VBOVertices);
		glDeleteBuffers(1, &m_VBOIndices);
		glDeleteVertexArrays(1, &m_VAO);
		std::cout << "Simple2DPanel deleted" << std::endl;
	}
	
	void Simple2DPanel::draw(GLenum primitive)const{
	    glBindVertexArray(m_VAO);
            glDrawElements(primitive, 2 * 3, GL_UNSIGNED_INT, (void*)0);
	}
}