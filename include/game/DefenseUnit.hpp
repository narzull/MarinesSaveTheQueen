#ifndef __DEFENSEUNIT_HPP__
#define __DEFENSEUNIT_HPP__

#include "../api/Entity.hpp"
#include "../game/GroundUnit.hpp"

#define DEFENSEUNIT_CADENCOR -1
#define DEFENSEUNIT_MIRROR -2

//GroundUnit class
namespace game {
class DefenseUnit : public api::Entity{
public:
    const static float s_DEFENSEUNIT_CADENCOR_Y_COORD = 0.0f;
    const static float s_DEFENSEUNIT_MIRROR_Y_COORD = 0.0f;
  
    //Constructor
    DefenseUnit(glm::vec3 rotation, GroundUnit * relatedGroundUnit, int type):m_RelatedGroundUnit(relatedGroundUnit), m_Type(type), m_Used(false){
      m_RelatedGroundUnit->setOccupied(true);
      setRotation(rotation);
      float yOffset = 0.0;
      switch(type){
	case DEFENSEUNIT_CADENCOR:
				    yOffset = (float)s_DEFENSEUNIT_CADENCOR_Y_COORD;
				    break;
	case DEFENSEUNIT_MIRROR:
				    yOffset = (float)s_DEFENSEUNIT_MIRROR_Y_COORD;
				    break;
      }
      setPosition(relatedGroundUnit->getPosition() + glm::vec3(0.0, yOffset, 0.0));
      updateModel();
    };
    
    //Setters
    void setUsed(bool used){ m_Used = used;};
    
    //Getters
    int getType()const{return m_Type;}
    bool isUsed()const{return m_Used;};
    GroundUnit * getRelatedGroundUnit()const{return m_RelatedGroundUnit;}
    
protected:
    GroundUnit * m_RelatedGroundUnit;
    int m_Type;
    bool m_Used;
};
} // namespace game
#endif // __DEFENSEUNIT_HPP__
