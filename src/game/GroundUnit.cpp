#include "../include/game/GroundUnit.hpp"
#include <iostream>
namespace game{
  GroundUnit::GroundUnit(unsigned int X, unsigned int Y, unsigned int centralX, unsigned int centralY):m_Type(GRASS_TYPE), m_Weight(5000), m_IsOccupied(false){
    m_Coord.first = X;
    m_Coord.second = Y;
    int deltaX = m_Coord.first - centralX;
    int deltaY = m_Coord.second - centralY;
    if(abs(deltaX) <= 2 && abs(deltaY) <= 2) m_Type = ROCK_TYPE;
    if(abs(deltaX) == 0 && abs(deltaY) == 0) m_Weight = 0;
    glm::vec3 finalPosition(deltaX * s_GROUNDUNIT_WIDTH, 0.0, deltaY * s_GROUNDUNIT_HEIGHT);
    setPosition(finalPosition);
    updateModel();
  }
}//namespace game