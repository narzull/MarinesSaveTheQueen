#include "renderer/TextureManager.hpp"

#include <iostream>

namespace renderer{
	
	TextureManager::~TextureManager(){
		glDeleteTextures(m_TextureID.size(), &m_TextureID[0]);
	}
	
	GLuint TextureManager::getTextureID(const std::string & textureFileName){
		//If texture already in manager
		int searchedTextureID;
		searchedTextureID = isInManager(textureFileName);
		if(searchedTextureID != -1) return (GLuint)searchedTextureID;
		GLuint newTextureID = loadTexture(textureFileName);
		m_TextureName.push_back(textureFileName);
		m_TextureID.push_back(newTextureID);
		return newTextureID;
	}
	
	GLuint TextureManager::loadTexture(const std::string & textureFileName){
		std::cout << "---------------------------------" << std::endl;
		std::cout << "TEXTURE LOADING : Loading the texture = " << textureFileName << std::endl;
		//Loading the image
		SDL_Surface * texture;
		texture = IMG_Load(textureFileName.c_str());
		
		if(!texture){
			std::cout << "FAILURE : Impossible to load the texture"<< std::endl;
			return 0;
		}

		// Allocates a texture id
		GLuint textureID;
		glGenTextures(1, &textureID);
		// Selects our current texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		// How to handle not normalised uvs
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// How to handle interpolation from texels to fragments
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Specifies which image will be used for this texture objet
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);
		 
		//Free the memory
		SDL_FreeSurface(texture);
		std::cout << "SUCCESS" << std::endl;
		return textureID;
	}
	
	int TextureManager::isInManager(const std::string & textureFileName)const{
		for(size_t i = 0; i < m_TextureName.size(); ++i){
			if(textureFileName.compare(m_TextureName[i]) == 0) return m_TextureID[i];
		}
		return -1;
	}
}