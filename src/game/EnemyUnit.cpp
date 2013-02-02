#include "../include/game/EnemyUnit.hpp"
#include "../include/api/Tools.hpp"
#include <math.h>
#include <iostream>

namespace game{
  EnemyUnit::EnemyUnit(float posX, float posZ, unsigned int xIndex, unsigned int yIndex, float speed):Entity(glm::vec3(posX,(float)EnemyUnit::s_ENEMYUNIT_Y_COORD,posZ)), m_PositionToReach(glm::vec3(0.0,(float)EnemyUnit::s_ENEMYUNIT_Y_COORD,0.0)), m_GroundUnitXToReach(xIndex), m_GroundUnitYToReach(yIndex), m_Speed(speed), m_Action(ENEMY_WAITING){
    autoRotateFromDirection();
    updateModel();
  }
  
  void EnemyUnit::autoRotateFromDirection(){
    glm::vec3 direction = m_PositionToReach - m_Position;
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
    if(m_Action == ENEMY_WALKING){
      glm::vec3 direction = m_PositionToReach - m_Position;
      float norm = tools::getNorm(direction);
      direction = glm::normalize(direction);
      float step = m_Speed;
      if(step > norm){
	step = norm;
	m_Action = ENEMY_WAITING;
      }
      m_Position += step*direction;
      updateModel();
    }
  }
}//namespace game