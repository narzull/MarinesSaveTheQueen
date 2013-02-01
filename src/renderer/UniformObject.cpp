#include "renderer/UniformObject.hpp"
#include <iostream>

namespace renderer{
	
	void UniformObject::draw(GLenum primitive) const{
		glBindVertexArray(m_VAO);
		glDrawElements(primitive,m_IndicesNumber, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	
	void UniformObject::computeNormals(const std::vector<glm::vec3> & verticesVector, const std::vector<size_t> & indicesVector, std::vector<glm::vec3> & normalsVector){

		for(size_t i = 0; i < indicesVector.size(); i+=3){
			glm::vec3 A = verticesVector[indicesVector[i]];
			glm::vec3 B = verticesVector[indicesVector[i+1]];
			glm::vec3 C = verticesVector[indicesVector[i+2]];
			
			glm::vec3 normal1 = glm::cross(B-A, C-A);
			normal1 = glm::normalize(normal1);
			glm::vec3 normal2 = glm::cross(C-B, A-B);
			normal2 = glm::normalize(normal2);
			glm::vec3 normal3 = glm::cross(A-C, B-C);
			normal3 = glm::normalize(normal3);
			
			normalsVector.push_back(normal1);
			normalsVector.push_back(normal2);
			normalsVector.push_back(normal3);
		}
	}
	
	void UniformObject::smoothNormals(const std::vector<glm::vec3> & verticesVector, const std::vector<size_t> & indicesVector, std::vector<glm::vec3> & normalVector){
		std::vector<size_t> indexSmoothNormal;
		for(size_t i = 0; i < indicesVector.size(); ++i){
			bool alreadySmooth = false;
			for(size_t j = 0; j < indexSmoothNormal.size(); ++j){
				if(indexSmoothNormal[j] == i) alreadySmooth = true;
			}
			if(!alreadySmooth){
				glm::vec3 normalBuffer = normalVector[indicesVector[i]];
				size_t normalCount = 1;
				std::vector<size_t> localIndexSmoothNormal;
				for(size_t j = i + 1; j < indicesVector.size(); ++j){
					if(fabs(verticesVector[indicesVector[i]].x - verticesVector[indicesVector[j]].x) < 0.00001 &&
						fabs(verticesVector[indicesVector[i]].y - verticesVector[indicesVector[j]].y) < 0.00001 &&
						fabs(verticesVector[indicesVector[i]].z - verticesVector[indicesVector[j]].z) < 0.00001){
						normalBuffer += normalVector[indicesVector[j]];
						++normalCount;
						localIndexSmoothNormal.push_back(j);
					}
				}
				normalBuffer /= normalCount;
				for(size_t j = 0; j < localIndexSmoothNormal.size(); ++j){
					normalVector[localIndexSmoothNormal[j]] = normalBuffer;
					indexSmoothNormal.push_back(localIndexSmoothNormal[j]);
				}
				indexSmoothNormal.push_back(i);
				normalVector[indicesVector[i]] = normalBuffer;
			}
		}
	}
	
	void UniformObject::buildFromVector(const std::vector<glm::vec3> & verticesVector, const std::vector<size_t> & indicesVector, std::vector<glm::vec3> & normalsVector,  bool autoNormals, bool smooth){
		
		if(autoNormals) computeNormals(verticesVector, indicesVector, normalsVector);
		if(smooth)smoothNormals(verticesVector, indicesVector, normalsVector);
		
		const unsigned int nbVertices = verticesVector.size() * 4;
		const unsigned int nbIndices = indicesVector.size();
		
		m_IndicesNumber = nbIndices;
		
		GLfloat vertices[nbVertices];
		GLuint indices[nbIndices];
		GLfloat normals[nbVertices];
		
		for(size_t i = 0; i < verticesVector.size(); ++i){
			vertices[4 * i + 0] = verticesVector[i].x;
			vertices[4 * i + 1] = verticesVector[i].y;
			vertices[4 * i + 2] = verticesVector[i].z;
			vertices[4 * i + 3] = 1.0;
			
			normals[4 * i + 0] = normalsVector[i].x;
			normals[4 * i + 1] = normalsVector[i].y;
			normals[4 * i + 2] = normalsVector[i].z;
			normals[4 * i + 3] = 0.0;
		}
		
		for(size_t i = 0; i < indicesVector.size(); ++i){
			indices[i] = indicesVector[i];
		}
		
		//Binding the VAO
		glBindVertexArray(m_VAO);

		//Filling Vertices
		glEnableVertexAttribArray(m_POSITION_ATTRIB_LOCATION);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
		glBufferData(GL_ARRAY_BUFFER, nbVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(m_POSITION_ATTRIB_LOCATION, 4, GL_FLOAT, GL_FALSE, 0, 0);
		
		//Filling normals
		 glEnableVertexAttribArray(m_NORMAL_ATTRIB_LOCATION);
		 glBindBuffer(GL_ARRAY_BUFFER, m_VBONormals);
		 glBufferData(GL_ARRAY_BUFFER, nbVertices * sizeof(GLfloat), normals, GL_STATIC_DRAW);
		 glVertexAttribPointer(m_NORMAL_ATTRIB_LOCATION, 4, GL_FLOAT, GL_FALSE, 0, 0);
		 
		 //Filling indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBOIndices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndices*sizeof(GLuint), indices, GL_STATIC_DRAW);
		
		//Unbinding the VAO
		glBindVertexArray(0);
	}
}