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
#include "renderer/Animation.hpp"
#include "renderer/ShaderManager/GBufferLightShaderManager.hpp"
#include "renderer/ShaderManager/LaccumLightShaderManager.hpp"
#include "renderer/ShaderManager/BlitShaderManager.hpp"
#include "renderer/ShaderManager/SimpleShaderManager.hpp"
#include "renderer/FramebufferGL.hpp"

//game includes
#include "game/Board.hpp"
#include "game/EnemyUnit.hpp"
#include "game/Turret.hpp"
#include "game/DefenseUnit.hpp"
#include "game/LifeBar.hpp"
#include "game/Barrier.hpp"

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
    void renderGame(const game::LifeBar & lifebar, const std::vector<Light> & m_LightVector, const game::Board & board, const std::vector<game::Barrier> & barriers, const std::vector<game::DefenseUnit> & defenseUnits, const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const api::Camera & camera);
    void renderPause(const game::LifeBar & lifebar, const game::Board & board, const std::vector<game::Barrier> & barriers, const std::vector<game::DefenseUnit> & defenseUnits, const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const cv::Mat * webcamImage, const api::Camera & camera);
    //Public methods for screen rendering
    void renderEndScreen();
    void renderBeginScreen();
    void renderWaveScreen();
    void renderGoScreen();
    
private:
    //Private methods for game rendering
    void renderGameBoard(const game::Board & board);
    void renderGameEnemies(const std::list<game::EnemyUnit> & enemies)const;
    void renderGameTurrets(const std::vector<game::Turret> & turrets)const;
    void renderGameRays(const std::vector<game::Ray> & rays)const;
    void renderGameDefenseUnits(const std::vector<game::DefenseUnit> & defenseUnits)const;
    void renderGameBarriers(const std::vector<game::Barrier> & barriers)const;
    void renderGameLifeBar(const game::LifeBar & lifebar)const;
    //Private methods for pause rendering
    void renderPauseBoard(const game::Board & board);
    void renderPauseEnemies(const std::list<game::EnemyUnit> & enemies)const;
    void renderPauseTurrets(const std::vector<game::Turret> & turrets)const;
    void renderPauseDefenseUnits(const std::vector<game::DefenseUnit> & defenseUnits)const;
    void renderPauseBarriers(const std::vector<game::Barrier> & barriers)const;
    
    //Private methods for pause rendering
    void renderBackground(const cv::Mat * webcamImage);
 
    //Attribute
    int m_Width;
    int m_Height;
    
    //Animation
    Animation m_EnemyAttackAnimation;
    Animation m_EnemyWalkAnimation;
    
    //Modele use to render
    UniformObject * m_SkyboxObject;
    UniformObject * m_RayObject1;
    UniformObject * m_RayObject2;
    UniformObject * m_RayObject3;
    UniformObject * m_TurretObject;
    UniformObject * m_HouseObject;
    UniformObject * m_GroundUnitObject;
    UniformObject * m_CadencorObject;
    UniformObject * m_MirrorObject;
    UniformObject * m_LifeBarObject;
    UniformObject * m_BarrierObject;
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
    SimpleShaderManager * m_SimpleShaderManager;
};
}//namespace api

#endif
