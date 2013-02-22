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
    
    static const char *BLIT_VERTEX_SHADER = "shaders/blit.shader.vs.glsl";
    static const char *BLIT_FRAGMENT_SHADER = "shaders/blit.shader.fs.glsl";
    
    static const char *SIMPLE_VERTEX_SHADER = "shaders/simple.shader.vs.glsl";
    static const char *SIMPLE_FRAGMENT_SHADER = "shaders/simple.shader.fs.glsl";

    //Creating shaders
    m_GBufferLightShaderManager = new GBufferLightShaderManager(GBUFFER_VERTEX_SHADER, GBUFFER_FRAGMENT_SHADER);
    m_LaccumLightShaderManager = new LaccumLightShaderManager(LACCUM_VERTEX_SHADER, LACCUM_FRAGMENT_SHADER);
    m_BlitShaderManager = new BlitShaderManager(BLIT_VERTEX_SHADER, BLIT_FRAGMENT_SHADER);
    m_SimpleShaderManager = new SimpleShaderManager(SIMPLE_VERTEX_SHADER, SIMPLE_FRAGMENT_SHADER);
    
    //Creating reference objects
    UniformObjectBuilder objectBuilder;
    
    //Ray Object
    m_RayObject3 = objectBuilder.buildFromObj("obj/ray3.obj", false);
    m_RayObject2 = objectBuilder.buildFromObj("obj/ray2.obj", false);
    m_RayObject1 = objectBuilder.buildFromObj("obj/ray1.obj", false);
    
    //DefenseUnit objects
    m_CadencorObject = objectBuilder.buildFromObj("obj/cadencor.obj", false);
    m_MirrorObject = objectBuilder.buildFromObj("obj/mirror.obj", false);
    m_MirrorObject->assignTexture(m_TextureManager.getTextureID("textures/mirror.png"));
    
    //Loading screen textures
    m_TextureManager.getTextureID("textures/screen/endScreen.png");
    
    //Creating the panel for deffered
    m_PanelObject = new Simple2DPanel();
    
    //LifeBar Object
    m_LifeBarObject = objectBuilder.buildFromObj("obj/lifebar.obj", false);
    
    //Ground Object
    m_GroundUnitObject = objectBuilder.buildFromObj("obj/ground.obj", false);
    
    //Loading alternative texture for the dirt
    m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/ground.png"));
    //m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/groundNormal.png"));
    //m_GroundUnitObject->assignSpecularMap(m_TextureManager.getTextureID("textures/groundSpecular.png"));
    
    //Assign Default Texture for the ground
    m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/full_grass.png"));
    //m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/grassNormal.png"));
    
    //Enemy Object
    m_EnemyObject = objectBuilder.buildFromObj("obj/zombie.obj", false);
    m_EnemyObject->assignTexture(m_TextureManager.getTextureID("textures/zombie.png"));
    //m_EnemyObject->assignNormalMap(m_TextureManager.getTextureID("textures/zombieNormal.png"));
    
    //Turret Object
    m_TurretObject = objectBuilder.buildFromObj("obj/turret.obj", false);
    m_TurretObject->assignTexture(m_TextureManager.getTextureID("textures/turret.png"));
    
    //House Object
    m_HouseObject = objectBuilder.buildFromObj("obj/house.obj", false);
    m_HouseObject->assignTexture(m_TextureManager.getTextureID("textures/house.png"));
    //m_HouseObject->assignNormalMap(m_TextureManager.getTextureID("textures/houseNormal.png"));
}

GLRenderer::~GLRenderer() {
    //Destroying the framebuffer
    destroy_framebuffer(m_GBuffer);
    //Deleting reference objects
    delete(m_LifeBarObject);
    delete(m_RayObject3);
    delete(m_RayObject2);
    delete(m_RayObject1);
    delete(m_GroundUnitObject);
    delete(m_HouseObject);
    delete(m_EnemyObject);
    delete(m_TurretObject);
    delete(m_CadencorObject);
    delete(m_MirrorObject);
    delete(m_PanelObject);
    //Deleting Shaders
    delete(m_GBufferLightShaderManager);
    delete(m_LaccumLightShaderManager);
    delete(m_BlitShaderManager);
    delete(m_SimpleShaderManager);
}

