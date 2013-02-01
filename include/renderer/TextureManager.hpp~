#ifndef __TEXTUREMANAGER_HPP__
#define __TEXTUREMANAGER_HPP__

#include <vector>
#include <string>
#include <GL/glew.h>
#include <SDL/SDL_image.h>

//Class to handle texture loading in our program
namespace renderer{
class TextureManager{
public:
	//Constructor & Destructor
	TextureManager(){};
	~TextureManager();
	//Getters
	GLuint getTextureID(const std::string & textureFileName);
	
private:
	//Internal methods to manage textures
	GLuint loadTexture(const std::string & textureFileName);
	int isInManager(const std::string & textureFileName)const;
	//Attribute
	std::vector<std::string> m_TextureName;
	std::vector<GLuint> m_TextureID;
};
}
#endif