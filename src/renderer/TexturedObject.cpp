#include "renderer/TexturedObject.hpp"
#include <iostream>
namespace renderer{
	TexturedObject::TexturedObject(){
		glBindVertexArray(m_VAO);
		GLuint index[3];
		glGenBuffers(3, index);
		glBindVertexArray(0);
		m_VBOIndices = index[0];
		m_VBONormals = index[1];
		m_VBOUvs = index[2];
		m_HasUvs = false;
		m_HasTexture = false;
		m_HasNormalMap = false;
	}
	
	TexturedObject::~TexturedObject(){
		glDeleteBuffers(1, &m_VBOUvs);
		glDeleteBuffers(1, &m_VBOIndices);
		glDeleteBuffers(1, &m_VBONormals);
	}
	
	void TexturedObject::setUvs(const std::vector<glm::vec2> & uvs){
		m_HasUvs = true;
		int uvsNumber = uvs.size() * 2;
		GLfloat * uvsTab = new GLfloat[uvsNumber];
		for(size_t i = 0; i < uvs.size(); ++i){
			uvsTab[2*i] = uvs[i].x;
			uvsTab[2*i+1] = uvs[i].y;
		}
		glBindVertexArray(m_VAO);
		glEnableVertexAttribArray(m_UVS_ATTRIB_LOCATION);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOUvs);
		glBufferData(GL_ARRAY_BUFFER, uvsNumber*sizeof(GLfloat), uvsTab, GL_STATIC_DRAW);
		glVertexAttribPointer(m_UVS_ATTRIB_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)0);
		glBindVertexArray(0);
		delete [] uvsTab;
	}
	
	void TexturedObject::assignTexture(GLuint textureID){
		m_HasTexture = true;
		m_TextureID = textureID;
	}
	
	void TexturedObject::assignNormalMap(GLuint normalMapID){
		m_HasNormalMap = true;
		m_NormalMapID = normalMapID;
	}
}