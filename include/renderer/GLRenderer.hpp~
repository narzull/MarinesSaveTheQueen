#ifndef _GLRENDERER_HPP_
#define _GLRENDERER_HPP_

//api includes
#include "api/Camera.hpp"
#include "api/Entity.hpp"

//renderer includes
#include "renderer/Simple2DPanel.hpp"
#include "renderer/UniformObject.hpp"
#include "renderer/TextureManager.hpp"
#include "renderer/ChangingTexture.hpp"
#include "renderer/ShaderManager/GBufferLightShaderManager.hpp"
#include "renderer/ShaderManager/LaccumLightShaderManager.hpp"
#include "renderer/ShaderManager/BlitShaderManager.hpp"
#include "renderer/FramebufferGL.hpp"

//game includes
#include "game/Board.hpp"
#include "game/EnemyUnit.hpp"
#include "game/Turret.hpp"
#include "game/DefenseUnit.hpp"
#include "game/LifeBar.hpp"

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
    void render(bool pause, const game::LifeBar & lifebar, const std::vector<Light> & m_LightVector, const game::Board & board, const std::vector<game::DefenseUnit> & defenseUnits, const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const cv::Mat * webcamImage, const api::Camera & camera);
    void renderEndScreen();
    void renderBeginScreen();
    void renderWaveScreen();
    void renderGoScreen();
    
private:
    //Private methods
    void renderBackground(const cv::Mat * webcamImage);
    void renderBoard(bool pause, const game::Board & board);
    void renderEnemies(const std::list<game::EnemyUnit> & enemies)const;
    void renderTurrets(bool pause, const std::vector<game::Turret> & turrets)const;
    void renderRays(const std::vector<game::Ray> & rays)const;
    void renderDefenseUnits(const std::vector<game::DefenseUnit> & defenseUnits)const;
    void renderLifeBar(const game::LifeBar & lifebar)const;
	
    //Attribute
    int m_Width;
    int m_Height;
    
    //Modele use to render
    UniformObject * m_RayObject1;
    UniformObject * m_RayObject2;
    UniformObject * m_RayObject3;
    UniformObject * m_TurretObject;
    UniformObject * m_EnemyObject;
    UniformObject * m_HouseObject;
    UniformObject * m_GroundUnitObject;
    UniformObject * m_CadencorObject;
    UniformObject * m_MirrorObject;
    UniformObject * m_LifeBarObject;
    Simple2DPanel * m_PanelObject;
    //Texture
    TextureManager m_TextureManager;
    ChangingTexture m_ChangingTexture;
    
    //Framebuffer
    FramebufferGL m_GBuffer;
    
    //Shader
    GBufferLightShaderManager * m_GBufferLightShaderManager;
    LaccumLightShaderManager * m_LaccumLightShaderManager;
    BlitShaderManager * m_BlitShaderManager;
};
}//namespace api

#endif
