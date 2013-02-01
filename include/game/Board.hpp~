#ifndef __BOARD_HPP__
#define __BOARD_HPP__


#include "GroundUnit.hpp"
#include <glm/glm.hpp>
#include <vector>

//Board class
namespace game {
class Board{
public:
    //Static attribute
    const static unsigned int s_GROUNDUNIT_NUMBER_WIDTH = 33;
    const static unsigned int s_GROUNDUNIT_NUMBER_HEIGHT = 33;
  
    //Constructor
    Board();
    ~Board(){};
    
    //Getters
    GroundUnit & getGroundUnitFromBoard(unsigned int x, unsigned int y);
    const GroundUnit & getGroundUnitFromBoard(unsigned int x, unsigned int y)const;
    std::vector<GroundUnit> & getGridBoard();
    const std::vector<GroundUnit> & getGridBoard()const;
    void getCenterGroundUnitCoord(unsigned int & x, unsigned int & y)const{ x = m_CentralGroundUnitX; y = m_CentralGroundUnitY;};
    void getRandomEnemyCoord(float & x, float & z)const;
    
    //Public board methods
    void computeGroundUnitsWeightFromCenter();
    void printGroundUnitsWeight();
   
private:
    //Attribute
    unsigned int m_CentralGroundUnitX;
    unsigned int m_CentralGroundUnitY;
    std::vector<GroundUnit> m_GridBoard;
};
} // namespace game
#endif // __BOARD_HPP__
