#include "../include/game/Ray.hpp"

#include <iostream>
namespace game{
  void Ray::autoComputeLenth(){
    int deltaX = abs(m_BeginningCoord.first - m_EndingCoord.first);
    int deltaZ = abs(m_BeginningCoord.second - m_EndingCoord.second);
    m_Length = std::max(deltaX, deltaZ);
    std::cout << "ray length : " << m_Length << std::endl;
  }
  
   void Ray::changeRayEndingCoord(std::pair<unsigned int, unsigned int> newEndingCoord){
      m_EndingCoord = newEndingCoord;
      autoComputeLenth();
   }
  
}//namespace game