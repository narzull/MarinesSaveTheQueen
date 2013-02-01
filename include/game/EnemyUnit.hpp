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
    //Constructor
    EnemyUnit(glm::vec3 currentPosition, float speed);
    virtual ~EnemyUnit(){};
    
    //Getters
    unsigned int getAction()const{ return m_Action;};
    
    //Public methods
    void walk();
    void autoRotateFromDirection();
    
private:
  
    glm::vec3 m_DestinationPosition;
    float m_Speed;
    unsigned int m_Action;
};
} // namespace game
#endif // __ENEMYUNIT_HPP__
