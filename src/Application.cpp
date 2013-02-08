#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include <time.h>

#include "../include/api/Application.hpp"


namespace api{
	//Constructor
	Application::Application(std::string windowTitle, const std::string & param): m_WINDOW_TITLE(windowTitle), m_Done(false){
		//Init the SDL Flags
		initSDLFlags();
		//Init the application model
		initApplication();
		initWave(m_WaveNumber);
	}
	
	//Destructor
	Application::~Application(){
		//Delete dynamic attributes
		delete m_GLRenderer;
		//Delete the Webcam
		cvReleaseCapture(&m_Webcam);
	}
	
	//Main Looping function
	void Application::loop(){
		while(!m_Done) {
			Uint32 start = SDL_GetTicks();

			//Pause 
			m_WebcamFrame = NULL;
			if(!m_Pause){
				//m_WebcamFrame = cvQueryFrame(m_Webcam);
				updateGame();
			}
			// Rendu
			m_GLRenderer->render(m_Pause, m_Lights, m_Board, m_DefenseUnit, m_Turrets, m_Enemies, m_WebcamFrame, m_Camera);
			SDL_GL_SwapBuffers();

			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				/*Event*/
				handleEvent(e);
			}
			
			moveCameraInApplication();
			
			m_FrameCount++;
			SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
			SDL_WarpMouse(m_WINDOW_WIDTH/2.0, m_WINDOW_HEIGHT/2.0);
			SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
			
			Uint32 end = SDL_GetTicks();
			int minLoopTime = 1000/FRAMES_PER_SECOND;
			int ellapseTime = end - start;
			if(ellapseTime < minLoopTime)SDL_Delay(minLoopTime-ellapseTime);
		}
		SDL_Quit();
	}
	
	void Application::initApplication(){
		//Init the rand seed
		srand(time(NULL));  
		//Init some game variables
		m_WaveNumber = 1;		
		//Init some variables
		m_Step = 0.1;
		m_MoveFlagX = 0;
		m_MoveFlagZ = 0;
		m_FrameCount = 0;
		m_AngleLong = 0;
		m_AngleLat = 0;
		m_MousePosX = 0;
		m_MousePosY = 0;
		m_Pause = true;
		m_GLRenderer = new renderer::GLRenderer(m_WINDOW_WIDTH, m_WINDOW_HEIGHT);
		
		//Init the Webcam
		m_Webcam = NULL;
		m_Webcam = cvCaptureFromCAM(CV_CAP_ANY);
		if(m_Webcam == NULL){
			std::cout << "No webcam found" << std::endl;
		}
		
		//Init some GL options
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE); //Enable backface culling
		glCullFace(GL_BACK);   //Cull front faces
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	
	//Init all the required SDL Flags
	void Application::initSDLFlags(){
		int sdlError=SDL_Init(SDL_INIT_EVERYTHING);
		if (sdlError<0) 
			std::cout<<"Unable to init SDL : "<<SDL_GetError()<<std::endl;
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Double buffering
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);	// Depth buffer size of 16-bit
	
		SDL_SetVideoMode(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, m_BYTES_PER_PIXEL, SDL_OPENGL);
		SDL_WM_SetCaption(m_WINDOW_TITLE.c_str(), 0);
		
		//Lock the cursor in the window
		SDL_WM_GrabInput(SDL_GRAB_ON);
	}
	
	//Event function
	void Application::handleEvent(const SDL_Event& event) {
		switch (event.type) {
			// Key presses
			case SDL_KEYDOWN:
				handleKeyEvent(event.key.keysym, true);
				break;
			// Key releases
			case SDL_KEYUP:
				handleKeyEvent(event.key.keysym, false);
				break;
			// Quit event (for example sent when the window is closed)
			case SDL_QUIT:
				m_Done = true;
				break;
			default:
				break;
		}
	}
	
	void Application::handleKeyEvent(const SDL_keysym& keysym, bool down){
		if (down) {
			switch (keysym.sym) {		
				case SDLK_LSHIFT:
					m_Step *= 3;
					break; 
				case SDLK_z :
					m_MoveFlagZ = 1;
					break;
				case SDLK_d :
					m_MoveFlagX = -1;			
					break;
				case SDLK_q :
					m_MoveFlagX = 1;
					break;	
				case SDLK_s :
					m_MoveFlagZ = -1;
					break;
				case SDLK_p :
					m_Pause = !m_Pause;
					break;
				case SDLK_y:
					bool save;
					save = saveScreen();
					std::cout << "Screenshot printed ? = " << save << std::endl;
					break;
				case SDLK_ESCAPE:
					m_Done = true;
					break;
				default:
					break;
			}
		}
		else{
			switch (keysym.sym) {			
				case SDLK_LSHIFT:
					m_Step /= 3;
					break;  
				case SDLK_z :
					m_MoveFlagZ = 0;
					break;
				case SDLK_d :
					m_MoveFlagX = 0;			
					break;
				case SDLK_q :
					m_MoveFlagX = 0;
					break;	
				case SDLK_s :
					m_MoveFlagZ = 0;
					break;
				default:
					break;
			}
		}
	}
	
	//Camera function
	void Application::moveCameraInApplication(){
		SDL_PumpEvents();
		int mouseRelX,mouseRelY;

		#ifdef __APPLE__
		int mistery = 0;
		SDL_GetRelativeMouseState(mistery,&mouseRelX,&mouseRelY);
		#else
		SDL_GetRelativeMouseState(&mouseRelX,&mouseRelY);
		#endif

		if(m_FrameCount < 3){
			mouseRelX = 0;
			mouseRelY = 0;	
		}

		m_MousePosX -= 2.0*mouseRelX/(GLfloat)m_WINDOW_WIDTH;
		m_MousePosY -= 2.0*mouseRelY/(GLfloat)m_WINDOW_HEIGHT;

		glm::vec3 moveVector;
		moveVector.x = -m_MoveFlagX * m_Step;
		moveVector.y = 0.0f;
		moveVector.z = -m_MoveFlagZ * m_Step;

		glm::vec3 angleVector;
		GLfloat angleForWindowWidth=M_PI;
		GLfloat angleForWindowHeight=M_PI/2.0;
		
		m_AngleLong += m_MousePosX*angleForWindowWidth;
		m_AngleLat += m_MousePosY*angleForWindowHeight;

		angleVector.x = m_AngleLat*20.0;
		angleVector.y = m_AngleLong*20.0;
		
		m_Camera.move(moveVector, angleVector);
	}
	
	//Save Screen
	bool Application::saveScreen(){
		//This prevents the images getting padded 
		// when the width multiplied by 3 is not a multiple of 4
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		
		int nSize = m_WINDOW_WIDTH*m_WINDOW_HEIGHT*3;
		// First let's create our buffer, 3 channels per Pixel
		char* dataBuffer = (char*)malloc(nSize*sizeof(char));
		
		if (!dataBuffer) return false;
		
		// Let's fetch them from the backbuffer	
		// We request the pixels in GL_BGR format, thanks to Berzeger for the tip
		glReadPixels((GLint)0, (GLint)0,
				(GLint)m_WINDOW_WIDTH, (GLint)m_WINDOW_HEIGHT,
				GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);
		
		//Now the file creation
		FILE *filePtr = fopen("screen.tga", "wb");
		if (!filePtr) return false;
		
		
		unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
		unsigned char header[6] = { m_WINDOW_WIDTH%256,m_WINDOW_WIDTH/256,
						m_WINDOW_HEIGHT%256,m_WINDOW_HEIGHT/256,
						24,0};
		// We write the headers
		fwrite(TGAheader,	sizeof(unsigned char),	12,	filePtr);
		fwrite(header,	sizeof(unsigned char),	6,	filePtr);
		// And finally our image data
		fwrite(dataBuffer,	sizeof(GLubyte),	nSize,	filePtr);
		fclose(filePtr);
		
		return true; 
	}
	
	//Scene methods
	void Application::initWave(unsigned int waveNumber){
	    //Setting the camera
	    m_Camera.setPosition(glm::vec3(0.0, 1.0, 3.0));
	    
	    m_Lights.push_back(renderer::Light(glm::vec4(-1.0,-1.0,-1.0,0.0), glm::vec3(0.3,0.3,1.0), 1.0));
	    m_Lights.push_back(renderer::Light(glm::vec4(-2.0,0.3,-2.0,1.0), glm::vec3(1.0,0.5,0.5), 5.0));
	    
	    //Computing the ground unit weight
	    m_Board.computeGroundUnitsWeightFromCenter();
	    //m_Board.printGroundUnitsWeight();
	    
	    //Setting the wave informations
	    m_EnemiesToKill = rand()%(50*waveNumber) + 20*waveNumber;
	    float enemiesSpeed = 0.01;
	    
	    //Init the enemy list
	    const game::GroundUnit * centralGroudUnit = m_Board.getCentralGroundUnit();
	    for(unsigned int i = 0; i < m_EnemiesToKill; ++i){
	      bool isValid = false;
	      //Getting random positions to place the enemy unit
	      do{
		game::GroundUnit * randomGroundUnit = m_Board.getRandomGroundUnit();
		if(randomGroundUnit != centralGroudUnit && !randomGroundUnit->isOccupied()){
		  isValid = true;
		  m_Enemies.push_front(game::EnemyUnit(randomGroundUnit, enemiesSpeed));
		}
	      }while(!isValid);
	    }
	    
	    //Init the others defense unit
	    game::GroundUnit * turretGroundUnit = m_Board.getGroundUnitFromBoard(9,14);
	    if(!turretGroundUnit->isOccupied()){
	      m_DefenseUnit.push_back(game::DefenseUnit(glm::vec3(0.0, 0.0, 0.0), turretGroundUnit, DEFENSEUNIT_CADENCOR));
	    }
	    turretGroundUnit = m_Board.getGroundUnitFromBoard(7,14);
	    if(!turretGroundUnit->isOccupied()){
	      m_DefenseUnit.push_back(game::DefenseUnit(glm::vec3(0.0, 0.0, 0.0), turretGroundUnit, DEFENSEUNIT_CADENCOR));
	    }
	    turretGroundUnit = m_Board.getGroundUnitFromBoard(8,11);
	    if(!turretGroundUnit->isOccupied()){
	      m_DefenseUnit.push_back(game::DefenseUnit(glm::vec3(0.0, 0.0, 0.0), turretGroundUnit, DEFENSEUNIT_MIRROR));
	    }
	    
	    turretGroundUnit = m_Board.getGroundUnitFromBoard(11,11);
	    if(!turretGroundUnit->isOccupied()){
	      m_DefenseUnit.push_back(game::DefenseUnit(glm::vec3(0.0, 90.0, 0.0), turretGroundUnit, DEFENSEUNIT_MIRROR));
	    }
	    
	    //Init some turrets
	    turretGroundUnit = m_Board.getGroundUnitFromBoard(8,5);
	    if(!turretGroundUnit->isOccupied()){
	      m_Turrets.push_back(game::Turret(glm::vec3(0.0, -90, 0.0), turretGroundUnit));
	      m_Turrets[m_Turrets.size()-1].initFromOtherDefenseUnit(m_DefenseUnit);
	    }
	    turretGroundUnit = m_Board.getGroundUnitFromBoard(8,14);
	    if(!turretGroundUnit->isOccupied()){
	      m_Turrets.push_back(game::Turret(glm::vec3(0.0, 90, 0.0), turretGroundUnit));
	      m_Turrets[m_Turrets.size()-1].initFromOtherDefenseUnit(m_DefenseUnit);
	    }
	    turretGroundUnit = m_Board.getGroundUnitFromBoard(7,9);
	    if(!turretGroundUnit->isOccupied()){
	      m_Turrets.push_back(game::Turret(glm::vec3(0.0, 0.0, 0.0), turretGroundUnit));
	      m_Turrets[m_Turrets.size()-1].initFromOtherDefenseUnit(m_DefenseUnit);
	    }
	}
	
	void Application::updateGame(){
	  
	  std::vector<game::Ray> rayVector;
	  
	  //Updating the turret
	  for(std::vector<game::Turret>::iterator turret = m_Turrets.begin(); turret != m_Turrets.end(); ++turret){
	      //Updating the current turret
	      (*turret).update();
	      //Getting all rays
	      if((*turret).isFiring()){
		(*turret).getRayVector(rayVector);
	      }
	  }
	  
	  //Updating the ennemies
	  std::list<game::EnemyUnit>::iterator enemy = m_Enemies.begin();
	  while(enemy != m_Enemies.end()){
	      
	      //Getting related ground unit informations
	      game::GroundUnit * localGroundUnit = (*enemy).getGroundUnitToReach();
	      std::pair<unsigned int, unsigned int> localCoord = localGroundUnit->getGroundUnitCoord();
	    
	      //Verifying if the enemy is destructed
	      bool delelteEnemy = false;
	      for(std::vector<game::Ray>::const_iterator ray = rayVector.begin(); ray != rayVector.end(); ++ray){
		std::pair<unsigned int, unsigned int> begin = (*ray).getBeginningCoord();
		std::pair<unsigned int, unsigned int> end = (*ray).getEndingCoord();
	      
		//Cheking if the local ground unit is in the ray
		if((localCoord.first >= begin.first && localCoord.first <= end.first) ||(localCoord.first <= begin.first && localCoord.first >= end.first)){
		  if((localCoord.second >= begin.second && localCoord.second <= end.second) ||(localCoord.second <= begin.second && localCoord.second >= end.second)){
		      delelteEnemy = true;
		  }
		}
	      }
	      //If the enemy must be deleted
	      if(delelteEnemy){
		localGroundUnit->setOccupied(false);
		enemy = m_Enemies.erase(enemy);
		continue;
	      }
	    
	      //Updating the enemy
	      updateEnemy((*enemy));
	      ++enemy;
	  }
	  //m_Board.printGroundUnitsOccupation();
	}
	
	void Application::updateEnemy(game::EnemyUnit & enemy){
	  int action = enemy.getAction();
	  if(action == ENEMY_WALKING){
	    enemy.walk();
	  }
	  else if(action == ENEMY_WAITING){
	    game::GroundUnit * currentGroundUnit = enemy.getGroundUnitToReach();
	    std::vector<game::GroundUnit *> neighbourGroundUnit;
	    bool isBlocked = m_Board.getNextGroundUnit(currentGroundUnit, neighbourGroundUnit);
	    if(isBlocked && currentGroundUnit->getWeight() <= 3){
	      enemy.setAction(ENEMY_FIRING);
	      enemy.autoRotateForFire();
	    }
	    else{
	      std::random_shuffle(neighbourGroundUnit.begin(), neighbourGroundUnit.end() );
	      for(std::vector<game::GroundUnit*>::iterator it = neighbourGroundUnit.begin(); it != neighbourGroundUnit.end(); ++it){
		game::GroundUnit * nextGroundUnit = (*it);
		if(enemy.setGroundUnitToReach(nextGroundUnit)){
		  enemy.setAction(ENEMY_WALKING);
		  break;
		}
	      }
	    }
	  }
	}
}//namespace api