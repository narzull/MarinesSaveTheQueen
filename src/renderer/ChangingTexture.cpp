#include "renderer/ChangingTexture.hpp"

#include <iostream>

namespace renderer{
  	ChangingTexture::ChangingTexture(){
		glGenTextures(1, &m_TextureID);
		// Selects our current texture
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		// How to handle not normalised uvs
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// How to handle interpolation from texels to fragments
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	
	ChangingTexture::~ChangingTexture(){
		glDeleteTextures(1, &m_TextureID);
	}
	
	void ChangingTexture::updateTexture(int width, int height, const GLvoid *  data){
		// Selects our current texture
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		// Specifies which image will be used for this texture objet
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
}