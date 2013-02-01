#ifndef __UNIFORMOBJECT__HPP__
#define __UNIFORMOBJECT__HPP__

#include "TexturedObject.hpp"
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

//Class that represent a 3D Textured Object that will not change 
namespace renderer{
class UniformObject : public TexturedObject{
public:
	//Constructor & Destructor
	UniformObject(){};
	virtual ~UniformObject(){};
	//Public methods
	virtual void draw(GLenum primitive) const;
	void buildFromVector(const std::vector<glm::vec3> & verticesVector, const std::vector<size_t> & indicesVector, std::vector<glm::vec3> & normalVector, bool computeNormals, bool smooth); 
	
protected:
	//Internal methods to modify the object
	void computeNormals(const std::vector<glm::vec3> & verticesVector, const std::vector<size_t> & indicesVector, std::vector<glm::vec3> & normalsVector);
	void smoothNormals(const std::vector<glm::vec3> & verticesVector, const std::vector<size_t> & indicesVector, std::vector<glm::vec3> & normalVector);
	//Attributes
	GLsizei m_IndicesNumber;
};
}
#endif //uniformobject.hpp