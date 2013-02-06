#ifndef _GLRENDERER_HPP_
#define _GLRENDERER_HPP_

//api includes
#include "api/Camera.hpp"
#include "api/Entity.hpp"

//renderer includes
#include "renderer/Simple2DPanel.hpp"
#include "renderer/UniformObject.hpp"
#include "renderer/TextureManager.hpp"
#include "renderer/ShaderManager/GBufferLightShaderManager.hpp"
#include "renderer/ShaderManager/LaccumLightShaderManager.hpp"
#include "renderer/FramebufferGL.hpp"

//game includes
#include "game/Board.hpp"
#include "game/EnemyUnit.hpp"
#include "game/Turret.hpp"

#include <GL/glew.h>
#include <vector>
#include <list>
#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h> 

namespace renderer{
class GLRenderer {
public:
    //Constructor & Destructor
    GLRenderer(int width, int height);
    ~GLRenderer();
    //Public methods
    void render(bool pause, const std::vector<Light> & m_LightVector, const std::vector<game::Ray> & rays, const game::Board & board,const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const IplImage * webcamFrame, const api::Camera & camera);
	
private:
    //Private methods
    int renderBackground(const IplImage * webcamFrame)const;
    void renderBoard(bool pause, const game::Board & board);
    void renderEnemies(bool pause, const std::list<game::EnemyUnit> & enemies)const;
    void renderTurrets(bool pause, const std::vector<game::Turret> & turrets)const;
    void renderRays(bool pause, const std::vector<game::Ray> & rays, const game::Board & board)const;
	
    //Attribute
    int m_Width;
    int m_Height;
    
    //Modele use to render
    UniformObject * m_RayObject;
    UniformObject * m_TurretObject;
    UniformObject * m_EnemyObject;
    UniformObject * m_HouseObject;
    UniformObject * m_GroundUnitObject;
    Simple2DPanel * m_PanelObject;
    //Texture
    TextureManager m_TextureManager;
    
    //Framebuffer
    FramebufferGL m_GBuffer;
    
    //Shader
    GBufferLightShaderManager * m_GBufferLightShaderManager;
    LaccumLightShaderManager * m_LaccumLightShaderManager;
};
}//namespace api

#endif
