#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "Camera.hpp"
#include "Entity.hpp"
#include "SoundManager.hpp"
#include "WebcamManager.hpp"
#include "../renderer/GLRenderer.hpp"
#include "../renderer/ShaderManager/LaccumLightShaderManager.hpp"
#include "../game/Board.hpp"
#include "../game/EnemyUnit.hpp"
#include "../game/Turret.hpp"
#include "../game/DefenseUnit.hpp"
#include "../game/Barrier.hpp"
#include "../game/LifeBar.hpp"

#include <string>
#include <vector>
#include <list>
#include <SDL/SDL.h>
#include <opencv/cv.h>
#include <opencv/highgui.h> 

#define FRAMES_PER_SECOND 30

#define GAME_STATUS_LAUNCH 1
#define GAME_STATUS_RUNNING 2
#define GAME_STATUS_WAVE_TRANSITION 3
#define GAME_STATUS_END 4

//Application class of our program that run the main loop
namespace api{
class Application{
private:
	//********************************
	//Attribute
	//********************************
	//Const attribute
	static const size_t m_BYTES_PER_PIXEL = 32;
	static const size_t m_WAVE_TRANSITION_FRAME_DURATION = 100;
	static const unsigned int m_INITIAL_NUMBER_OF_DOWN_BARRIER = 4;
	static const unsigned int m_INITIAL_MAX_MARKER = 3;
	static const int m_ID_MAIN_MARKER = 809;
	static const int m_ID_TURRET_MARKER = 679;
	static const int m_ID_MIRROR_MARKER = 666;
	static const int m_ID_CADENCOR_MARKER = 173;
	const std::string m_WINDOW_TITLE;
	
	//Game attribute
	int m_GameStatus;
	game::LifeBar m_LifeBar;
	SoundManager m_SoundManager;
	WebcamManager m_WebcamManager;
	
	//Wave transition
	unsigned int m_WaveTransitionCounter;
	
	//Scene Entities
	unsigned int m_WaveNumber;
	unsigned int m_BossWaveNumber;
	bool m_BossWaveFlag;
	
	unsigned int m_EnemiesToKill;
	unsigned int m_MaxMarker;
	game::Board m_Board;
	std::vector<renderer::Light> m_Lights;
	std::list<game::EnemyUnit> m_Enemies;
	std::vector<game::DefenseUnit> m_DefenseUnit;
	std::vector<game::Barrier> m_Barriers;
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
	
	//PAUSE METHODS
	//Capture markers
	void captureMarkers();
	//Compute correct position of markers
	void computePosOfMarker(aruco::Marker& currentMarker, glm::vec3& posMark, glm::vec3& rotMark, double& thetaY)	;
	//clear object and ground units
	void deleteGameObjects();
	//compute ground weight and init turrets
	void initWeightsAndUnits();
	
	
	//*****************************
	//Private game methods
	//*****************************
	
	//Wave methods
	void launchNextWaveTransition();
	void updateWaveTransition();
	//Global game methods
	void initWave(unsigned int waveNumber, bool bossWave);
	void updateEnemy(game::EnemyUnit & enemy);
	void updateGame();
	void startGame();
	void restartGame();
	//Barrier Methods
	void initBarrier();
	void removeRandomBarrier();
	
public:
	//Public attribute
  	static const size_t m_WINDOW_WIDTH = 1024;
	static const size_t m_WINDOW_HEIGHT = 768;
	
	//Constructor & Destructor
	Application(std::string windowTitle, int argc, char ** argv);
	~Application();
	
	//Applciation public methods
	void loop();
};
}

#endif //Application .hpp