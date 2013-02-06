#ifndef __SIMPLE2DPANEL__HPP__
#define __SIMPLE2DPANEL__HPP__

#include <GL/glew.h>

//Abstract class that represent a basic object
namespace renderer{
class Simple2DPanel{
public:
	//Constructor & Destructor
	Simple2DPanel();
	~Simple2DPanel();
	//Methods
	void draw(GLenum primitive) const;
private:
	//Attribute
	static const GLuint m_POSITION_ATTRIB_LOCATION = 0;
	GLuint m_VBOIndices;
	GLuint m_VBOVertices;
	GLuint m_VAO;
};
}

#endif //Simple2DPanel.hpp