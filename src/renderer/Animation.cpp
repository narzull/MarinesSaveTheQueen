//renderer include
#include "renderer/Animation.hpp"
#include "renderer/UniformObjectBuilder.hpp"

#include <iostream>

//Class to handle animated mesh
namespace renderer{
	//Constructor
	Animation::Animation(){
	}
	//Destructor
	Animation::~Animation(){
	  std::cout << "---------------------------------" << std::endl;
	  std::cout << "ANIMATION : Destroying" << std::endl;
	  for(unsigned int i = 0; i < m_UniformObjectVector.size(); ++i){
	    delete(m_UniformObjectVector[i]);
	  }
	}
	
	//Public Methods
	void Animation::addObjToAnimation(const std::string & objFile, bool smooth){
	      UniformObjectBuilder objectBuilder;
	      UniformObject * newObject = objectBuilder.buildFromObj(objFile.c_str(), smooth);
	      if(newObject != NULL){
		m_UniformObjectVector.push_back(newObject);
	      }
	      else{
		std::cout << "FAILURE" << std::endl;
	      }
	}
	
	void Animation::assignTexture(GLuint textureID){
	   for(unsigned int i = 0; i < m_UniformObjectVector.size(); ++i){
	    m_UniformObjectVector[i]->assignTexture(textureID);;
	   }
	}
	
	void Animation::assignNormalTexture(GLuint textureID){
	   for(unsigned int i = 0; i < m_UniformObjectVector.size(); ++i){
	    m_UniformObjectVector[i]->assignTexture(textureID);;
	   }
	}
	
	void Animation::assignSpecularTexture(GLuint textureID){
	   for(unsigned int i = 0; i < m_UniformObjectVector.size(); ++i){
	    m_UniformObjectVector[i]->assignTexture(textureID);;
	   }
	}
	
	const UniformObject * Animation::getAnimationUniformObject(unsigned int frameID)const{
	  if(frameID >= m_UniformObjectVector.size()) return NULL;
	  return m_UniformObjectVector[frameID];
	}
	
}