#ifndef __ENEMYUNIT_HPP__
#define __ENEMYUNIT_HPP__

#include "../api/Entity.hpp"
#include "../game/GroundUnit.hpp"

#include <glm/glm.hpp>

#define ENEMY_CLASSIC 1
#define ENEMY_BOSS 2

#define ENEMY_WAITING 1
#define ENEMY_WALKING 2
#define ENEMY_FIRING 3

//GroundUnit class
namespace game {
class EnemyUnit : public api::Entity{
public:
  
    //Static attribute
    const static float s_ENEMYUNIT_Y_COORD = 0.02f;
    const static unsigned int s_ENEMYUNIT_WALK_ANIM_SPEED = 5;
    const static unsigned int s_ENEMYUNIT_WALK_ANIM_TOTAL_FRAME = 10;
    const static unsigned int s_ENEMYUNIT_ATTACK_ANIM_SPEED = 5;
    const static unsigned int s_ENEMYUNIT_ATTACK_ANIM_TOTAL_FRAME = 10;
    
    //Constructor
    EnemyUnit(unsigned int type, GroundUnit * groundUnit, float speed);
    virtual ~EnemyUnit(){};
    
    //Getters
    unsigned int getAction()const{ return m_Action;};
    float getSpeed()const{ return m_Speed;};
    GroundUnit * getGroundUnitToReach()const{return m_GroundUnitToReach;};
    unsigned int getWalkAnimationFrameID()const{return m_WalkFrameAnimationCounter;}
    unsigned int getAttackAnimationFrameID()const{return m_AttackFrameAnimationCounter;}
    unsigned int getType()const{return m_Type;};
    unsigned int getForce()const{return m_Force;};
    bool shoot(){--m_Life; return m_Life <= 0;};
    
    //Setters
    void setSpeed(float speed){m_Speed = speed;};
    void setAction(int action){m_Action = action;};
    bool setGroundUnitToReach(GroundUnit* groundUnitToReach);
    
    //Public methods
    void walk();
    void autoRotateFromDirection(glm::vec3 destinationPosition);
    void autoRotateForFire();
    void updateCounter();
    
private:
    GroundUnit * m_GroundUnitToReach;
    float m_Speed;
    unsigned int m_Type;
    unsigned int m_Force;
    unsigned int m_Life;
    unsigned int m_Action;
    unsigned int m_AttackFrameAnimationCounter;
    unsigned int m_WalkFrameAnimationCounter;
    unsigned int m_LoopCounter;
};
} // namespace game
#endif // __ENEMYUNIT_HPP__
