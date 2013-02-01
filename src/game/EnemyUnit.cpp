#include "../include/game/EnemyUnit.hpp"
#include "../include/api/Tools.hpp"
#include <math.h>
#include <iostream>

namespace game{
  EnemyUnit::EnemyUnit(glm::vec3 currentPosition, float speed):Entity(currentPosition), m_DestinationPosition(glm::vec3(0.0,0.15,0.0)), m_Speed(speed), m_Action(ENEMY_WAITING){
    autoRotateFromDirection();
    updateModel();
  }
  
  void EnemyUnit::autoRotateFromDirection(){
    glm::vec3 direction = m_DestinationPosition - m_Position;
    direction = glm::normalize(direction);
    float angle = acosf(direction.x) * 360 / (2*M_PI);
    float angleFinal = 90;
    if(direction.z > 0){
	angleFinal -= angle;
    }
    else{
      angleFinal += angle;
    }
    setRotation(glm::vec3(0.0, angleFinal, 0.0));
  }
  
   void EnemyUnit::walk(){
    glm::vec3 direction = m_DestinationPosition - m_Position;
    float norm = tools::getNorm(direction);
    direction = glm::normalize(direction);
    float step = m_Speed;
    if(step > norm) step = norm;
    m_Position += step*direction;
    updateModel();
  }
}//namespace game