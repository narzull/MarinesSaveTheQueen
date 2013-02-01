#ifndef __OBJECT__HPP__
#define __OBJECT__HPP__

#include <GL/glew.h>

//Abstract class that represent a basic object
namespace renderer{
class Object{
public:
	//Constructor & Destructor
	Object();
	virtual ~Object();
	//Abstract Methods
	virtual void draw(GLenum primitive) const = 0;
protected:
	//Attribute
	static const GLuint m_POSITION_ATTRIB_LOCATION = 0;
	GLuint m_VBOVertices;
	GLuint m_VAO;
};
}

#endif //object.hpp