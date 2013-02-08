#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "../api/Entity.hpp"
#include <vector>

//GroundUnit class
namespace game {
  
class Ray : public api::Entity{
public :
  Ray(unsigned int beginningX, unsigned int beginningZ, unsigned int endingX, unsigned int endingZ, glm::vec3 position, glm::vec3 angle):Entity(position, angle){
    m_BeginningCoord.first = beginningX;
    m_BeginningCoord.second = beginningZ;
    m_EndingCoord.first = endingX;
    m_EndingCoord.second = endingZ;
    autoComputeLenth();
    updateModel();
  };
  
  //Getters
  std::pair<unsigned int, unsigned int> getBeginningCoord()const{return m_BeginningCoord;};
  std::pair<unsigned int, unsigned int> getEndingCoord()const{return m_EndingCoord;};
  
  //Public methods
  void changeRayEndingCoord(std::pair<unsigned int, unsigned int> newEndingCoord);
  
private:
  void autoComputeLenth();
  
  std::pair<unsigned int, unsigned int> m_BeginningCoord;
  std::pair<unsigned int, unsigned int> m_EndingCoord;
  unsigned int m_Length;
};
} // namespace game
#endif // __DEFENSEUNIT_HPP__
