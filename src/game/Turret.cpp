#include "../include/game/Turret.hpp"
#include "../include/game/Board.hpp"
#include <iostream>

namespace game{
  
  bool Turret::isFiring()const{
    if(m_TurnCounter == m_Cadency) return true;
    return false;
  }
  
  bool Turret::showRay()const{
    if(m_TurnCounter <= s_SHOWRAY_FRAME_NUMBER) return true;
    return false;
  }
  
  void Turret::update(){
    if(m_TurnCounter == m_Cadency) m_TurnCounter = 0;
    ++m_TurnCounter;
  }
  
  void Turret::getRayVector(std::vector<Ray> & rayVector)const{
    for(std::vector<Ray>::const_iterator it = m_RayVector.begin(); it != m_RayVector.end(); ++it){
      rayVector.push_back((*it));
    }
  }
  
  void Turret::initFromOtherDefenseUnit(const std::vector<DefenseUnit> & otherDefenseUnit){
    std::pair<unsigned int, unsigned int> coord = m_RelatedGroundUnit->getGroundUnitCoord();
    computeAndAddRay(coord.first, coord.second, m_Angles, m_RayVector, m_Position, m_Angles);
    
    //Checking for condensator
    for(std::vector<DefenseUnit>::const_iterator it = otherDefenseUnit.begin(); it != otherDefenseUnit.end(); ++it){
	std::pair<unsigned int, unsigned int> defenseUnitCoord = (*it).getRelatedGroundUnit()->getGroundUnitCoord();
	int deltaX = abs(coord.first - defenseUnitCoord.first);
	int deltaZ = abs(coord.second - defenseUnitCoord.second);
	if(std::max(deltaX, deltaZ) == 1 && (*it).getType() == DEFENSEUNIT_CADENCOR){
	  m_Cadency *= 0.70;
	}
    }
  }
  
  void Turret::computeAndAddRay(unsigned int x, unsigned int z, const glm::vec3 & rotation, std::vector<Ray> & rayVector, glm::vec3 position, glm::vec3 angles){
    int endingX = x;
    int endingZ = z;
    if(int(rotation.y) % 90 != 0){
      std::cout << "Warning during the ray computing, angle.y % 90 != 0 ! No ray added !" << std::endl;
    }
    else{
      endingX += m_Range * cos(rotation.y*2*M_PI/360.0);
      endingZ += m_Range * -sin(rotation.y*2*M_PI/360.0);
      if(endingX < 0) endingX = 0;
      if(endingZ < 0) endingZ = 0;
      unsigned int endX = (unsigned int)endingX;
      unsigned int endZ = (unsigned int)endingZ;
      if(endX >= (unsigned int)Board::s_GROUNDUNIT_NUMBER_WIDTH) endX = (unsigned int)Board::s_GROUNDUNIT_NUMBER_WIDTH - 1;
      if(endZ >= (unsigned int)Board::s_GROUNDUNIT_NUMBER_HEIGHT) endZ = (unsigned int)Board::s_GROUNDUNIT_NUMBER_HEIGHT - 1;
      rayVector.push_back(Ray(x, z, endX, endZ, position, angles));
    }
  }
  
}//namespace game