#ifndef __BARRIER_HPP__
#define __BARRIER_HPP__

#include "../api/Entity.hpp"
#include <iostream>
//GroundUnit class
namespace game {
class Barrier: public api::Entity{
public:
      //Static attribute
    const static float s_BARRIER_Y_COORD = 0.0f;
  
    //Constructor
    Barrier(const glm::vec3 & rotation, GroundUnit * relatedGroundUnit):m_RelatedGroundUnit(relatedGroundUnit){
      m_RelatedGroundUnit->setOccupied(true);
      m_RelatedGroundUnit->setWeight(-1);
      setRotation(rotation);
      setPosition(relatedGroundUnit->getPosition() + glm::vec3(0.0, (float)s_BARRIER_Y_COORD, 0.0));
      updateModel();
    };
    
    //Getters
    GroundUnit * getRelatedGroundUnit()const{ return m_RelatedGroundUnit;};

private:
    GroundUnit * m_RelatedGroundUnit;
};
} // namespace game
#endif // __BARRIER_HPP__
