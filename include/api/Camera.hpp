#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/glm.hpp>

//Camera class
namespace api {
struct Camera {
	//Constructor
    Camera();
	//Setters
    void setPosition(const glm::vec3&);
    void setPerspectiveProjection(float left, float right, float bottom, float top, float near, float far);
    void setOrthoProjection(float left, float right, float bottom, float top, float near, float far);
    void setView(const glm::mat4 & view){m_View = view;};
    void setProjection(const glm::mat4 & proj){m_Projection = proj;};
	//Getters
    glm::vec3 getXAxis() const;
    glm::vec3 getYAxis() const;
    glm::vec3 getZAxis() const;
    glm::vec3 getPosition() const;
    glm::mat4 getView() const;
    glm::mat4 getProjection() const;
    //General methods
    void move(const glm::vec3 & move, const glm::vec3 & angle);
    void reset();
private:
    void updateView();
	//Attribute
    glm::vec3 m_XAxis; // Camera axis x : right side
    glm::vec3 m_YAxis; // Camera axis y : up
    glm::vec3 m_ZAxis; // Camera axis z : backward
    glm::vec3 m_Position; // Camera position
    glm::mat4 m_View; // View matrix
    glm::mat4 m_Projection; // Projection matrix
};
} // namespace api
#endif // __CAMERA_HPP__
