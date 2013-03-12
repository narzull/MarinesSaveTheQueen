#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include <time.h>

#include "../include/api/Application.hpp"
#include "../include/api/Tools.hpp"

namespace api{
	//Constructor
	Application::Application(std::string windowTitle, int argc, char** argv): m_WINDOW_TITLE(windowTitle), m_GameStatus(GAME_STATUS_LAUNCH), m_Done(false){
		
		//Init the webcam manager
		bool initWebcam = m_WebcamManager.initWebcamManager(argc, argv);
		if(!initWebcam){
		  exit(1);
		}
		m_Camera.setProjection(m_WebcamManager.getProjectionMatrix(m_WINDOW_WIDTH, m_WINDOW_HEIGHT));
		
		//Init the SDL Flags
		initSDLFlags();
		//Init variables at the beginning
		//Init the rand seed
		srand(time(NULL));
		//Creating the renderer
		m_GLRenderer = new renderer::GLRenderer(m_WINDOW_WIDTH, m_WINDOW_HEIGHT);
		//Init some GL options
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE); //Enable backface culling
		glCullFace(GL_BACK);   //Cull front faces
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//Init the application model
		initApplication();
	}
	
	//Destructor
	Application::~Application(){
		//Delete dynamic attributes
		delete m_GLRenderer;
	}
	
	//Main Looping function
	void Application::loop(){
		while(!m_Done) {
			Uint32 start = SDL_GetTicks();
			
			//GAME LAUNCHING CODE
			if(m_GameStatus == GAME_STATUS_LAUNCH){
			  m_GLRenderer->renderBeginScreen();
			}
			else{
			  
			  //GAME RUNNING CODE
			  if(!m_Pause && m_GameStatus == GAME_STATUS_RUNNING){
			    //Update the frame count 
			    m_FrameCount++;
			    updateGame();
			    m_GLRenderer->renderGame(m_LifeBar, m_Lights, m_Board, m_Barriers, m_DefenseUnit, m_Turrets, m_Enemies, m_Camera);
			  }
			  else if(m_Pause && m_GameStatus == GAME_STATUS_RUNNING){
			      
			     //suppress existing object before detection
			     deleteGameObjects();
			     
			     //capture markers and create adapted units
			     captureMarkers();
			     
			  }
			  
			  //GAME WAVE TRANSITION CODE
			  if(m_GameStatus == GAME_STATUS_WAVE_TRANSITION){
			    if(m_WaveTransitionCounter < (unsigned int)60){
			      m_GLRenderer->renderWaveScreen();
			    }else{
			      m_GLRenderer->renderGoScreen();
			    }
			    updateWaveTransition();
			  }
			  
			  //GAME ENDING CODE
			  if(m_GameStatus == GAME_STATUS_END){
			    m_GLRenderer->renderEndScreen();
			  }
			}
			
			SDL_GL_SwapBuffers();
			
			//Events
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				/*Event*/
				handleEvent(e);
			}
			
			//CAMERA MOVEMENT CODE
			//if(m_GameStatus == GAME_STATUS_RUNNING && !m_Pause)moveCameraInApplication();
			SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
			SDL_WarpMouse(m_WINDOW_WIDTH/2.0, m_WINDOW_HEIGHT/2.0);
			SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
			
			Uint32 end = SDL_GetTicks();
			int minLoopTime = 1000/FRAMES_PER_SECOND;
			int ellapseTime = end - start;
			if(ellapseTime < minLoopTime)SDL_Delay(minLoopTime-ellapseTime);
		}
		std::cout << "---------------------------------" << std::endl;
		std::cout << "GAME STOP" << std::endl;
		SDL_Quit();
	}
	
	
	//capture images and do the detecting process of markers
	void Application::captureMarkers(){
		
		//capture images from webcam
		const cv::Mat* webcamImage = m_WebcamManager.grabCurrentImage();
		
		//container of aruco markers
		std::vector<aruco::Marker> markers;
		
		//detect markers
		m_WebcamManager.grabMarkersInCurrentImage(markers);
		
		std::cout << "SIIIIZE OF MARKER VECTOR " << markers.size()  << std::endl;
		
		//if any marker is detected
		if(markers.size() > 0){
			
			//modelview matrix for OpenGL
			double modelview[16];
			
			//find the main marker
			aruco::Marker* mainMarker = NULL;
			glm::mat4 modelViewMatrix;
			
			for(unsigned int i = 0 ; i < markers.size(); ++i){
			  //main marker was detected
			  if(markers[i].id == m_ID_MAIN_MARKER){
			    
			    //get the main marker
			    mainMarker = &markers[i];
			    
			    //update the camera according to the main marker
			    mainMarker->glGetModelViewMatrix(modelview);
			    tools::transformToMatrix(modelview, modelViewMatrix);
			    m_Camera.setView(modelViewMatrix);
			    
			    markers.erase(markers.begin()+i);
			  }
			  else
			    std::cout << "ANOTHER MARKER DETECTED" << std::endl;
			}
			
			//if the main marker has been found
			if(mainMarker != NULL){
			  
			    //ground unit coord
			    int x,z;
			    
			    //for each detected marker
			    //for(unsigned int j = 0 ; j < markers.size() ; ++j){
			      for(unsigned int j = 0 ; j < markers.size() ; ++j ){    
				    //init vecs
				    glm::vec3 posMark = glm::vec3();
				    glm::vec3 rotMark = glm::vec3();
				    
				    //angle of rotation of the turret
				    double thetaY;
				    
				    //get transformation datas
				    computePosOfMarker(markers[j],posMark,rotMark,thetaY);
				    
				    //adapt the scale and units
				    x = posMark.x * 2.5 ;
				    z = posMark.z * 2.5 ;
				    glm::vec3 rotation(0,thetaY*180/M_PI,0);
				    
				    //find the correct ground unit
				    std::pair<unsigned int, unsigned int> coordCenter = m_Board.getCentralGroundUnit()->getGroundUnitCoord();
				    //std::cout << "GROUND UNIT x =   " << x+coordCenter.first << " - z = " << z+coordCenter.second << std::endl;
				    if( !m_Board.getGroundUnitFromBoard(x+coordCenter.first,z+coordCenter.second)->isOccupied() && j < m_MaxMarker){
				      if(markers[j].id == m_ID_TURRET_MARKER ){
					  //create the correct turret with good transformation
					  game::Turret newTurret = game::Turret(rotation,m_Board.getGroundUnitFromBoard(x+coordCenter.first,z+coordCenter.second));
				      
					  //add the turret to the vector of turrets
					  m_Turrets.push_back(newTurret);
				      }
				      
				      else if(markers[j].id == m_ID_CADENCOR_MARKER ){
					  //create the cadencor with good transformation
					  game::DefenseUnit newCadencor = game::DefenseUnit(rotation,m_Board.getGroundUnitFromBoard(x+coordCenter.first,z+coordCenter.second)
					    ,game::DefenseUnit::s_DEFENSEUNIT_CADENCOR_TYPE);
				      
					  //add the turret to the vector of turrets
					  m_DefenseUnit.push_back(newCadencor);
				      }
				      
				      else if(markers[j].id == m_ID_MIRROR_MARKER ){
					  //create the cadencor with good transformation
					  game::DefenseUnit newMirror = game::DefenseUnit(rotation,m_Board.getGroundUnitFromBoard(x+coordCenter.first,z+coordCenter.second)
					    ,game::DefenseUnit::s_DEFENSEUNIT_MIRROR_TYPE);
				      
					  //add the turret to the vector of turrets
					  m_DefenseUnit.push_back(newMirror);
				      }
				    }
				  }
			      
			      //init all game object detected
			      for(std::vector<game::Turret>::iterator it = m_Turrets.begin(); it != m_Turrets.end(); ++it){
					(*it).initFromOtherDefenseUnit(m_DefenseUnit);
			      }
			      
			}
		  
		  
		}
		
		m_GLRenderer->renderPause(m_LifeBar, m_Board, m_Barriers, m_DefenseUnit, m_Turrets, m_Enemies, webcamImage, m_Camera);
	  
	}
	
	// find correct datas from marker detection to use them in opengl world
	void Application::computePosOfMarker(aruco::Marker& currentMarker, glm::vec3& posMark, glm::vec3& rotMark, double& thetaY){
	  
	   double modelviewCurrentMarker[16];
	   glm::mat4 modelViewMatrixCurrentMarker;
	   glm::mat4 ViewCamera = m_Camera.getView();
	   
	   //get the modelview matrix of the current marker
	   currentMarker.glGetModelViewMatrix(modelviewCurrentMarker);
	   tools::transformToMatrix(modelviewCurrentMarker, modelViewMatrixCurrentMarker);
	   
	   //model matrix of the current marker by mult inverse matrix View of the camera 
	   //and model view matrix of the current marker
	   glm::mat4 modelMarker = glm::inverse(ViewCamera) * modelViewMatrixCurrentMarker;
	   
	   // translation vector = last row of the model matrix
	   posMark = glm::vec3(modelMarker[3][0],modelMarker[3][1],modelMarker[3][2]);
	   
	   // sin Y = r02 in model matrix
	   double sinY = modelMarker[0][2];
	   thetaY = asin(sinY);
	   
	   //to find in which part of the trigonometric circle we are (left or right) 
	   double thetaX = atan2(-modelMarker[1][2],modelMarker[2][2]);
	   double cosX = cos(thetaX);
	   
	   //magic
	   double signeCosY = -cosX;
	   
	   //find the correct angle according to the sign of the cosinus
	   if(signeCosY < 0){
	     if(sinY > 0){
		thetaY = M_PI - abs(asin(sinY));
	     }
	     else
	        thetaY = - M_PI + abs(asin(sinY));
	   }
	   
	   //tronc the angle
	   if(thetaY > -3*M_PI/4 && thetaY < -M_PI/4)
	      thetaY = -M_PI/2;
	   else if(thetaY < M_PI/4 && thetaY > -M_PI/4)
	      thetaY = 0;
	   else if(thetaY < 3*M_PI/4 && thetaY > M_PI/4)
	      thetaY = M_PI/2;
	   else if(thetaY > 3*M_PI/4 || thetaY < -3*M_PI/4)
	      thetaY = M_PI;
	   else;	//keep thetaY like it is
	   
	}
	
	void Application::deleteGameObjects(){
	    
	    //CLEAR THE CURRENT TURRETS AND THE GROUND UNIT
		for(std::vector<game::Turret>::iterator it = m_Turrets.begin(); it != m_Turrets.end(); ++it){
		  (*it).freeGroundUnit();
		}
		m_Turrets.clear();
	
	    //CLEAR THE CURRENT DEFENSE UNIT AND THE GROUND UNIT
		for(std::vector<game::DefenseUnit>::iterator it = m_DefenseUnit.begin(); it != m_DefenseUnit.end(); ++it){
		  (*it).freeGroundUnit();
		}
		m_DefenseUnit.clear();
	     
	}
	
	void Application::initApplication(){
		//Init some game variables
		m_WaveNumber = 1;
		m_BossWaveNumber = 1;	
		m_BossWaveFlag = false;
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
		m_MaxMarker = m_INITIAL_MAX_MARKER;
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
					if(m_GameStatus == GAME_STATUS_RUNNING) m_Pause = !m_Pause;
					break;
				case SDLK_r :
					if(m_GameStatus == GAME_STATUS_END) restartGame();
					if(m_GameStatus == GAME_STATUS_LAUNCH) startGame();
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
	void Application::initWave(unsigned int waveNumber, bool bossWave){
	    float enemiesSpeed;
	    unsigned int enemiesType;
	    
	    if(!bossWave){
	      std::cout << "---------------------------------" << std::endl;
	      std::cout << "LAUNCHING WAVE " << waveNumber << std::endl;
	      //Launching the music
	      if(waveNumber == 1)m_SoundManager.launchBackGroundMusic("./audio/Sea-Of-Grass.ogg");
	      if(waveNumber == 3)m_SoundManager.launchBackGroundMusic("./audio/Lords-Of-The-Sky.ogg");
	      if(waveNumber == 6)m_SoundManager.launchBackGroundMusic("./audio/Surrounded.ogg");
	      //Setting the wave informations
	      m_EnemiesToKill = rand()%(5 * waveNumber + 20) + 5 * waveNumber;
	      enemiesSpeed = 0.02*(waveNumber/4.0);
	      m_MaxMarker = m_INITIAL_MAX_MARKER + (waveNumber - 1);
	      enemiesType = ENEMY_CLASSIC;
	    }
	    else{
	      std::cout << "---------------------------------" << std::endl;
	      std::cout << "LAUNCHING BOSS WAVE " << waveNumber << std::endl;
	      m_EnemiesToKill = waveNumber;
	      enemiesSpeed = 0.025;
	      enemiesType = ENEMY_BOSS;
	    }
	    //Init the enemy list
	    const game::GroundUnit * centralGroudUnit = m_Board.getCentralGroundUnit();
	    std::pair<unsigned int, unsigned int> centralCoord = centralGroudUnit->getGroundUnitCoord();
	    unsigned int enemyCpt = 0;
	    while(enemyCpt < m_EnemiesToKill){
	      bool isValid = false;
	      int tryCpt = 0;
	      //Getting random positions to place the enemy unit
	      do{
		game::GroundUnit * randomGroundUnit = m_Board.getRandomGroundUnit();
		if(!randomGroundUnit->isOccupied()){
		  std::pair<unsigned int, unsigned int> coord = randomGroundUnit->getGroundUnitCoord();
		  if(coord.first < centralCoord.first - game::Board::s_BOARD_DISTANCE_AROUND_CENTER || coord.first > centralCoord.first + game::Board::s_BOARD_DISTANCE_AROUND_CENTER){
		    if(coord.second < centralCoord.second - game::Board::s_BOARD_DISTANCE_AROUND_CENTER || coord.second > centralCoord.second + game::Board::s_BOARD_DISTANCE_AROUND_CENTER){
		      isValid = true;
		      m_Enemies.push_front(game::EnemyUnit(enemiesType, randomGroundUnit, enemiesSpeed));
		    }
		  }
		}
		++tryCpt;
	      }while(!isValid && tryCpt < 3);
	      if(!isValid){
		--m_EnemiesToKill;
	      }
	      else{
		++enemyCpt;
	      }  
	    }
	    std::cout << "Ennemies to kill : " << m_EnemiesToKill << std::endl;
	    std::cout << "Enemies number : " << m_Enemies.size() << std::endl;
	    std::cout << "Available Marker : " << m_MaxMarker << std::endl;  
	    //std::cout << m_Enemies.begin()->getWalkAnimationFrameID() << std::endl;
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
	  
	  if(rayVector.size() != 0) m_SoundManager.playRandomLaserSound();
	  if(m_Enemies.size() != 0 && rand()%250==0) m_SoundManager.playRandomZombieSound();
	  
	  //Updating the ennemies
	  std::list<game::EnemyUnit>::iterator enemy = m_Enemies.begin();
	  while(enemy != m_Enemies.end()){
	      
	      //Getting related ground unit informations
	      game::GroundUnit * localGroundUnit = (*enemy).getGroundUnitToReach();
	      std::pair<unsigned int, unsigned int> localCoord = localGroundUnit->getGroundUnitCoord();
	    
	      //Verifying if the enemy is destructed
	      bool deleteEnemy = false;
	      for(std::vector<game::Ray>::const_iterator ray = rayVector.begin(); ray != rayVector.end(); ++ray){
		std::pair<unsigned int, unsigned int> begin = (*ray).getBeginningCoord();
		std::pair<unsigned int, unsigned int> end = (*ray).getEndingCoord();
	      
		//Cheking if the local ground unit is in the ray
		if((localCoord.first >= begin.first && localCoord.first <= end.first) ||(localCoord.first <= begin.first && localCoord.first >= end.first)){
		  if((localCoord.second >= begin.second && localCoord.second <= end.second) ||(localCoord.second <= begin.second && localCoord.second >= end.second)){
		      if(enemy->shoot())deleteEnemy = true;
		  }
		}
	      }
	      //If the enemy must be deleted
	      if(deleteEnemy){
		--m_EnemiesToKill;
		localGroundUnit->setOccupied(false);
		enemy = m_Enemies.erase(enemy);
		continue;
	      }
	      //Updating the enemy
	      updateEnemy((*enemy));
	      ++enemy;
	  }
	  
	  //Updating the game info
	  m_LifeBar.update();
	  if(!m_LifeBar.isAlive())m_GameStatus = GAME_STATUS_END;
	  
	  if(m_EnemiesToKill == 0){
	    launchNextWaveTransition();
	  }
	  
	  //m_Board.printGroundUnitsOccupation();
	}
	
	void Application::updateEnemy(game::EnemyUnit & enemy){
	  enemy.updateCounter();
	  int action = enemy.getAction();
	  if(action == ENEMY_WALKING){
	    enemy.walk();
	  }
	  else if(action == ENEMY_WAITING){;
	    game::GroundUnit * currentGroundUnit = enemy.getGroundUnitToReach();
	    std::vector<game::GroundUnit *> neighbourGroundUnit;
	    bool isBlocked = m_Board.getNextGroundUnit(currentGroundUnit, neighbourGroundUnit);
	    if(isBlocked && currentGroundUnit->getWeight() <= (int)game::Board::s_BOARD_DISTANCE_AROUND_CENTER){
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
	  else if(action == ENEMY_FIRING){
	    m_LifeBar.SubstractLife(enemy.getForce());
	  }
	}
	
	void Application::restartGame(){
	  //Destroying the game variables
	  m_Lights.clear();
	  m_Enemies.clear();
	  m_Turrets.clear();
	  m_DefenseUnit.clear();
	  m_Barriers.clear();
	  //Restarting some elements
	  m_LifeBar.restart();
	  m_Board.restartAllBoard();
	  //Init a new application
	  initApplication();
	  startGame();
	}
	
	void Application::startGame(){
	  std::cout << "---------------------------------" << std::endl;
	  std::cout << "GAME START" << std::endl;
	  
	  //Set some game unity
	  m_Lights.push_back(renderer::Light(glm::vec4(-1.0,-1.0,-1.0,0.0), glm::vec3(0.3,0.3,1.0), 1.0));
	  m_Lights.push_back(renderer::Light(glm::vec4(2.0,-0.3,2.0,0.0), glm::vec3(1.0,0.5,0.5), 2.0));
	  //Init some defense units
	  game::GroundUnit * turretGroundUnit = m_Board.getGroundUnitFromBoard(10,10);
	  if(!turretGroundUnit->isOccupied()){
	    m_DefenseUnit.push_back(game::DefenseUnit(glm::vec3(0.0, 0.0, 0.0), turretGroundUnit, game::DefenseUnit::s_DEFENSEUNIT_CADENCOR_TYPE));
	  }   
	  turretGroundUnit = m_Board.getGroundUnitFromBoard(8,5);
	  if(!turretGroundUnit->isOccupied()){
	    m_DefenseUnit.push_back(game::DefenseUnit(glm::vec3(0.0, 0.0, 0.0), turretGroundUnit, game::DefenseUnit::s_DEFENSEUNIT_CADENCOR_TYPE));
	  }   
	  turretGroundUnit = m_Board.getGroundUnitFromBoard(7,9);
	  if(!turretGroundUnit->isOccupied()){
	    m_DefenseUnit.push_back(game::DefenseUnit(glm::vec3(0.0, 90.0, 0.0), turretGroundUnit, game::DefenseUnit::s_DEFENSEUNIT_MIRROR_TYPE));
	  }
	  turretGroundUnit = m_Board.getGroundUnitFromBoard(10,9);
	  if(!turretGroundUnit->isOccupied()){
	    m_Turrets.push_back(game::Turret(glm::vec3(0.0, -180, 0.0), turretGroundUnit));
	    m_Turrets[m_Turrets.size()-1].initFromOtherDefenseUnit(m_DefenseUnit);
	  }
	  turretGroundUnit = m_Board.getGroundUnitFromBoard(6,7);
	  if(!turretGroundUnit->isOccupied()){
	    m_Turrets.push_back(game::Turret(glm::vec3(0.0, 0.0, 0.0), turretGroundUnit));
	    m_Turrets[m_Turrets.size()-1].initFromOtherDefenseUnit(m_DefenseUnit);
	  }
	  turretGroundUnit = m_Board.getGroundUnitFromBoard(9,6);
	  if(!turretGroundUnit->isOccupied()){
	    m_Turrets.push_back(game::Turret(glm::vec3(0.0, -90.0, 0.0), turretGroundUnit));
	    m_Turrets[m_Turrets.size()-1].initFromOtherDefenseUnit(m_DefenseUnit);
	  }
	  
	  for(std::vector<game::DefenseUnit>::const_iterator unit = m_DefenseUnit.begin(); unit != m_DefenseUnit.end(); ++unit){
	    if((*unit).getType() == game::DefenseUnit::s_DEFENSEUNIT_CADENCOR_TYPE){
	      glm::vec3 pos = (*unit).getPosition();
	      m_Lights.push_back(renderer::Light(glm::vec4(pos.x, 0.5, pos.z,1.0), glm::vec3(0.3,1.0,0.3), 4.0));  
	    }
	  }
	  
	  //Init the barrier in the game
	  initBarrier();
	  //Computing the ground unit weight
	  m_Board.computeGroundUnitsWeightFromCenter();
	  //Initialize the current wave
	  initWave(m_WaveNumber, false);
	  //Changing game status
	  m_GameStatus = GAME_STATUS_RUNNING;
	}
	
	void Application::initBarrier(){
	  unsigned int xBegin = 4;
	  unsigned int xEnd = 13;
	  unsigned int zBegin = 4;
	  unsigned int zEnd = 13;
	  std::cout << xBegin << " " << xEnd << std::endl;
	  for(unsigned int i = zBegin; i != zEnd; ++i){
	    //For first and last line
	    if(i == zBegin || i == zEnd-1){
	      for(unsigned int j = xBegin; j != xEnd; ++j){
		float angle;
		if(i == zBegin) angle = 0;
		if(i == zEnd - 1) angle = 180;
		game::GroundUnit * localGroundUnit = m_Board.getGroundUnitFromBoard(j,i);
		m_Barriers.push_back(game::Barrier(glm::vec3(0,angle,0), localGroundUnit));
	      }
	    }//For the other lines
	    else{
	      game::GroundUnit * localGroundUnit = m_Board.getGroundUnitFromBoard(xBegin,i);
	      m_Barriers.push_back(game::Barrier(glm::vec3(0,90,0), localGroundUnit));
	      localGroundUnit = m_Board.getGroundUnitFromBoard(xEnd-1,i);
	      m_Barriers.push_back(game::Barrier(glm::vec3(0,-90,0), localGroundUnit));
	    }
	  }
	  std::random_shuffle(m_Barriers.begin(), m_Barriers.end());
	  for(unsigned int i = 0; i < m_INITIAL_NUMBER_OF_DOWN_BARRIER; ++i){
	    removeRandomBarrier();
	  }
	}
	
	void Application::removeRandomBarrier(){
	  game::GroundUnit * localGroundUnit = m_Barriers[m_Barriers.size()-1].getRelatedGroundUnit();
	  localGroundUnit->setOccupied(false);
	  localGroundUnit->setWeight(5000);
	  m_Barriers.pop_back();
	}
	
	void Application::launchNextWaveTransition(){
	    std::cout << "---------------------------------" << std::endl;
	    std::cout << "WAVE " << m_WaveNumber << " FINISHED" << std::endl;
	    
	    //Delete a barrier
	    removeRandomBarrier();
	    m_Board.resartAllBoardExceptObstacle();
	    m_Board.computeGroundUnitsWeightFromCenter();
	    //m_Board.printGroundUnitsWeight();
	    
	    //Load the next wave
	    if(m_BossWaveFlag){
	      ++m_BossWaveNumber;
	      m_BossWaveFlag = false;
	      initWave(m_WaveNumber, false);
	    }
	    else{
	      ++m_WaveNumber;
	      if(m_WaveNumber%2==1 && m_WaveNumber != 1){
		m_BossWaveFlag = true;
		initWave(m_BossWaveNumber, true);
	      }
	      else{
		  initWave(m_WaveNumber, false);
	      }
	    }
	    
	    m_GameStatus = GAME_STATUS_WAVE_TRANSITION;
	    m_WaveTransitionCounter = 0;
	    m_Pause = false;
	  
	}
	
	void Application::updateWaveTransition(){
	    ++m_WaveTransitionCounter;
	    if(m_WaveTransitionCounter == m_WAVE_TRANSITION_FRAME_DURATION){
	      m_GameStatus = GAME_STATUS_RUNNING;
	      m_Pause = true;
	    }
	}
}//namespace api