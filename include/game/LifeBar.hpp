#ifndef __LIFEBAR_HPP__
#define __LIFEBAR_HPP__

#include "../api/Entity.hpp"
#include "../api/Camera.hpp"

#include <iostream>

//GroundUnit class
namespace game {
class LifeBar: public api::Entity{
public:
    //Static attribute
    const static float s_LIFEBAR_Y_COORD = 0.6f;
    const static unsigned int s_INITIAL_LIFE = 25000;
  
    //Constructor
    LifeBar():m_Life(s_INITIAL_LIFE){
      setPosition(glm::vec3(0.0, (float)s_LIFEBAR_Y_COORD, 0.0));
      updateModel();
    };
    
    //Getters
    float getLifeRatio()const{
      return m_Life/(float)s_INITIAL_LIFE;
    }
    bool isAlive()const{
      if(m_Life == 0) return false;
      return true;
    }
    
    //Public methods
    void SubstractLife(unsigned int attackPower){
      if((int)m_Life - (int)attackPower <= 0){
	m_Life = 0;
      }
      else{
	m_Life -= attackPower;
      }
    }
    
    void update(){
	setScale(glm::vec3(m_Life/(float)s_INITIAL_LIFE, 1.0, 1.0));
	updateModel();
    }
    
    void restart(){
	m_Life = s_INITIAL_LIFE;
    }

private:
    unsigned int m_Life;
};
} // namespace game
#endif // __DEFENSEUNIT_HPP__