void GLRenderer::renderGame(const game::LifeBar & lifebar, const std::vector<Light> & m_LightVector, const game::Board & board, const std::vector<game::DefenseUnit> & defenseUnits, const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const api::Camera & camera) {
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
    //Render the objects
    renderGameBoard(board);
    renderGameEnemies(enemies);
    renderGameTurrets(turrets);
    renderGameDefenseUnits(defenseUnits);
    renderGameLifeBar(lifebar);
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
    glm::mat4 invMatrix =  glm::inverse(camera.getProjection() * camera.getView());
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
}

void GLRenderer::renderPause(const game::LifeBar & lifebar, const game::Board & board, const std::vector<game::DefenseUnit> & defenseUnits, const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const cv::Mat * webcamImage, const api::Camera & camera){
   // Viewport 
  glViewport(0, 0, m_Width, m_Height);
  // Default states
  glEnable(GL_DEPTH_TEST);
  // Clear the front buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  renderBackground(webcamImage);
  
  glUseProgram(m_SimpleShaderManager->getShaderID());
  m_SimpleShaderManager->setCameraMatrixInShader(camera.getView(), camera.getProjection());
  renderPauseBoard(board);
  renderPauseEnemies(enemies);
  renderPauseTurrets(turrets);
  renderPauseDefenseUnits(defenseUnits);
}

//***************************
//Private game rendering
//***************************
void GLRenderer::renderGameBoard(const game::Board & board){
     const std::vector<game::GroundUnit*> grid = board.getGridBoard();
     const game::GroundUnit * centralGroundUnit = board.getCentralGroundUnit();
     for(std::vector<game::GroundUnit*>::const_iterator it = grid.begin(); it != grid.end(); ++it){
	//Drawing the house if it's the central unit
	if((*it) == centralGroundUnit){
	  m_GBufferLightShaderManager->setModelMatrixInShader((*it)->getModel());
	  m_GBufferLightShaderManager->setObjectTextureInShader(m_HouseObject);
	  m_HouseObject->draw(GL_TRIANGLES);
	}
	//Getting the type and setting the texture
	if((*it)->getType() == ROCK_TYPE){
	  m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/ground.png"));
	  //m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/groundNormal.png"));
	}
	else{
	  m_GroundUnitObject->assignTexture(m_TextureManager.getTextureID("textures/full_grass.png"));
	  //m_GroundUnitObject->assignNormalMap(m_TextureManager.getTextureID("textures/grassNormal.png"));
	}
	m_GBufferLightShaderManager->setModelMatrixInShader((*it)->getModel());
	m_GBufferLightShaderManager->setObjectTextureInShader(m_GroundUnitObject);
	m_GroundUnitObject->draw(GL_TRIANGLES);
     }
}

void GLRenderer::renderGameEnemies(const std::list<game::EnemyUnit> & enemies)const{
  for(std::list<game::EnemyUnit>::const_iterator it = enemies.begin(); it != enemies.end(); ++it){
    	m_GBufferLightShaderManager->setModelMatrixInShader((*it).getModel());
	m_GBufferLightShaderManager->setObjectTextureInShader(m_EnemyObject);
	m_EnemyObject->draw(GL_TRIANGLES);
  }
}

void GLRenderer::renderGameTurrets(const std::vector<game::Turret> & turrets)const{
  for(std::vector<game::Turret>::const_iterator it = turrets.begin(); it != turrets.end(); ++it){
	if((*it).showRay()){
	  std::vector<game::Ray> rayVector;
	  (*it).getRayVector(rayVector);
	  renderGameRays(rayVector);
	}
    	m_GBufferLightShaderManager->setModelMatrixInShader((*it).getModel());
	m_GBufferLightShaderManager->setObjectTextureInShader(m_TurretObject);
	m_TurretObject->draw(GL_TRIANGLES);
  }
}

