#include "../include/api/Camera.hpp"
#include "../include/api/Tools.hpp"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace api {

// Default constructor
Camera::Camera() :
    m_XAxis(1, 0, 0), m_YAxis(0, 1, 0), m_ZAxis(0, 0, 1), m_Position(0, 0, 0.2){
    updateView();
    setPerspectiveProjection(-0.1, 0.1, -0.1, 0.1, .1, 100);
}

// Updates view
void Camera::updateView() {
    // Rotation to be aligned with correct camera axis
    glm::mat4 RcInv(m_XAxis.x, m_YAxis.x, m_ZAxis.x, 0, m_XAxis.y, m_YAxis.y, m_ZAxis.y, 0, m_XAxis.z, m_YAxis.z, m_ZAxis.z, 0, 0, 0, 0, 1);
    // Translation to be at the right distance from the scene
    glm::mat4 TcInv(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -m_Position.x, -m_Position.y, -m_Position.z, 1);
    // Initializes
    m_View = RcInv * TcInv;
}

void Camera::move(const glm::vec3 & move, const glm::vec3 & angles){
	glm::vec3 cameraNewPos;
	cameraNewPos = m_Position + m_XAxis * move.x + m_YAxis * move.y + m_ZAxis * move.z;

	//Set the translation matrix
	glm::vec3 translationVector(-cameraNewPos);

	//Set the view Matrix
	m_View = glm::mat4();
	m_View = glm::rotate(m_View, -angles.x, glm::vec3(1.0,0.0,0.0));
	m_View = glm::rotate(m_View, -angles.y, glm::vec3(0.0,1.0,0.0));
	m_View = glm::rotate(m_View, -angles.z, glm::vec3(0.0,0.0,1.0));
	m_View = glm::translate(m_View, translationVector);
	
	//Update the camera axis and the position 
	m_XAxis.x = m_View[0][0];
	m_YAxis.x = m_View[0][1];
	m_ZAxis.x = m_View[0][2];

	m_XAxis.y = m_View[1][0];
	m_YAxis.y = m_View[1][1];
	m_ZAxis.y = m_View[1][2];

	m_XAxis.z = m_View[2][0];
	m_YAxis.z = m_View[2][1];
	m_ZAxis.z = m_View[2][2];
	
	m_Position = cameraNewPos;
}

//Setters
void Camera::setPerspectiveProjection(float left, float right, float bottom, float top, float near, float far) {
    m_Projection = glm::mat4( //
        (2 * near) / (right - left), 0, 0, 0, //
        0, (2 * near) / (top - bottom), 0, 0, (right + left) / (right - left), //
        (top + bottom) / (top - bottom), -(far + near) / (far - near), -1, //
        0, 0, -(2 * far * near) / (far - near), 0);
}

void Camera::setOrthoProjection(float left, float right, float bottom, float top, float near, float far) {
    m_Projection = glm::mat4( //
        2 / (right - left), 0, 0, 0, //
        0, 2 / (top - bottom), 0, 0, //
        0, 0, -2 / (far - near), 0, //
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1);
}

void Camera::setPosition(const glm::vec3 &p) {
    m_Position = p;
}

//Getters
glm::vec3 Camera::getPosition() const {
    return m_Position;
}

glm::vec3 Camera::getXAxis() const {
    return m_XAxis;
}

glm::vec3 Camera::getYAxis() const {
    return m_YAxis;
}

glm::vec3 Camera::getZAxis() const {
    return m_ZAxis;
}

glm::mat4 Camera::getView() const {
    return m_View;
}

glm::mat4 Camera::getProjection() const {
    return m_Projection;
}

} // namespace api
