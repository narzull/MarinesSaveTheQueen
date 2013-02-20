#ifndef __CHANGINGTEXTURE_HPP__
#define __CHANGINGTEXTURE_HPP__

#include <vector>
#include <string>
#include <GL/glew.h>
#include <SDL/SDL_image.h>

//Class to handle texture loading in our program
namespace renderer{
class ChangingTexture{
public:
	//Constructor & Destructor
	ChangingTexture();
	~ChangingTexture();
	//Getters
	GLuint getID(){return m_TextureID;};
	//Public Methods
	void updateTexture(int width, int height, const GLvoid *  data);
private:
	//Attribute
	GLuint m_TextureID;
};
}
#endif