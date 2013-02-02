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
    ~Board();
    
    //Getters
    //Get Ground Unit
    GroundUnit * getGroundUnitFromBoard(unsigned int x, unsigned int z);
    const GroundUnit * getGroundUnitFromBoard(unsigned int x, unsigned int z)const;
    //Get Grid Board
    std::vector<GroundUnit*> & getGridBoard();
    const std::vector<GroundUnit*> & getGridBoard()const;
    //Get Center Ground Unit 
    const GroundUnit * getCentralGroundUnit()const;
    //Get Random Ground Unit
    GroundUnit * getRandomGroundUnit();
    const GroundUnit * getRandomGroundUnit()const;
    //Get Next Ground Unit
    void getNextGroundUnit(const GroundUnit * currentGroundUnit, std::vector<GroundUnit*> & possibleGroundUnitToReach);
    
    //Public board methods
    void computeGroundUnitsWeightFromCenter();
    void printGroundUnitsWeight();
    void printGroundUnitsOccupation();
   
private:
    //Attribute
    unsigned int m_CentralGroundUnitX;
    unsigned int m_CentralGroundUnitZ;
    std::vector<GroundUnit*> m_GridBoard;
};
} // namespace game
#endif // __BOARD_HPP__