void GLRenderer::renderGameRays(const std::vector<game::Ray> & rays)const{
    m_GBufferLightShaderManager->setColorInShader(Color::Green());
    for(std::vector<game::Ray>::const_iterator it = rays.begin(); it != rays.end(); ++it){
	m_GBufferLightShaderManager->setModelMatrixInShader((*it).getModel());
	if((*it).getLength() == 3){
	  m_GBufferLightShaderManager->setObjectTextureInShader(m_RayObject3);
	  m_RayObject3->draw(GL_TRIANGLES);
	}
	else if((*it).getLength() == 2){
	  m_GBufferLightShaderManager->setObjectTextureInShader(m_RayObject2);
	  m_RayObject2->draw(GL_TRIANGLES);
	}
	else if((*it).getLength() == 1){
	  m_GBufferLightShaderManager->setObjectTextureInShader(m_RayObject1);
	  m_RayObject1->draw(GL_TRIANGLES);
	}
    }  
}

void GLRenderer::renderGameDefenseUnits(const std::vector<game::DefenseUnit> & defenseUnits)const{
    for(std::vector<game::DefenseUnit>::const_iterator it = defenseUnits.begin(); it != defenseUnits.end(); ++it){
	m_GBufferLightShaderManager->setModelMatrixInShader((*it).getModel());
	if((*it).getType() == DEFENSEUNIT_CADENCOR){
	  m_GBufferLightShaderManager->setObjectTextureInShader(m_CadencorObject);
	  m_CadencorObject->draw(GL_TRIANGLES);
	}
	else{
	  m_GBufferLightShaderManager->setObjectTextureInShader(m_MirrorObject);
	  m_MirrorObject->draw(GL_TRIANGLES);
	}
    } 
}

 void GLRenderer::renderGameLifeBar(const game::LifeBar & lifebar)const{
  float ratio = lifebar.getLifeRatio();
  if(ratio > 0.75){
    m_GBufferLightShaderManager->setColorInShader(Color::Green());
  }
  else if(ratio > 0.25){
     m_GBufferLightShaderManager->setColorInShader(Color::Orange());
  }
  else{
    m_GBufferLightShaderManager->setColorInShader(Color::Red());
  }
  m_GBufferLightShaderManager->setModelMatrixInShader(lifebar.getModel());
  m_GBufferLightShaderManager->setObjectTextureInShader(m_LifeBarObject);
  m_LifeBarObject->draw(GL_TRIANGLES);
 }
 
//***************************
//Private pause rendering
//***************************
void GLRenderer::renderBackground(const cv::Mat * webcamFrame){
	//Updating the background texture
	m_ChangingTexture.updateTexture(webcamFrame->cols, webcamFrame->rows, (unsigned int*)webcamFrame->ptr(0));
	//Drawing the background
	glViewport(0, 0, m_Width, m_Height);
	glUseProgram(m_BlitShaderManager->getShaderID());
	glDisable(GL_DEPTH_TEST);
	//Update light uniforms
	m_BlitShaderManager->setTextureInShader(m_ChangingTexture.getID());
	// Draw quad
	m_PanelObject->draw(GL_TRIANGLES);
	glEnable(GL_DEPTH_TEST);
}

void GLRenderer::renderPauseBoard(const game::Board & board){
     const std::vector<game::GroundUnit*> grid = board.getGridBoard();
     const game::GroundUnit * centralGroundUnit = board.getCentralGroundUnit();
     for(std::vector<game::GroundUnit*>::const_iterator it = grid.begin(); it != grid.end(); ++it){
        if((*it)->isOccupied()){
	  m_SimpleShaderManager->setColorInShader(Color::Red());
	}
	else{
	  m_SimpleShaderManager->setColorInShader(Color::Green());
	}
	//Drawing the house if it's the central unit
	if((*it) == centralGroundUnit){
	  m_SimpleShaderManager->setColorInShader(Color::Blue());
	  m_SimpleShaderManager->setModelMatrixInShader((*it)->getModel());
	  m_HouseObject->draw(GL_TRIANGLES);
	}
	m_SimpleShaderManager->setModelMatrixInShader((*it)->getModel());
	m_GroundUnitObject->draw(GL_TRIANGLES);
     }
}

