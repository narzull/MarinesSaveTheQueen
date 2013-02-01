#ifndef __UNIFORMOBJECTBUILDER__HPP__
#define __UNIFORMOBJECTBUILDER__HPP__

#include "UniformObject.hpp"
#include <string>

namespace renderer{

class UniformObjectBuilder{
	
public:
	//Constructor
	UniformObjectBuilder(){};
	//Building methods
	UniformObject * buildFromObj(const std::string & objFile, bool smooth);
	UniformObject * buildTruncCone(size_t discLat);
	UniformObject * buildSphere(size_t discLong, size_t discLat, bool smooth);
	UniformObject * buildCube();
	UniformObject * buildCylinder(size_t discLat);
	UniformObject * buildTore(size_t discLong, size_t discLat, bool smooth);
};

}

#endif //uniformobjectbuilder.hpp