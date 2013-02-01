#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <glm/glm.hpp>

//Entity class
namespace api {
class Entity {
public:
    //Constructor
    Entity():m_Model(glm::mat4()), m_Position(glm::vec3()), m_Angles(glm::vec3()), m_Scale(glm::vec3(1.0,1.0,1.0)){};
    Entity(glm::vec3 position):m_Model(glm::mat4()), m_Position(position), m_Angles(glm::vec3()), m_Scale(glm::vec3(1.0,1.0,1.0)){};
    virtual ~Entity(){};
    //Getters
    glm::mat4 getModel() const {return m_Model;};
    glm::vec3 getPosition() const {return m_Position;};
    glm::vec3 getRotation() const {return m_Angles;};
    glm::vec3 getScale() const {return m_Scale;};
    //General methods
    void setPosition(const glm::vec3 & newPosition);
    void setRotation(const glm::vec3 & angles);
    void setScale(const glm::vec3 & scale);
    void updateModel(); 
protected:
    //Attribute
    glm::mat4 m_Model;
    glm::vec3 m_Position;
    glm::vec3 m_Angles;
    glm::vec3 m_Scale;
};
} // namespace api
#endif // __CAMERA_HPP__
