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
	 for(int i = 0; i <=1; ++i){
	  for(int j = -1; j <=1; j= j+2){
	    unsigned int groundUnitX, groundUnitZ;
	    localGroundUnit->getGroundUnitCoord(groundUnitX, groundUnitZ);
	    int indiceX, indiceZ;
	    if(i%2 ==0){
	      indiceX = groundUnitX + j;
	      indiceZ = groundUnitZ;
	    }
	    else{
	      indiceX = groundUnitX;
	      indiceZ = groundUnitZ + j;
	    }
	    if(indiceX >= 0 && indiceZ >= 0 && indiceX < int(s_GROUNDUNIT_NUMBER_WIDTH) && indiceZ < int(s_GROUNDUNIT_NUMBER_HEIGHT)){
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
    
    void Board::getNextGroundUnit(const GroundUnit * currentGroundUnit, std::vector<GroundUnit*> & possibleGroundUnitToReach){
	unsigned int currentX = 0;
	unsigned int currentZ = 0;
	currentGroundUnit->getGroundUnitCoord(currentX, currentZ);
	
	//Selecting the neighbour index in board
	std::vector<unsigned int> neighbourX;
	std::vector<unsigned int> neighbourZ;
	if(currentX != 0) neighbourX.push_back(currentX - 1);
	if(currentX != s_GROUNDUNIT_NUMBER_WIDTH - 1) neighbourX.push_back(currentX+1);
	if(currentZ != 0) neighbourZ.push_back(currentZ - 1);
	if(currentZ != s_GROUNDUNIT_NUMBER_HEIGHT - 1) neighbourZ.push_back(currentZ+1);
	
	//Setting the min to the weight of the current groundunit
	int minWeight = currentGroundUnit->getWeight();
	
	//Searching on the X neighbours
	for(unsigned int i = 0; i < neighbourX.size(); ++i){
	  GroundUnit * neighbourGroundUnit = getGroundUnitFromBoard(neighbourX[i], currentZ);
	  if(neighbourGroundUnit->getWeight() < minWeight && !neighbourGroundUnit->isOccupied()){
	    possibleGroundUnitToReach.clear();
	    minWeight = neighbourGroundUnit->getWeight();
	    possibleGroundUnitToReach.push_back(neighbourGroundUnit);
	  }
	  else if(neighbourGroundUnit->getWeight() == minWeight){
	    possibleGroundUnitToReach.push_back(neighbourGroundUnit);
	  }
	}
	
	//Searching on the Z neighbours
	for(unsigned int i = 0; i < neighbourZ.size(); ++i){
	  GroundUnit * neighbourGroundUnit = getGroundUnitFromBoard(currentX, neighbourZ[i]);
	  if(neighbourGroundUnit->getWeight() < minWeight && !neighbourGroundUnit->isOccupied()){
	    possibleGroundUnitToReach.clear();
	    minWeight = neighbourGroundUnit->getWeight();
	    possibleGroundUnitToReach.push_back(neighbourGroundUnit);
	  }
	  else if(neighbourGroundUnit->getWeight() == minWeight){
	    possibleGroundUnitToReach.push_back(neighbourGroundUnit);
	  }
	}
    }
}//namespace game