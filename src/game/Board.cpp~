#include "../include/game/Board.hpp"

#include <iostream>
#include <stack>

namespace game{
    //Constructor
    Board::Board():m_CentralGroundUnitX((s_GROUNDUNIT_NUMBER_WIDTH - 1)/2), m_CentralGroundUnitY((s_GROUNDUNIT_NUMBER_HEIGHT - 1)/2){
      //Checking the grid number
      if(s_GROUNDUNIT_NUMBER_WIDTH%2 != 1) std::cout << "Be carefull, the number of GroundUnit on width is not odd, the board will not be balanced" << std::endl;
      if(s_GROUNDUNIT_NUMBER_HEIGHT%2 != 1) std::cout << "Be carefull, the number of GroundUnit on height is not odd, the board will not be balanced" << std::endl;
      //Creating the GroundUnit
      for(unsigned int i = 0; i < s_GROUNDUNIT_NUMBER_WIDTH * s_GROUNDUNIT_NUMBER_HEIGHT; ++i){
	m_GridBoard.push_back(GroundUnit(i%s_GROUNDUNIT_NUMBER_WIDTH, i/s_GROUNDUNIT_NUMBER_WIDTH, m_CentralGroundUnitX, m_CentralGroundUnitY));
      }
    };
    
    //Getters
    GroundUnit & Board::getGroundUnitFromBoard(unsigned int x, unsigned int y){
      return m_GridBoard[y * s_GROUNDUNIT_NUMBER_WIDTH + x];
    }
    
    const GroundUnit & Board::getGroundUnitFromBoard(unsigned int x, unsigned int y)const{
      return m_GridBoard[y * s_GROUNDUNIT_NUMBER_WIDTH + x];
    }
    
    std::vector<GroundUnit> & Board::getGridBoard(){
      return m_GridBoard;
    }
    
    const std::vector<GroundUnit> & Board::getGridBoard()const{
      return m_GridBoard;
    }
    
    //Public board methods
    void Board::computeGroundUnitsWeightFromCenter(){
      std::stack<GroundUnit*> stack;
      stack.push(&getGroundUnitFromBoard(m_CentralGroundUnitX, m_CentralGroundUnitY));
      while(!stack.empty()){
	 GroundUnit * localGroundUnit = stack.top();
	 stack.pop();
	 for(int i = 0; i <=1; ++i){
	  for(int j = -1; j <=1; j= j+2){
	    unsigned int groundUnitX, groundUnitY;
	    localGroundUnit->getGroundUnitCoord(groundUnitX, groundUnitY);
	    int indiceX, indiceY;
	    if(i%2 ==0){
	      indiceX = groundUnitX + j;
	      indiceY = groundUnitY;
	    }
	    else{
	      indiceX = groundUnitX;
	      indiceY = groundUnitY + j;
	    }
	    if(indiceX >= 0 && indiceY >= 0 && indiceX < int(s_GROUNDUNIT_NUMBER_WIDTH) && indiceY < int(s_GROUNDUNIT_NUMBER_HEIGHT)){
	      GroundUnit * neighbourGroundUnit = &getGroundUnitFromBoard(indiceX, indiceY);
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
	std::cout << getGroundUnitFromBoard(j, i).getWeight() << " | ";
	if(j == s_GROUNDUNIT_NUMBER_WIDTH-1) std::cout << std::endl;
      }
     }
    }
    
    void Board::getRandomEnemyCoord(float & x, float & z)const{
      bool unitPlaced = false;
      do{
	unsigned int caseIdX = rand()%s_GROUNDUNIT_NUMBER_WIDTH;
	unsigned int caseIdY = rand()%s_GROUNDUNIT_NUMBER_HEIGHT;
	if(caseIdX != m_CentralGroundUnitX && caseIdY != m_CentralGroundUnitY){
	  unitPlaced = true;
	  glm::vec3 pos = getGroundUnitFromBoard(caseIdX, caseIdY).getPosition();
	  x = pos.x;
	  z = pos.z;
	}
      }while(!unitPlaced);
    }
}//namespace game