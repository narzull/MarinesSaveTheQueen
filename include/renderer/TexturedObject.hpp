#ifndef __TEXTUREDOBJECT__HPP__
#define __TEXTUREDOBJECT__HPP__

#include "Object.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

//Class that represent a 3D Textured Object
namespace renderer{
class TexturedObject : public Object{
public:
	//Constructor & destructor
	TexturedObject();
	virtual ~TexturedObject();
	//Setters
	void setUvs(const std::vector<glm::vec2> & uvs);
	void assignTexture(GLuint textureID);
	void assignNormalMap(GLuint normalMapID);
	//Getters
	bool hasUvs(){return m_HasUvs;};
	bool hasTexture(){return m_HasTexture;};
	bool hasNormalMap(){return m_HasNormalMap;};
	GLuint getTextureID(){return m_TextureID;};
	GLuint getNormalMapID(){return m_NormalMapID;};
protected:
	//Attribute
	static const GLuint m_NORMAL_ATTRIB_LOCATION = 1;
	static const GLuint m_UVS_ATTRIB_LOCATION = 2;
	//Uvs
	bool m_HasUvs;
	GLuint m_VBOUvs;
	//Texture
	bool m_HasTexture;
	bool m_HasNormalMap;
	GLuint m_TextureID;
	GLuint m_NormalMapID;
	//Normals
	GLuint m_VBONormals;
	//Indices
	GLuint m_VBOIndices;
};
}
#endif //texturedobject.hpp