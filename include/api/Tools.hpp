#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

//Global Tools for our program
namespace tools {
	//General Methods
	double distanceBetween(const glm::vec3 & p1, const glm::vec3 & p2);
	float getNorm(const glm::vec3 & vector);
	float max(const std::vector<float> & values);
	float min(const std::vector<float> & values);
	bool isDoubleEquals(double v1, double v2);
	//Transformation functions
	void transformToTable(GLfloat * tab, glm::mat4 matrix);
	void transformToMatrix(double * tab, glm::mat4 & matrix);
	//Reading in file
	void readVec3(std::istringstream& line, glm::vec3 & readVec);
	void readVec2(std::istringstream& line, glm::vec2 & readVec);
	void readFace(std::istringstream& line, std::vector<size_t> & indices,  std::vector<size_t> & uvIndices, std::vector<size_t> & normalsIndices);
	void split(const std::string& string, std::vector<std::string>& tokens, const std::string& delim);
	int getInfosFromObj(const std::string & objFileName,
						std::vector<glm::vec3> & verticesList,
						std::vector<glm::vec2> & uvList,
						std::vector<glm::vec3> & normalsList,
						std::vector<size_t> & verticesIndices,
						std::vector<size_t> & uvIndices,
						std::vector<size_t> & normalsIndices,
						bool & hasVn,
						bool & hasVt
					);
} // namespace tools
#endif // __TOOLS_HPP__
