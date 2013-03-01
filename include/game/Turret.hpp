#ifndef __TURRET_HPP__
#define __TURRET_HPP__

#include "../api/Entity.hpp"
#include "DefenseUnit.hpp"
#include "Ray.hpp"
#include <vector>

//GroundUnit class
namespace game {
class Turret: public api::Entity{
public:
      //Static attribute
    const static float s_TURRET_Y_COORD = 0.0f;
    const static unsigned int s_TURRET_DEFAULT_CADENCY = 120;
    const static unsigned int s_TURRET_DEFAULT_RANGE = 3;
    const static unsigned int s_SHOWRAY_FRAME_NUMBER = 10;
  
    //Constructor
    Turret(const glm::vec3 & rotation, GroundUnit * relatedGroundUnit): m_Cadency(s_TURRET_DEFAULT_CADENCY), m_TurnCounter(0), m_Range(s_TURRET_DEFAULT_RANGE), m_RelatedGroundUnit(relatedGroundUnit){
      m_RelatedGroundUnit->setOccupied(true);
      m_RelatedGroundUnit->setWeight(-1);
      setRotation(rotation);
      setPosition(relatedGroundUnit->getPosition() + glm::vec3(0.0, (float)s_TURRET_Y_COORD, 0.0));
      updateModel();
    };
    
    ~Turret(){
      //m_RelatedGroundUnit->setOccupied(false);
      //m_RelatedGroundUnit->setWeight(0);
    }
    
    //Getters
    void getRayVector(std::vector<Ray> & rayVector)const;
    GroundUnit * getRelatedGroundUnit()const{return m_RelatedGroundUnit;}
    //Turret public functions
    bool isFiring()const;
    bool showRay()const;
    void update();
    void initFromOtherDefenseUnit(std::vector<DefenseUnit> & otherDefenseUnit);

private:
  
    void computeAndAddRay(unsigned int x, unsigned int z, const glm::vec3 & rotation, std::vector<Ray> & rayVector, glm::vec3 position);
  
    std::vector<Ray> m_RayVector;
    unsigned int m_Cadency;
    unsigned int m_TurnCounter;
    unsigned int m_Range;
    GroundUnit * m_RelatedGroundUnit;
};
} // namespace game
#endif // __DEFENSEUNIT_HPP__
