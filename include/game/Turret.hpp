#ifndef __TURRET_HPP__
#define __TURRET_HPP__

#include "DefenseUnit.hpp"
#include "Ray.hpp"
#include <vector>

//GroundUnit class
namespace game {
class Turret : public DefenseUnit{
public:
      //Static attribute
    const static float s_TURRET_Y_COORD = 0.0f;
    const static unsigned int s_TURRET_DEFAULT_CADENCY = 120;
    const static unsigned int s_TURRET_DEFAULT_RANGE = 3;
    const static unsigned int s_SHOWRAY_FRAME_NUMBER = 10;
  
    //Constructor
    Turret(const glm::vec3 & rotation, GroundUnit * relatedGroundUnit):DefenseUnit(rotation, (float)s_TURRET_Y_COORD, relatedGroundUnit, -1), m_Cadency(s_TURRET_DEFAULT_CADENCY), m_TurnCounter(0), m_Range(s_TURRET_DEFAULT_RANGE){};
    
    //Getters
    void getRayVector(std::vector<Ray> & rayVector)const;
    //Turret public functions
    bool isFiring()const;
    bool showRay()const;
    void update();
    void initFromOtherDefenseUnit();

private:
  
    void computeAndAddRay(unsigned int x, unsigned int z, const glm::vec3 & rotation, std::vector<Ray> & rayVector, glm::vec3 position, glm::vec3 angles);
  
    std::vector<Ray> m_RayVector;
    unsigned int m_Cadency;
    unsigned int m_TurnCounter;
    unsigned int m_Range;
};
} // namespace game
#endif // __DEFENSEUNIT_HPP__
