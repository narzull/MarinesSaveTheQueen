#include "../include/api/Entity.hpp"

#include <glm/gtc/matrix_transform.hpp> 

namespace api{
	void Entity::setPosition(const glm::vec3 & newPosition){
		m_Position = newPosition;
	}
	void Entity::setRotation(const glm::vec3 & angles){
		m_Angles = angles;
	}
	void Entity::setScale(const glm::vec3 & scale){
		m_Scale = scale;
	}
	void Entity::updateModel(){
		m_Model = glm::mat4();
		m_Model = glm::translate(m_Model, m_Position);
		m_Model = glm::rotate(m_Model, m_Angles.x, glm::vec3(1.0,0.0,0.0));
		m_Model = glm::rotate(m_Model, m_Angles.y, glm::vec3(0.0,1.0,0.0));
		m_Model = glm::rotate(m_Model, m_Angles.z, glm::vec3(0.0,0.0,1.0));
		m_Model = glm::scale(m_Model, m_Scale);
	}
}//namespace api