#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include "UniformObject.hpp"
#include <vector>
#include <string>

//Class to handle animated mesh
namespace renderer{
class Animation{
public:
	//Constructor & Destructor
	Animation();
	~Animation();
	//Public Methods
	void addObjToAnimation(const std::string & objFile, bool smooth);
	void assignTexture(GLuint textureID);
	void assignNormalTexture(GLuint textureID);
	void assignSpecularTexture(GLuint textureID);
	const UniformObject * getAnimationUniformObject(unsigned int frameID)const;
	
private:
	std::vector<UniformObject *> m_UniformObjectVector;
};
}
#endif