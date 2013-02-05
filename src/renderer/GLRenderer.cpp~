//renderer includes
#include "renderer/GLRenderer.hpp"
#include "renderer/Color.hpp"
#include "renderer/UniformObjectBuilder.hpp"

//game includes
#include "game/GroundUnit.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


namespace renderer{


GLRenderer::GLRenderer(){
    // Init glew (A GL context must exist)
    GLenum error;
    if((error = glewInit()) != GLEW_OK) {
        throw std::runtime_error((const char*)glewGetErrorString(error));
    }

	static const char *SIMPLE_VERTEX_SHADER = "shaders/colorShader.vs.glsl";
	static const char *SIMPLE_FRAGMENT_SHADER = "shaders/colorShader.fs.glsl";
	static const char *LIGHT_VERTEX_SHADER = "shaders/lightShader.vs.glsl";
	static const char *LIGHT_FRAGMENT_SHADER = "shaders/lightShader.fs.glsl";
    
	//Creating shaders

	m_SimpleShaderManager = new SimpleShaderManager(SIMPLE_VERTEX_SHADER, SIMPLE_FRAGMENT_SHADER);
	m_LightShaderManager = new LightShaderManager(LIGHT_VERTEX_SHADER, LIGHT_FRAGMENT_SHADER);
	
	//Creating reference objects
	UniformObjectBuilder objectBuilder;
	
	//Ground Object
	m_GroundUnitObject = objectBuilder.buildFromObj("obj/ground.obj", false);
	//Loading alternative texture for the dirt
	m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/ground.png"));
	m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/groundNormal.png"));
	m_GroundUnitObject->assignSpecularMap(m_TextureManager.getTextureID("textures/groundSpecular.png"));
	//Assign Default Texture for the ground
	m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/full_grass.png"));
	m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/grassNormal.png"));
	
	//Enemy Object
	m_EnemyObject = objectBuilder.buildFromObj("obj/zombie.obj", false);
	m_EnemyObject->assignTexture(m_TextureManager.getTextureID("textures/zombie.png"));
// 	m_EnemyObject->assignNormalMap(m_TextureManager.getTextureID("textures/zombieNormal.png"));
	
	//Turret Object
	m_TurretObject = objectBuilder.buildFromObj("obj/turret.obj", false);
	m_TurretObject->assignTexture(m_TextureManager.getTextureID("textures/turret.png"));
	
	//House Object
	m_HouseObject = objectBuilder.buildFromObj("obj/house.obj", false);
	m_HouseObject->assignTexture(m_TextureManager.getTextureID("textures/house.png"));
	m_HouseObject->assignNormalMap(m_TextureManager.getTextureID("textures/houseNormal.png"));
	
}

GLRenderer::~GLRenderer() {
    //Deleting reference objects
    delete(m_GroundUnitObject);
    delete(m_HouseObject);
    delete(m_EnemyObject);
    delete(m_TurretObject);
    //Deleting Shaders
    delete(m_SimpleShaderManager);
    delete(m_LightShaderManager);
}

void GLRenderer::render(const game::Board & board, const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const IplImage * webcamFrame, const api::Camera & camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(webcamFrame != NULL) renderBackground(webcamFrame);
	
	//Normal Shader
	glUseProgram(m_SimpleShaderManager->getShaderID());
	
	//Light Shader
	glUseProgram(m_LightShaderManager->getShaderID());	
	//Setting variables in shader
	m_LightShaderManager->setEyeInShader(camera.getPosition());
	Light light(glm::vec3(-1.0,-1.0,-1.0), glm::vec3(1.0,1.0,1.0), 1.0);
	m_LightShaderManager->setLightInShader(light);
	
	m_LightShaderManager->setColorInShader(Color::Yellow());
	
	renderBoard(board, camera);
	renderEnemies(enemies, camera);
	renderTurrets(turrets, camera);
}

int GLRenderer::renderBackground(const IplImage * webcamFrame)const{
	GLenum format;
        switch(webcamFrame->nChannels) {
            case 1:
                format = GL_LUMINANCE;
                break;
            case 2:
                format = GL_LUMINANCE_ALPHA;
                break;
            case 3:
                format = GL_BGR;
                break;
	    default:
		    return 1;
        }
        glPixelZoom(0.5,0.5);
        glDrawPixels(webcamFrame->width, webcamFrame->height, format, GL_UNSIGNED_BYTE, webcamFrame->imageData);
	return 0;
}

void GLRenderer::renderBoard(const game::Board & board, const api::Camera & camera){
     const std::vector<game::GroundUnit*> grid = board.getGridBoard();
     const game::GroundUnit * centralGroundUnit = board.getCentralGroundUnit();
     for(std::vector<game::GroundUnit*>::const_iterator it = grid.begin(); it != grid.end(); ++it){
	//Getting the type and setting the texture
	if((*it)->getType() == ROCK_TYPE){
	  m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/ground.png"));
	  m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/groundNormal.png"));
	}
	else{
	  m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/full_grass.png"));
	  m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/grassNormal.png"));
	}
	m_LightShaderManager->set3DMatrixInShader((*it)->getModel(), camera.getView(), camera.getProjection());
	m_LightShaderManager->setObjectTextureInShader(m_GroundUnitObject);
	m_GroundUnitObject->draw(GL_TRIANGLES);
	
	if((*it) == centralGroundUnit){
	  m_LightShaderManager->set3DMatrixInShader(glm::mat4(), camera.getView(), camera.getProjection());
	  m_LightShaderManager->setObjectTextureInShader(m_HouseObject);
	  m_HouseObject->draw(GL_TRIANGLES);
	}
     }
}

void GLRenderer::renderEnemies(const std::list<game::EnemyUnit> & enemies, const api::Camera & camera)const{
  for(std::list<game::EnemyUnit>::const_iterator it = enemies.begin(); it != enemies.end(); ++it){
    	m_LightShaderManager->set3DMatrixInShader((*it).getModel(), camera.getView(), camera.getProjection());
	m_LightShaderManager->setObjectTextureInShader(m_EnemyObject);
	m_EnemyObject->draw(GL_TRIANGLES);
  }
}

void GLRenderer::renderTurrets(const std::vector<game::Turret> & turrets, const api::Camera & camera)const{
  for(std::vector<game::Turret>::const_iterator it = turrets.begin(); it != turrets.end(); ++it){
    	m_LightShaderManager->set3DMatrixInShader((*it).getModel(), camera.getView(), camera.getProjection());
	m_LightShaderManager->setObjectTextureInShader(m_TurretObject);
	m_TurretObject->draw(GL_TRIANGLES);
  }
}

}//namespace renderer
