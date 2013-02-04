#ifndef __GROUNDUNIT_HPP__
#define __GROUNDUNIT_HPP__

#include "../api/Entity.hpp"
#include <iostream>

#define GRASS_TYPE 1
#define ROCK_TYPE 2

//GroundUnit class
namespace game {
class GroundUnit : public api::Entity{
public:
    //Static attribute
    const static float s_GROUNDUNIT_WIDTH = 0.5;
    const static float s_GROUNDUNIT_HEIGHT = 0.5;
  
    //Constructor
    GroundUnit(unsigned int X, unsigned int Y, unsigned int centralX, unsigned int centralY);
    virtual ~GroundUnit(){};
    
    //Getters
    std::pair<unsigned int, unsigned int> getGroundUnitCoord()const{return m_Coord;};
    unsigned int getType()const{return m_Type;};
    int getWeight()const{return m_Weight;};
    bool isOccupied()const{ return m_IsOccupied;};
    
    //Setters
    void setWeight(int weight){ m_Weight = weight;};
    void setOccupied(bool occupation){m_IsOccupied = occupation;};
    
private:
    std::pair<unsigned int, unsigned int> m_Coord;
    unsigned int m_Type;
    int m_Weight;
    bool m_IsOccupied;
};
} // namespace game
#endif // __GROUNDUNIT_HPP__
