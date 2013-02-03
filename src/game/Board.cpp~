#include "../include/game/Board.hpp"

#include <iostream>
#include <stack>

namespace game{
    //**********************
    //Constructor
    //**********************
    
    Board::Board():m_CentralGroundUnitX((s_GROUNDUNIT_NUMBER_WIDTH - 1)/2), m_CentralGroundUnitZ((s_GROUNDUNIT_NUMBER_HEIGHT - 1)/2){
      //Checking the grid number
      if(s_GROUNDUNIT_NUMBER_WIDTH%2 != 1) std::cout << "Be carefull, the number of GroundUnit on width is not odd, the board will not be balanced" << std::endl;
      if(s_GROUNDUNIT_NUMBER_HEIGHT%2 != 1) std::cout << "Be carefull, the number of GroundUnit on height is not odd, the board will not be balanced" << std::endl;
      //Creating the GroundUnit
      for(unsigned int i = 0; i < s_GROUNDUNIT_NUMBER_WIDTH * s_GROUNDUNIT_NUMBER_HEIGHT; ++i){
	m_GridBoard.push_back(new GroundUnit(i%s_GROUNDUNIT_NUMBER_WIDTH, i/s_GROUNDUNIT_NUMBER_WIDTH, m_CentralGroundUnitX, m_CentralGroundUnitZ));
      }
    };
    
    Board::~Board(){
      for(unsigned int i = 0; i < m_GridBoard.size(); ++i){
	delete m_GridBoard[i];
      }
    }
    
    //************************
    //Getters
    //************************
    //Get Ground Unit
    GroundUnit * Board::getGroundUnitFromBoard(unsigned int x, unsigned int z){
      return m_GridBoard[z * s_GROUNDUNIT_NUMBER_WIDTH + x];
    }
    
    const GroundUnit * Board::getGroundUnitFromBoard(unsigned int x, unsigned int z)const{
      return m_GridBoard[z * s_GROUNDUNIT_NUMBER_WIDTH + x];
    }
    
    //Get Grid Board
    std::vector<GroundUnit*> & Board::getGridBoard(){
      return m_GridBoard;
    }
    
    const std::vector<GroundUnit*> & Board::getGridBoard()const{
      return m_GridBoard;
    }
    
    //Get Center Ground Unit 
    const GroundUnit * Board::getCentralGroundUnit()const{
      return getGroundUnitFromBoard(m_CentralGroundUnitX, m_CentralGroundUnitZ);
    }
    
    //Get Random Ground Unit 
    const GroundUnit * Board::getRandomGroundUnit()const{
      unsigned int indiceX = rand()%s_GROUNDUNIT_NUMBER_WIDTH;
      unsigned int indiceY = rand()%s_GROUNDUNIT_NUMBER_HEIGHT;
      return getGroundUnitFromBoard(indiceX, indiceY);
    }
    
    GroundUnit * Board::getRandomGroundUnit(){
      unsigned int indiceX = rand()%s_GROUNDUNIT_NUMBER_WIDTH;
      unsigned int indiceY = rand()%s_GROUNDUNIT_NUMBER_HEIGHT;
      return getGroundUnitFromBoard(indiceX, indiceY);
    }
    
    //***************************
    //Other Public Board Methods
    //***************************
    
    void Board::computeGroundUnitsWeightFromCenter(){
      std::stack<GroundUnit*> stack;
      stack.push(getGroundUnitFromBoard(m_CentralGroundUnitX, m_CentralGroundUnitZ));
      while(!stack.empty()){
	 GroundUnit * localGroundUnit = stack.top();
	 stack.pop();
	 for(int i = -1; i <=1; ++i){
	  for(int j = -1; j <=1; ++j){
	    unsigned int groundUnitX, groundUnitZ;
	    localGroundUnit->getGroundUnitCoord(groundUnitX, groundUnitZ);
	    int indiceX, indiceZ;
	    indiceX = groundUnitX + i;
	    indiceZ = groundUnitZ + j;
	    
	    if(indiceX >= 0 && indiceZ >= 0 && indiceX < int(s_GROUNDUNIT_NUMBER_WIDTH) && indiceZ < int(s_GROUNDUNIT_NUMBER_HEIGHT)){
	      if(indiceX != (int)groundUnitX || indiceZ != (int)groundUnitZ){
		GroundUnit * neighbourGroundUnit = getGroundUnitFromBoard(indiceX, indiceZ);
		if(neighbourGroundUnit->getWeight() > localGroundUnit->getWeight() + 1 && neighbourGroundUnit->getWeight() != -1){
		  neighbourGroundUnit->setWeight(localGroundUnit->getWeight()+1);
		  stack.push(neighbourGroundUnit);
		}
	      }
	    }
	  }
	 }
      }
    }
    
    void Board::printGroundUnitsWeight(){
     for(unsigned int i = 0; i < s_GROUNDUNIT_NUMBER_HEIGHT; ++i){
      for(unsigned int j = 0; j < s_GROUNDUNIT_NUMBER_WIDTH; ++j){
	std::cout << getGroundUnitFromBoard(j, i)->getWeight() << " | ";
	if(j == s_GROUNDUNIT_NUMBER_WIDTH-1) std::cout << std::endl;
      }
     }
    }
    
    void Board::printGroundUnitsOccupation(){
     for(unsigned int i = 0; i < s_GROUNDUNIT_NUMBER_HEIGHT; ++i){
      for(unsigned int j = 0; j < s_GROUNDUNIT_NUMBER_WIDTH; ++j){
	std::cout << getGroundUnitFromBoard(j, i)->isOccupied() << " | ";
	if(j == s_GROUNDUNIT_NUMBER_WIDTH-1) std::cout << std::endl;
      }
     }
    }
    
    bool Board::getNextGroundUnit(const GroundUnit * currentGroundUnit, std::vector<GroundUnit*> & possibleGroundUnitToReach){
	unsigned int currentX = 0;
	unsigned int currentZ = 0;
	bool isBlocked = false;
	currentGroundUnit->getGroundUnitCoord(currentX, currentZ);
	//Setting the min to the weight of the current groundunit
	int minWeight = currentGroundUnit->getWeight();
	//Searching on the X neighbours
	for(int i = -1; i <= 1; ++i){
	  for(int j = -1; j <= 1; ++j){
	    int xIndex = currentX + i;
	    int zIndex = currentZ + j;
	    
	    if(xIndex >= 0 && zIndex >= 0 && (unsigned int)xIndex < s_GROUNDUNIT_NUMBER_WIDTH && (unsigned int)zIndex < s_GROUNDUNIT_NUMBER_HEIGHT && ((unsigned int)xIndex != currentX || (unsigned int)zIndex != currentZ)){
	      GroundUnit * neighbourGroundUnit = getGroundUnitFromBoard(xIndex, zIndex);
	      if(neighbourGroundUnit->getWeight() < minWeight && !neighbourGroundUnit->isOccupied() && neighbourGroundUnit->getWeight() > 0){
		possibleGroundUnitToReach.clear();
		minWeight = neighbourGroundUnit->getWeight();
		possibleGroundUnitToReach.push_back(neighbourGroundUnit);
	      }
	      else if(neighbourGroundUnit->getWeight() == minWeight){
		possibleGroundUnitToReach.push_back(neighbourGroundUnit);
	      }
	    }
	  }
	}
	if(currentGroundUnit->getWeight() == minWeight) isBlocked = true;
	return isBlocked;
    }
}//namespace game