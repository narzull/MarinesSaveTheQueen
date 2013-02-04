#ifndef __DEFENSEUNIT_HPP__
#define __DEFENSEUNIT_HPP__

#include "../api/Entity.hpp"
#include "../game/GroundUnit.hpp"

#define DEFENSEUNIT_TURRET -1
#define DEFENSEUNIT_CADENCOR -2
#define DEFENSEUNIT_MIRROR -3

//GroundUnit class
namespace game {
class DefenseUnit : public api::Entity{
public:
    //Constructor
    DefenseUnit(glm::vec3 rotation, float yOffset, GroundUnit * relatedGroundUnit, int type):m_RelatedGroundUnit(relatedGroundUnit), m_Type(type){
      m_RelatedGroundUnit->setOccupied(true);
      setRotation(rotation);
      setPosition(relatedGroundUnit->getPosition() + glm::vec3(0.0, yOffset, 0.0));
      updateModel();
    };
    
    //Getters
    int getDefenseUnitType()const{return m_Type;}
    GroundUnit * getRelatedGroundUnit()const{return m_RelatedGroundUnit;}
    
protected:
    GroundUnit * m_RelatedGroundUnit;
    int m_Type;
};
} // namespace game
#endif // __DEFENSEUNIT_HPP__
