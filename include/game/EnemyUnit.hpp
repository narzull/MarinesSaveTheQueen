#ifndef __ENEMYUNIT_HPP__
#define __ENEMYUNIT_HPP__

#include "../api/Entity.hpp"

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
    EnemyUnit(float posX, float posZ, unsigned int xIndex, unsigned int yIndex, float speed);
    virtual ~EnemyUnit(){};
    
    //Getters
    unsigned int getAction()const{ return m_Action;};
    float getSpeed()const{ return m_Speed;};
    void getGroundUnitToReach(unsigned int & x, unsigned int & y)const{ x = m_GroundUnitXToReach; y = m_GroundUnitYToReach;};
    glm::vec3 getPositionToReach()const{return m_PositionToReach;};
    
    //Setters
    void setSpeed(float speed){m_Speed = speed;};
    void setGroundUnitToReach(unsigned int xIndex, unsigned int yIndex){ m_GroundUnitXToReach = xIndex; m_GroundUnitYToReach = yIndex;};
    void setAction(int action){m_Action = action;};
    void setPositionToReach(glm::vec3 destination){m_PositionToReach = destination + glm::vec3(0.0,(float)game::EnemyUnit::s_ENEMYUNIT_Y_COORD,0.0);};
    
    //Public methods
    void walk();
    void autoRotateFromDirection();
    
private:
    glm::vec3 m_PositionToReach;
    unsigned int m_GroundUnitXToReach;
    unsigned int m_GroundUnitYToReach;
    float m_Speed;
    unsigned int m_Action;
};
} // namespace game
#endif // __ENEMYUNIT_HPP__
