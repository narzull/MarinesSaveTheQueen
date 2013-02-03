#ifndef __TURRET_HPP__
#define __TURRET_HPP__

#include "DefenseUnit.hpp"

//GroundUnit class
namespace game {
class Turret : public DefenseUnit{
public:
      //Static attribute
    const static float s_TURRET_Y_COORD = 0.0f;
  
    //Constructor
    Turret(glm::vec3 rotation, GroundUnit * relatedGroundUnit):DefenseUnit(rotation, (float)s_TURRET_Y_COORD, relatedGroundUnit, -1){};
};
} // namespace game
#endif // __DEFENSEUNIT_HPP__
