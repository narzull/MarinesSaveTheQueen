#include "../include/api/SoundManager.hpp"

#include <iostream>
namespace api{
  
  SoundManager::SoundManager():m_BackgroundMusic(NULL), m_LaserSound1(NULL){
    //Init the sound librairy
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
	std::cout << "SoundManager : Impossible to init : " << Mix_GetError() << std::endl;
    }
    Mix_AllocateChannels(2);
    loadSound(&m_LaserSound1, "./audio/laser_1.ogg");
  }
  
  SoundManager::~SoundManager(){
     //Stop all the sounds
     Mix_HaltChannel(-1);
     //Destroying the background music
     destroySound(&m_BackgroundMusic);
     destroySound(&m_LaserSound1);
     Mix_CloseAudio();
  };
  
  void SoundManager::launchBackGroundMusic(const std::string & filename){
    destroySound(&m_BackgroundMusic);
    loadSound(&m_BackgroundMusic, filename);
    if(m_BackgroundMusic != NULL){
      	if(Mix_PlayChannel(0 ,m_BackgroundMusic, -1) == -1){
	  std::cout << "SoundManager : Impossible to play : " << filename << std::endl;
	} 
    } 
  }
  
  void SoundManager::playRandomLaserSound()const{
    if(m_LaserSound1 != NULL){
      	if(Mix_PlayChannel(1, m_LaserSound1, 0) == -1){
	  std::cout << "SoundManager : Impossible to play : the laser sound" << std::endl;
	} 
    } 
  }
  
  void SoundManager::loadSound(Mix_Chunk ** musicRessource, const std::string & filename){
    if(*musicRessource == NULL){
      *musicRessource = Mix_LoadWAV(filename.c_str());
      if(*musicRessource == NULL){
	  std::cout << "SoundManager : Impossible to load : " << filename << std::endl;
      }
    }
    else{
      std::cout << "SoundManager : Trying to load a sound at a non NULL ressource : " << filename << std::endl;
    }
  }
  
  void SoundManager::destroySound(Mix_Chunk ** musicRessource){
    if(*musicRessource != NULL){
      Mix_FreeChunk(*musicRessource);
      *musicRessource = NULL;
      if(*musicRessource == NULL) std::cout << "SoundManager : Music deleted" << std::endl;
    }
  }

}//namespace api