void GLRenderer::renderPauseEnemies(const std::list<game::EnemyUnit> & enemies)const{
  m_SimpleShaderManager->setColorInShader(Color::Blue());
  for(std::list<game::EnemyUnit>::const_iterator it = enemies.begin(); it != enemies.end(); ++it){
    	m_SimpleShaderManager->setModelMatrixInShader((*it).getModel());
	m_EnemyObject->draw(GL_TRIANGLES);
  }
}

void GLRenderer::renderPauseTurrets(const std::vector<game::Turret> & turrets)const{
  m_SimpleShaderManager->setColorInShader(Color::Blue());
  for(std::vector<game::Turret>::const_iterator it = turrets.begin(); it != turrets.end(); ++it){
    	m_SimpleShaderManager->setModelMatrixInShader((*it).getModel());
	m_TurretObject->draw(GL_TRIANGLES);
  }
}

void GLRenderer::renderPauseDefenseUnits(const std::vector<game::DefenseUnit> & defenseUnits)const{
    m_SimpleShaderManager->setColorInShader(Color::Blue());
    for(std::vector<game::DefenseUnit>::const_iterator it = defenseUnits.begin(); it != defenseUnits.end(); ++it){
	m_SimpleShaderManager->setModelMatrixInShader((*it).getModel());
	if((*it).getType() == DEFENSEUNIT_CADENCOR){
	  m_CadencorObject->draw(GL_TRIANGLES);
	}
	else{
	  m_MirrorObject->draw(GL_TRIANGLES);
	}
    } 
}


 
 //**********************************
 //Public screen rendering
 //********************************** 
  void GLRenderer::renderEndScreen(){
    glViewport(m_Width/4.0, m_Height/4.0, m_Width/2.0, m_Height/2.0);
    glUseProgram(m_BlitShaderManager->getShaderID());
    glDisable(GL_DEPTH_TEST);
    //Update light uniforms
    m_BlitShaderManager->setTextureInShader(m_TextureManager.getTextureID("textures/screen/endScreen.png"));
    // Draw quad
    m_PanelObject->draw(GL_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
  }

  void GLRenderer::renderBeginScreen(){
    glViewport(0, 0, m_Width, m_Height);
    glUseProgram(m_BlitShaderManager->getShaderID());
    glDisable(GL_DEPTH_TEST);
    //Update light uniforms
    m_BlitShaderManager->setTextureInShader(m_TextureManager.getTextureID("textures/screen/endScreen.png"));
    // Draw quad
    m_PanelObject->draw(GL_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
  }
  
  void GLRenderer::renderWaveScreen(){
    glViewport(m_Width/4.0, m_Height/4.0, m_Width/2.0, m_Height/2.0);
    glUseProgram(m_BlitShaderManager->getShaderID());
    glDisable(GL_DEPTH_TEST);
    //Update light uniforms
    m_BlitShaderManager->setTextureInShader(m_TextureManager.getTextureID("textures/screen/waveScreen.png"));
    // Draw quad
    m_PanelObject->draw(GL_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
  }
  
  void GLRenderer::renderGoScreen(){
    glViewport(m_Width/4.0, m_Height/4.0, m_Width/2.0, m_Height/2.0);
    glUseProgram(m_BlitShaderManager->getShaderID());
    glDisable(GL_DEPTH_TEST);
    //Update light uniforms
    m_BlitShaderManager->setTextureInShader(m_TextureManager.getTextureID("textures/screen/goScreen.png"));
    // Draw quad
    m_PanelObject->draw(GL_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
  }
}//namespace renderer
