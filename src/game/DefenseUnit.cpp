#include "../include/game/DefenseUnit.hpp"

namespace game{
  
  void DefenseUnit::freeGroundUnit(){
      m_RelatedGroundUnit->setOccupied(false);
      m_RelatedGroundUnit->setWeight(0);
  }
  
}//namespace game