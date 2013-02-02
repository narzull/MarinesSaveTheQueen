#ifndef __ENEMYUNIT_HPP__
#define __ENEMYUNIT_HPP__

#include "../api/Entity.hpp"
#include "../game/GroundUnit.hpp"

#include <glm/glm.hpp>

#define ENEMY_WAITING 1
#define ENEMY_WALKING 2
#define ENEMY_FIRING 3

//GroundUnit class
namespace game {
class EnemyUnit : public api::Entity{
public:
  
    //Static attribute
    const static float s_ENEMYUNIT_Y_COORD = 0.15f;
    
    //Constructor
    EnemyUnit(GroundUnit * groundUnit, float speed);
    virtual ~EnemyUnit(){};
    
    //Getters
    unsigned int getAction()const{ return m_Action;};
    float getSpeed()const{ return m_Speed;};
    GroundUnit * getGroundUnitToReach()const{return m_GroundUnitToReach;};
    
    //Setters
    void setSpeed(float speed){m_Speed = speed;};
    void setAction(int action){m_Action = action;};
    int setGroundUnitToReach(GroundUnit* groundUnitToReach);
    
    //Public methods
    void walk();
    void autoRotateFromDirection();
    
private:
    GroundUnit * m_GroundUnitToReach;
    float m_Speed;
    unsigned int m_Action;
};
} // namespace game
#endif // __ENEMYUNIT_HPP__
