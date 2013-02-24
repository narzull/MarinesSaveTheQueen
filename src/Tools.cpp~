#include "api/Tools.hpp"


namespace tools{
	double distanceBetween(const glm::vec3 & p1, const glm::vec3 & p2){
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	}
	
	float getNorm(const glm::vec3 & vector){
		return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}
	
	float max(const std::vector<float> & values){
		size_t indMax = 0;
		float valMax = values[0];
		for(size_t i = 1; i < 3; ++i){
			if(values[i] > valMax){
				valMax = values[i];
				indMax = i;
			}
		}
		return values[indMax];
	}
	
	float min(const std::vector<float> & values){
		size_t indMin = 0;
		float valMin = values[0];
		for(size_t i = 1; i < 3; ++i){
			if(values[i] < valMin){
				valMin = values[i];
				indMin = i;
			}
		}
		return values[indMin];
	}
	
	bool isDoubleEquals(double v1, double v2){
		if(fabs(v1 - v2) < 0.0000001) return true;
		return false; 
	}
	
	//Transformation functions
	void transformToTable(GLfloat * tab, glm::mat4 matrix){
		for(size_t i = 0; i < 4; ++i){
			for(size_t j = 0; j < 4; ++j){
				tab[i*4+j] = matrix[i][j];
			}
		}
	}
	
	void transformToMatrix(double * tab, glm::mat4 & matrix){
		for(size_t i = 0; i < 16; ++i){
		     matrix[i/4][i%4] = tab[i];
		}
	}
	
	//Reading in file
	void readVec3(std::istringstream& line, glm::vec3 & readVec)
	{
		GLfloat vec[3]={0.0, 0.0, 0.0};
		line >> vec[0] >> vec[1] >> vec[2];
		readVec.x = vec[0];
		readVec.y = vec[1];
		readVec.z = vec[2];
	}

	// Fills a std::vector with two GLfloat values in a string
	void readVec2(std::istringstream& line, glm::vec2 & readVec)
	{
		GLfloat vec[2]={0.0, 0.0};
		line >> vec[0] >> vec[1];
		readVec.x = vec[0];
		readVec.y = 1.0-vec[1];
	}

	// Fills std::vectors with indices of three type for the vertices in the face
	void readFace(std::istringstream& line, std::vector<size_t> & indices,  std::vector<size_t> & uvIndices, std::vector<size_t> & normalsIndices)
	{
		std::string face;
		while (!line.eof())
		{
			line >> face;
				std::vector<std::string> sequence;
				split(face, sequence, "/");
				size_t index=strtoul(sequence[0].c_str(), NULL, 10)-1;
				indices.push_back(index);

				size_t uvIndex=strtoul(sequence[1].c_str(), NULL, 10)-1;
				uvIndices.push_back(uvIndex);

				size_t normalIndex=strtoul(sequence[2].c_str(), NULL, 10)-1;
				normalsIndices.push_back(normalIndex);
		}
	}
	
	void split(const std::string& string, std::vector<std::string>& tokens, const std::string& delim)
	{
			// Clears the vector where the results are put
			tokens.clear();
			// Goes through the string and extract the tokens
			for (std::string::size_type p1=0, p2=0; p1!=std::string::npos; )
			{
					p1=string.find_first_not_of(delim, p1);
					if (p1!=std::string::npos)
					{
							p2=string.find_first_of(delim, p1);
							tokens.push_back(string.substr(p1, p2-p1));
							p1=p2;
					}
			}
	}
	
	int getInfosFromObj(const std::string & objFileName, 
					std::vector<glm::vec3> & verticesList,
					std::vector<glm::vec2> & uvsList,
					std::vector<glm::vec3> & normalsList,
					std::vector<size_t> & verticesIndices,
					std::vector<size_t> & uvsIndices,
					std::vector<size_t> & normalsIndices,
					bool & hasVn,
					bool & hasVt
				){
		
		//Loading the file
		std::ifstream file(objFileName.c_str(), std::ios_base::in);
		std::string buf, key;
		
		if(!file)
		{
			return 1;
		}
		
		//Reading the file
		while (getline(file, buf))
		{
				std::istringstream line(buf);
				line >> key;    
				if(key=="v"){
					glm::vec3 vertice;
					tools::readVec3(line, vertice);
					verticesList.push_back(vertice);
				}
				else if(key == "vt"){
					glm::vec2 uvs;
					tools::readVec2(line, uvs);
					uvsList.push_back(uvs);
					hasVt=true; 
				}
				else if(key=="vn"){
					glm::vec3 normal;
					tools::readVec3(line, normal);
					normalsList.push_back(normal);
					hasVn=true; 
				}
				else if(key=="f"){
					std::vector<size_t> indice, uvIndice, normalIndice;
					tools::readFace(line, indice,  uvIndice, normalIndice);
					for(size_t i = 0; i < 3; ++i){
						verticesIndices.push_back(indice[i]);
						uvsIndices.push_back(uvIndice[i]);
						normalsIndices.push_back(normalIndice[i]);
					}
				}
				else{
				}
		}
		return 0;
	}
}