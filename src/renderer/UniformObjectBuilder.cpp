#include "renderer/UniformObjectBuilder.hpp"
#include "api/Tools.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace renderer{
	//Building methods
	UniformObject * UniformObjectBuilder::buildTruncCone(size_t discLat){
		UniformObject * newObject = new UniformObject();
		
		double angle = 2*M_PI / discLat;
		std::vector<glm::vec3> vertices;
		std::vector<size_t> indices;
		
		double bottomRadius = 0.5;
		double topRadius = 0.25;
		
		//Filling the base vertices
		for(size_t i = 0; i < discLat; ++i){
			//First Triangle
			vertices.push_back(glm::vec3(0.0, -0.5, 0.0));
			vertices.push_back(glm::vec3(bottomRadius*cos((i)*angle), -0.5, bottomRadius*sin((i)*angle)));
			vertices.push_back(glm::vec3(bottomRadius*cos((i+1)*angle), -0.5, bottomRadius*sin((i+1)*angle)));
		}
		
		for(size_t i = 0; i < discLat; ++i){
			//Second Triangle
			vertices.push_back(glm::vec3(bottomRadius*cos((i)*angle), -0.5, bottomRadius*sin((i)*angle)));
			vertices.push_back(glm::vec3(topRadius*cos((i+1)*angle), 0.5, topRadius*sin((i+1)*angle)));
			vertices.push_back(glm::vec3(bottomRadius*cos((i+1)*angle), -0.5, bottomRadius*sin((i+1)*angle)));
			
			//Second Triangle
			vertices.push_back(glm::vec3(bottomRadius*cos((i)*angle), -0.5, bottomRadius*sin((i)*angle)));
			vertices.push_back(glm::vec3(topRadius*cos((i)*angle), 0.5, topRadius*sin((i)*angle)));
			vertices.push_back(glm::vec3(topRadius*cos((i+1)*angle), 0.5, topRadius*sin((i+1)*angle)));
		}
		
		for(size_t i = 0; i < discLat; ++i){
			//Second Triangle
			vertices.push_back(glm::vec3(0.0, 0.5, 0.0));
			vertices.push_back(glm::vec3(topRadius*cos((i+1)*angle), 0.5, topRadius*sin((i+1)*angle)));
			vertices.push_back(glm::vec3(topRadius*cos((i)*angle), 0.5, topRadius*sin((i)*angle)));
		}
		
		//Filling indices
		for(size_t i = 0; i < vertices.size(); ++i){
			indices.push_back(i);
		}
		
		std::vector<glm::vec3> normals;
		newObject->buildFromVector(vertices, indices, normals, true, false);
		return newObject;
	}
	
	UniformObject * UniformObjectBuilder::buildSphere(size_t discLong, size_t discLat, bool smooth){
		UniformObject * newObject = new UniformObject();
		
		GLfloat deltaAngleTeta = 2*M_PI/GLfloat(discLong);
		GLfloat deltaAngleOmega = M_PI/GLfloat(discLat);
		
		std::vector<glm::vec3> vertices;
		std::vector<size_t> indices;
		
		//Filling the vertices
		for(GLuint nbStage=0 ;nbStage < (GLuint)discLat ;nbStage++){ 
			GLfloat localRadius = (cos((-M_PI/2.0) + (nbStage) * deltaAngleOmega));
			GLfloat nextLocalRadius = (cos((-M_PI/2.0) + (nbStage+1) * deltaAngleOmega));
			
			for(GLuint iAngle=0 ; iAngle<(GLuint)discLong ;iAngle++){ 
				//First Triangle
				if(nbStage != 0){
				vertices.push_back(glm::vec3(0.5*localRadius*cos(iAngle*deltaAngleTeta), 0.5*localRadius*sin(iAngle*deltaAngleTeta), 0.5*sin((-M_PI/2.0) + nbStage * deltaAngleOmega)));
				vertices.push_back(glm::vec3(0.5*localRadius*cos((iAngle+1)*deltaAngleTeta), 0.5*localRadius*sin((iAngle+1)*deltaAngleTeta), 0.5*sin((-M_PI/2.0) + nbStage * deltaAngleOmega)));
				vertices.push_back(glm::vec3(0.5*nextLocalRadius*cos((iAngle+1)*deltaAngleTeta), 0.5*nextLocalRadius*sin((iAngle+1)*deltaAngleTeta), .5*sin((-M_PI/2.0) + (nbStage+1) * deltaAngleOmega)));
				}
				//Second Triangle
				if(nbStage != discLat -1){
				vertices.push_back(glm::vec3(0.5*localRadius*cos(iAngle*deltaAngleTeta), 0.5*localRadius*sin(iAngle*deltaAngleTeta), 0.5*sin((-M_PI/2.0) + nbStage * deltaAngleOmega)));
				vertices.push_back(glm::vec3(0.5*nextLocalRadius*cos((iAngle+1)*deltaAngleTeta), 0.5*nextLocalRadius*sin((iAngle+1)*deltaAngleTeta), 0.5*sin((-M_PI/2.0) + (nbStage+1) * deltaAngleOmega)));
				vertices.push_back(glm::vec3(0.5*nextLocalRadius*cos(iAngle*deltaAngleTeta), 0.5*nextLocalRadius*sin(iAngle*deltaAngleTeta), 0.5*sin((-M_PI/2.0) + (nbStage+1) * deltaAngleOmega)));
				}
			}
		}
		//Filling the indices
		for(size_t iIndex = 0; iIndex < vertices.size(); iIndex++){
			indices.push_back(iIndex);
		}
		
		std::vector<glm::vec3> normals;
		newObject->buildFromVector(vertices, indices, normals, true, smooth);
		return newObject;
	}
	
	UniformObject * UniformObjectBuilder::buildCube(){
		UniformObject * newObject = new UniformObject();
		
		std::vector<glm::vec3> vertices;
		std::vector<size_t> indices;
		
		//First Face
		vertices.push_back(glm::vec3(-0.5,-0.5,0.5));
		vertices.push_back(glm::vec3(0.5,-0.5,0.5));
		vertices.push_back(glm::vec3(0.5,0.5,0.5));
		
		vertices.push_back(glm::vec3(-0.5,-0.5,0.5));
		vertices.push_back(glm::vec3(0.5,0.5,0.5));
		vertices.push_back(glm::vec3(-0.5,0.5,0.5));
		
		//Second Face
		vertices.push_back(glm::vec3(0.5,-0.5,0.5));
		vertices.push_back(glm::vec3(0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(0.5,0.5,-0.5));
		
		vertices.push_back(glm::vec3(0.5,-0.5,0.5));
		vertices.push_back(glm::vec3(0.5,0.5,-0.5));
		vertices.push_back(glm::vec3(0.5,0.5,0.5));
		
		//Third Face
		vertices.push_back(glm::vec3(0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(-0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(-0.5,0.5,-0.5));
		
		vertices.push_back(glm::vec3(0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(-0.5,0.5,-0.5));
		vertices.push_back(glm::vec3(0.5,0.5,-0.5));
		
		//Forth Face
		vertices.push_back(glm::vec3(-0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(-0.5,-0.5,0.5));
		vertices.push_back(glm::vec3(-0.5,0.5,0.5));
		
		vertices.push_back(glm::vec3(-0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(-0.5,0.5,0.5));
		vertices.push_back(glm::vec3(-0.5,0.5,-0.5));
		
		//Top Face
		vertices.push_back(glm::vec3(-0.5,0.5,-0.5));
		vertices.push_back(glm::vec3(0.5,0.5,0.5));
		vertices.push_back(glm::vec3(0.5,0.5,-0.5));
		
		vertices.push_back(glm::vec3(-0.5,0.5,-0.5));
		vertices.push_back(glm::vec3(-0.5,0.5,0.5));
		vertices.push_back(glm::vec3(0.5,0.5,0.5));
		
		//Bottom Face
		vertices.push_back(glm::vec3(-0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(0.5,-0.5,0.5));
		
		vertices.push_back(glm::vec3(-0.5,-0.5,-0.5));
		vertices.push_back(glm::vec3(0.5,-0.5,0.5));
		vertices.push_back(glm::vec3(-0.5,-0.5,0.5));
		
		for(size_t i = 0; i < vertices.size(); ++i){
			indices.push_back(i);
		}
		
		std::vector<glm::vec3> normals;
		newObject->buildFromVector(vertices, indices, normals, true, false);
		return newObject;
	}
	
	//Creating a sphere
	UniformObject * UniformObjectBuilder::buildCylinder(size_t discLat){
		
		UniformObject * newObject = new UniformObject();
		
		double angle = 2*M_PI / discLat;
		std::vector<glm::vec3> vertices;
		std::vector<size_t> indices;

		//Filling the base vertices
		for(size_t i = 0; i < discLat; ++i){
			//First Triangle
			vertices.push_back(glm::vec3(0.0, -0.5, 0.0));
			vertices.push_back(glm::vec3(0.5*cos((i)*angle), -0.5, 0.5*sin((i)*angle)));
			vertices.push_back(glm::vec3(0.5*cos((i+1)*angle), -0.5, 0.5*sin((i+1)*angle)));
		}
		
		for(size_t i = 0; i < discLat; ++i){
			//Second Triangle
			vertices.push_back(glm::vec3(0.5*cos((i)*angle), -0.5, 0.5*sin((i)*angle)));
			vertices.push_back(glm::vec3(0.5*cos((i+1)*angle), 0.5, 0.5*sin((i+1)*angle)));
			vertices.push_back(glm::vec3(0.5*cos((i+1)*angle), -0.5, 0.5*sin((i+1)*angle)));
			
			//Second Triangle
			vertices.push_back(glm::vec3(0.5*cos((i)*angle), -0.5, 0.5*sin((i)*angle)));
			vertices.push_back(glm::vec3(0.5*cos((i)*angle), 0.5, 0.5*sin((i)*angle)));
			vertices.push_back(glm::vec3(0.5*cos((i+1)*angle), 0.5, 0.5*sin((i+1)*angle)));
		}
		
		for(size_t i = 0; i < discLat; ++i){
			//Second Triangle
			vertices.push_back(glm::vec3(0.0, 0.5, 0.0));
			vertices.push_back(glm::vec3(0.5*cos((i+1)*angle), 0.5, 0.5*sin((i+1)*angle)));
			vertices.push_back(glm::vec3(0.5*cos((i)*angle), 0.5, 0.5*sin((i)*angle)));
		}
		
		//Filling indices
		for(size_t i = 0; i < vertices.size(); ++i){
			indices.push_back(i);
		}
		
		std::vector<glm::vec3> normals;
		newObject->buildFromVector(vertices, indices, normals, true, false);
		return newObject;
	}
	
	UniformObject * UniformObjectBuilder::buildTore(size_t discLong, size_t discLat, bool smooth){
		UniformObject * newObject = new UniformObject();
		
		GLfloat horizontalAngle = 2*M_PI/GLfloat(discLong);
		GLfloat verticalAngle = 2*M_PI/GLfloat(discLat);
		
		std::vector<glm::vec3> vertices;
		std::vector<size_t> indices;
		
		//Filling the vertices
		for(GLuint horizontal=0 ;horizontal < (GLuint)discLat ;horizontal++){ 
			
			double radius = 0.22;
			
			glm::vec3 center(0.5 * cos(horizontalAngle*horizontal), 0.0, 0.5 * sin(horizontalAngle*horizontal));
			glm::vec3 direction = glm::normalize(center);
			
			glm::vec3 nextCenter(0.5 * cos(horizontalAngle*(horizontal+1)), 0.0, 0.5 * sin(horizontalAngle*(horizontal+1)));
			glm::vec3 nextDirection = glm::normalize(nextCenter);
			
			for(GLuint vertical =0 ; vertical <(GLuint)discLong ; vertical++){ 
				//First Triangle
				vertices.push_back(glm::vec3(center.x + radius * direction.x * cos(vertical*verticalAngle), center.y + radius*sin(vertical*verticalAngle), center.z + radius * direction.z * cos(vertical*verticalAngle)));
				vertices.push_back(glm::vec3(nextCenter.x + radius * nextDirection.x * cos((vertical+1)*verticalAngle), nextCenter.y + radius*sin((vertical+1)*verticalAngle), nextCenter.z + radius * nextDirection.z * cos((vertical+1)*verticalAngle)));
				vertices.push_back(glm::vec3(nextCenter.x + radius * nextDirection.x * cos(vertical*verticalAngle), nextCenter.y + radius*sin(vertical*verticalAngle), nextCenter.z + radius * nextDirection.z * cos(vertical*verticalAngle)));
	
				//Second Triangle
				vertices.push_back(glm::vec3(center.x + radius * direction.x * cos(vertical*verticalAngle), center.y + radius*sin(vertical*verticalAngle), center.z + radius * direction.z * cos(vertical*verticalAngle)));
				vertices.push_back(glm::vec3(center.x + radius * direction.x * cos((vertical+1)*verticalAngle), center.y + radius*sin((vertical+1)*verticalAngle), center.z + radius * direction.z * cos((vertical+1)*verticalAngle)));
				vertices.push_back(glm::vec3(nextCenter.x + radius * nextDirection.x * cos((vertical+1)*verticalAngle), nextCenter.y + radius*sin((vertical+1)*verticalAngle), nextCenter.z + radius * nextDirection.z * cos((vertical+1)*verticalAngle)));
			}
		}
		//Filling the indices
		for(size_t iIndex = 0; iIndex < vertices.size(); iIndex++){
			indices.push_back(iIndex);
		}
		std::vector<glm::vec3> normals;
		newObject->buildFromVector(vertices, indices, normals, true, smooth);
		return newObject;
	}
	
	UniformObject * UniformObjectBuilder::buildFromObj(const std::string & objFile, bool smooth){
		UniformObject * newObject = new UniformObject();

		//Setting some variables
		bool hasVt=false;
		bool hasVn=false;
		std::vector<glm::vec3> verticesList;
		std::vector<glm::vec2> uvsList;
		std::vector<glm::vec3> normalsList;
		
		std::vector<glm::vec3> finalVertices;
		std::vector<glm::vec2> finalUvs;
		std::vector<glm::vec3> finalNormals;
		std::vector<size_t> finalIndices;
		
		std::vector<size_t> verticeIndices;
		std::vector<size_t> uvIndices;
		std::vector<size_t> normalIndices;
		
		int load = tools::getInfosFromObj(objFile,
										   verticesList,
										   uvsList,
										   normalsList,
										   verticeIndices,
										   uvIndices,
									       normalIndices,
									       hasVn,
										   hasVt);
		
		if(load){
			std::cout << "Impossible to read the file " << objFile << std::endl;
			delete newObject;
			return NULL;
		}
		
		for(size_t i = 0; i < verticeIndices.size(); ++i){
			finalVertices.push_back(verticesList[verticeIndices[i]]);
			finalUvs.push_back(uvsList[uvIndices[i]]);
			finalNormals.push_back(normalsList[normalIndices[i]]);
			finalIndices.push_back(i);
		}
		
		//Filling our final vector
		if (!hasVn) 
		{
			std::cout << "Error : No normals for " << objFile << std::endl;
			delete newObject;
			return NULL;
		}
		newObject->buildFromVector(finalVertices, finalIndices, finalNormals, false, smooth);
		if (hasVt){ 
			newObject->setUvs(finalUvs);
		}
		std::cout << "Object " << objFile << " loaded " << std::endl;
		return newObject;
	}
}