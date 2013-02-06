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


GLRenderer::GLRenderer(int width, int height):m_Width(width), m_Height(height){
    // Init glew (A GL context must exist)
    GLenum error;
    if((error = glewInit()) != GLEW_OK) {
        throw std::runtime_error((const char*)glewGetErrorString(error));
    }
    
    int status;
    status = build_framebuffer(m_GBuffer, m_Width, m_Height, 2);  
    if (status == -1)  
    {  
	    throw std::runtime_error("Error in building the frame buffer");
    } 

    static const char *GBUFFER_VERTEX_SHADER = "shaders/gbuffer.lightshader.vs.glsl";
    static const char *GBUFFER_FRAGMENT_SHADER = "shaders/gbuffer.lightshader.fs.glsl";
    
    static const char *LACCUM_VERTEX_SHADER = "shaders/laccum.lightshader.vs.glsl";
    static const char *LACCUM_FRAGMENT_SHADER = "shaders/laccum.lightshader.fs.glsl";

    //Creating shaders
    m_GBufferLightShaderManager = new GBufferLightShaderManager(GBUFFER_VERTEX_SHADER, GBUFFER_FRAGMENT_SHADER);
    m_LaccumLightShaderManager = new LaccumLightShaderManager(LACCUM_VERTEX_SHADER, LACCUM_FRAGMENT_SHADER);
    
    //Creating reference objects
    UniformObjectBuilder objectBuilder;
    
    //Creating the panel for deffered
    m_PanelObject = new Simple2DPanel();
    
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
    //Destroying the framebuffer
    destroy_framebuffer(m_GBuffer);
    //Deleting reference objects
    delete(m_GroundUnitObject);
    delete(m_HouseObject);
    delete(m_EnemyObject);
    delete(m_TurretObject);
    delete(m_PanelObject);
    //Deleting Shaders
    delete(m_GBufferLightShaderManager);
    delete(m_LaccumLightShaderManager);
}

void GLRenderer::render(bool pause, const std::vector<Light> & m_LightVector, const game::Board & board, const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const IplImage * webcamFrame, const api::Camera & camera) {
    //*****************************
    //INIT OF THE DEFFERED
    //*****************************
    //Binding the GBuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_GBuffer.fbo);
    glDrawBuffers(m_GBuffer.outCount, m_GBuffer.drawBuffers);
    // Viewport 
    glViewport(0, 0, m_Width, m_Height);
    // Default states
    glEnable(GL_DEPTH_TEST);
    // Clear the front buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //*****************************
    //G-BUFFER SHADER PART OF THE DEFFERED
    //*****************************
    // Bind gbuffer shader
    glUseProgram(m_GBufferLightShaderManager->getShaderID());
    //Upload uniforms
    m_GBufferLightShaderManager->setCameraMatrixInShader(camera.getView(), camera.getProjection());
    m_GBufferLightShaderManager->setPauseInShader(pause);
    //Render the objects
    renderBoard(pause, board, camera);
    renderEnemies(pause, enemies, camera);
    renderTurrets(pause, turrets, camera);
    //Unbinding the GBuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Clearing the front buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
     //*****************************
    //LACCUM SHADER PART OF THE DEFFERED
    //*****************************
    // Viewport 
    glViewport(0, 0, m_Width, m_Height);
    //Bind the laccum shader
    glUseProgram(m_LaccumLightShaderManager->getShaderID());
    // Upload uniforms
    m_LaccumLightShaderManager->setEyeInShader(camera.getPosition());  
    glm::mat4 invMatrix =  glm::inverse(camera.getProjection());
    m_LaccumLightShaderManager->setInvMatrixInShader(invMatrix);
    m_LaccumLightShaderManager->setTextureInShaderFromGBuffer(m_GBuffer);
    // Blit above the rest
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    for (unsigned int i = 0; i < m_LightVector.size(); ++i)
    {
	//Update light uniforms
	m_LaccumLightShaderManager->setLightInShader(m_LightVector[i]);
	// Draw quad
	m_PanelObject->draw(GL_TRIANGLES);
    }
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    
    /*  
    if(webcamFrame != NULL) renderBackground(webcamFrame);
    */
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

void GLRenderer::renderBoard(bool pause, const game::Board & board, const api::Camera & camera){

      GLenum primitive = GL_TRIANGLES;
      if(pause) primitive = GL_LINE_LOOP;
  
     const std::vector<game::GroundUnit*> grid = board.getGridBoard();
     const game::GroundUnit * centralGroundUnit = board.getCentralGroundUnit();
     for(std::vector<game::GroundUnit*>::const_iterator it = grid.begin(); it != grid.end(); ++it){
       
	if((*it)->isOccupied()){
	  m_GBufferLightShaderManager->setColorInShader(Color::Red());
	}
	else{
	  m_GBufferLightShaderManager->setColorInShader(Color::Green());
	}
	
	//Drawing the house if it's the central unit
	if((*it) == centralGroundUnit){
	  m_GBufferLightShaderManager->setColorInShader(Color::Blue());
	  m_GBufferLightShaderManager->setModelMatrixInShader((*it)->getModel());
	  m_GBufferLightShaderManager->setObjectTextureInShader(m_HouseObject);
	  m_HouseObject->draw(primitive);
	}
       
	//Getting the type and setting the texture
	if((*it)->getType() == ROCK_TYPE){
	  m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/ground.png"));
	  m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/groundNormal.png"));
	}
	else{
	  m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/full_grass.png"));
	  m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/grassNormal.png"));
	}
	m_GBufferLightShaderManager->setModelMatrixInShader((*it)->getModel());
	m_GBufferLightShaderManager->setObjectTextureInShader(m_GroundUnitObject);
	m_GroundUnitObject->draw(primitive);
     }
}

void GLRenderer::renderEnemies(bool pause, const std::list<game::EnemyUnit> & enemies, const api::Camera & camera)const{
  m_GBufferLightShaderManager->setColorInShader(Color::Red());
  for(std::list<game::EnemyUnit>::const_iterator it = enemies.begin(); it != enemies.end(); ++it){
    	m_GBufferLightShaderManager->setModelMatrixInShader((*it).getModel());
	m_GBufferLightShaderManager->setObjectTextureInShader(m_EnemyObject);
	m_EnemyObject->draw(GL_TRIANGLES);
  }
}

void GLRenderer::renderTurrets(bool pause, const std::vector<game::Turret> & turrets, const api::Camera & camera)const{
  m_GBufferLightShaderManager->setColorInShader(Color::Blue());
  for(std::vector<game::Turret>::const_iterator it = turrets.begin(); it != turrets.end(); ++it){
    	m_GBufferLightShaderManager->setModelMatrixInShader((*it).getModel());
	m_GBufferLightShaderManager->setObjectTextureInShader(m_TurretObject);
	m_TurretObject->draw(GL_TRIANGLES);
  }
}

}//namespace renderer
