#include "../include/game/EnemyUnit.hpp"
#include "../include/api/Tools.hpp"
#include <math.h>
#include <iostream>

namespace game{
  EnemyUnit::EnemyUnit(GroundUnit * groundUnit, float speed):Entity(groundUnit->getPosition() + glm::vec3(0.0,(float)EnemyUnit::s_ENEMYUNIT_Y_COORD,0.0)), m_GroundUnitToReach(groundUnit), m_Speed(speed), m_Action(ENEMY_WAITING), m_LoopCounter(0){
    m_GroundUnitToReach->setOccupied(true);
    updateModel();
    m_WalkFrameAnimationCounter = rand() % 10;
  }
  
  bool EnemyUnit::setGroundUnitToReach(GroundUnit* groundUnitToReach){
    if(!groundUnitToReach->isOccupied()){
      m_GroundUnitToReach->setOccupied(false);
      m_GroundUnitToReach = groundUnitToReach;
      m_GroundUnitToReach->setOccupied(true);
      autoRotateFromDirection(m_GroundUnitToReach->getPosition());
      return true;
    }
    return false;
  }
  
  void EnemyUnit::autoRotateFromDirection(glm::vec3 destinationPosition){
    glm::vec3 positionToReach = destinationPosition + glm::vec3(0.0,(float)EnemyUnit::s_ENEMYUNIT_Y_COORD,0.0);
    glm::vec3 direction = positionToReach - m_Position;
    direction = glm::normalize(direction);
    float angle = acosf(direction.x) * 360 / (2*M_PI);
    float angleFinal = 0;
    if(direction.z > 0){
	angleFinal -= angle;
    }
    else{
      angleFinal += angle;
    }
    setRotation(glm::vec3(0.0, angleFinal, 0.0));
  }
  
  void EnemyUnit::autoRotateForFire(){
    autoRotateFromDirection(glm::vec3(0.0, 0.0, 0.0));
    updateModel();
  }
  
   void EnemyUnit::walk(){
    if(m_Action == ENEMY_WALKING){
      //Updating the position
      glm::vec3 positionToReach = m_GroundUnitToReach->getPosition() + glm::vec3(0.0,(float)EnemyUnit::s_ENEMYUNIT_Y_COORD,0.0);
      glm::vec3 direction = positionToReach - m_Position;
      float norm = tools::getNorm(direction);
      direction = glm::normalize(direction);
      float step = m_Speed;
      if(step > norm){
	step = norm;
	m_Action = ENEMY_WAITING;
      }
      m_Position += step*direction;
      updateModel();
      
      //Updating the animation frame
      if(m_LoopCounter % s_ENEMYUNIT_WALK_ANIM_SPEED == 0){
	++m_WalkFrameAnimationCounter;
	m_WalkFrameAnimationCounter = m_WalkFrameAnimationCounter%10;
      }
    }
  }
  
  void EnemyUnit::updateCounter(){
    ++m_LoopCounter;
    if(m_LoopCounter%1000 == 0)m_LoopCounter = 0;
  }
}//namespace game