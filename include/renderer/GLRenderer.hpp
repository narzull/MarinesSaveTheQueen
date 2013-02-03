#ifndef _GLRENDERER_HPP_
#define _GLRENDERER_HPP_

//api includes
#include "api/Camera.hpp"
#include "api/Entity.hpp"

//renderer includes
#include "renderer/UniformObject.hpp"
#include "renderer/TextureManager.hpp"
#include "renderer/ShaderManager/SimpleShaderManager.hpp"
#include "renderer/ShaderManager/LightShaderManager.hpp"

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
    GLRenderer();
    ~GLRenderer();
    //Public methods
    void render(const game::Board & board,const std::vector<game::Turret> & turrets, const std::list<game::EnemyUnit> & enemies, const IplImage * webcamFrame, const api::Camera & camera);
	
private:
    //Private methods
    int renderBackground(const IplImage * webcamFrame)const;
    void renderBoard(const game::Board & board, const api::Camera & camera);
    void renderEnemies(const std::list<game::EnemyUnit> & enemies, const api::Camera & camera)const;
    void renderTurrets(const std::vector<game::Turret> & turrets, const api::Camera & camera)const;
	
    //Modele use to render
    UniformObject * m_TurretObject;
    UniformObject * m_EnemyObject;
    UniformObject * m_HouseObject;
    UniformObject * m_GroundUnitObject;
    //Texture
    TextureManager m_TextureManager;
    //Shader
    SimpleShaderManager * m_SimpleShaderManager;
    LightShaderManager * m_LightShaderManager;
};
}//namespace api

#endif
