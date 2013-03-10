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
  
  void Turret::freeGroundUnit(){
    m_RelatedGroundUnit->setOccupied(false);
    m_RelatedGroundUnit->setWeight(0);
  }
  
  void Turret::getRayVector(std::vector<Ray> & rayVector)const{
    for(std::vector<Ray>::const_iterator it = m_RayVector.begin(); it != m_RayVector.end(); ++it){
      rayVector.push_back((*it));
    }
  }
  
  void Turret::initFromOtherDefenseUnit(std::vector<DefenseUnit> & otherDefenseUnit){
    std::pair<unsigned int, unsigned int> coord = m_RelatedGroundUnit->getGroundUnitCoord();
    computeAndAddRay(coord.first, coord.second, m_Angles, m_RayVector, m_Position);
    
    //Checking for condensator
    for(std::vector<DefenseUnit>::iterator it = otherDefenseUnit.begin(); it != otherDefenseUnit.end(); ++it){
	std::pair<unsigned int, unsigned int> defenseUnitCoord = (*it).getRelatedGroundUnit()->getGroundUnitCoord();
	int deltaX = abs(coord.first - defenseUnitCoord.first);
	int deltaZ = abs(coord.second - defenseUnitCoord.second);
	if(std::max(deltaX, deltaZ) == 1 && (*it).getType() == game::DefenseUnit::s_DEFENSEUNIT_CADENCOR_TYPE){
	  m_Cadency *= 0.70;
	  (*it).setUsed(true);
	}
    }
    
    //Checking for mirrors
    bool rayAdded;
    unsigned int currentRayIndex = 0;
    do{
      rayAdded = false;
      std::pair<unsigned int, unsigned int> begin = m_RayVector[currentRayIndex].getBeginningCoord();
      std::pair<unsigned int, unsigned int> end = m_RayVector[currentRayIndex].getEndingCoord();
      
      //Checking all the defense unit
      for(std::vector<DefenseUnit>::iterator it = otherDefenseUnit.begin(); it != otherDefenseUnit.end(); ++it){
	if((*it).getType() == game::DefenseUnit::s_DEFENSEUNIT_MIRROR_TYPE && !(*it).isUsed()){
	    GroundUnit * localGroundUnit = (*it).getRelatedGroundUnit();
	    std::pair<unsigned int, unsigned int> localCoord = localGroundUnit->getGroundUnitCoord();
	    if((localCoord.first >= begin.first && localCoord.first <= end.first) ||(localCoord.first <= begin.first && localCoord.first >= end.first)){
	      if((localCoord.second >= begin.second && localCoord.second <= end.second) ||(localCoord.second <= begin.second && localCoord.second >= end.second)){
		     m_RayVector[currentRayIndex].changeRayEndingCoord(localCoord);
		     computeAndAddRay(localCoord.first, localCoord.second, (*it).getRotation(), m_RayVector, localGroundUnit->getPosition());
		     rayAdded = true; 
		     (*it).setUsed(true);
	      }
	    }
	}
      }
      ++currentRayIndex;
    }while(rayAdded);
  }
  
  void Turret::computeAndAddRay(unsigned int x, unsigned int z, const glm::vec3 & rotation, std::vector<Ray> & rayVector, glm::vec3 position){
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
      rayVector.push_back(Ray(x, z, endX, endZ, position, rotation));
    }
  }
  
}//namespace game