#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "Camera.hpp"
#include "Entity.hpp"
#include "SoundManager.hpp"
#include "../renderer/GLRenderer.hpp"
#include "../renderer/ShaderManager/LaccumLightShaderManager.hpp"
#include "../game/Board.hpp"
#include "../game/EnemyUnit.hpp"
#include "../game/Turret.hpp"
#include "../game/DefenseUnit.hpp"
#include "../game/LifeBar.hpp"

#include <string>
#include <vector>
#include <list>
#include <SDL/SDL.h>
#include <opencv/cv.h>
#include <opencv/highgui.h> 

#define FRAMES_PER_SECOND 30

//Application class of our program that run the main loop
namespace api{
class Application{
private:
	//********************************
	//Attribute
	//********************************
	//Const attribute
	static const size_t m_WINDOW_WIDTH = 1024;
	static const size_t m_WINDOW_HEIGHT = 768;
	static const size_t m_BYTES_PER_PIXEL = 32;
	const std::string m_WINDOW_TITLE;
	
	//Game attribute
	game::LifeBar m_LifeBar;
	api::SoundManager m_SoundManager;
	
	//Scene Entities
	unsigned int m_WaveNumber;
	unsigned int m_EnemiesToKill;
	game::Board m_Board;
	std::vector<renderer::Light> m_Lights;
	std::list<game::EnemyUnit> m_Enemies;
	std::vector<game::DefenseUnit> m_DefenseUnit;
	std::vector<game::Turret> m_Turrets;

	//Renderer attribute
	renderer::GLRenderer* m_GLRenderer;
	
	//Application variables
	bool m_Done;
	bool m_Pause;
	bool m_LockCamera;
	//Camera related attribute
	api::Camera m_Camera;
	double m_Step;
	int m_MoveFlagX;
	int m_MoveFlagZ;
	GLfloat m_MousePosX;
	GLfloat m_MousePosY;
	GLfloat m_AngleLong;
	GLfloat m_AngleLat;
	GLuint m_FrameCount;
	
	//Webcam attribute
	CvCapture * m_Webcam;
	IplImage * m_WebcamFrame;
	
	//*****************************
	//Private methods
	//*****************************
	//Event private methods
	void handleEvent(const SDL_Event& event);
	void handleKeyEvent(const SDL_keysym& keysym, bool down);
	//Application private methods
	void initApplication();
	void initSDLFlags();
	bool saveScreen();
	//Camera related functions
	void moveCameraInApplication();
	
	//*****************************
	//Private game methods
	//*****************************
	void initWave(unsigned int waveNumber);
	void updateEnemy(game::EnemyUnit & enemy);
	void updateGame();
public:
	//Constructor & Destructor
	Application(std::string windowTitle, const std::string & param);
	~Application();
	
	//Applciation public methods
	void loop();
};
}

#endif //Application .hpp