#include "../include/api/SoundManager.hpp"

#include <iostream>
namespace api{
  
  SoundManager::SoundManager():m_BackgroundMusic(NULL), m_LaserSound(NULL), m_ZombieSound(NULL){
    //Init the sound librairy
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SOUND MANAGER : Initialisation" << std::endl;
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
	std::cout << "FAILURE : Impossible to init : " << Mix_GetError() << std::endl;
    }else{
	std::cout << "SUCCES" << std::endl;
    }
    Mix_AllocateChannels(3);
    loadSound(&m_LaserSound, "./audio/laser_1.ogg");
    loadSound(&m_ZombieSound, "./audio/zombie.ogg");
  }
  
  SoundManager::~SoundManager(){
     //Stop all the sounds
     Mix_HaltChannel(-1);
     //Destroying the background music
     destroySound(&m_BackgroundMusic);
     destroySound(&m_LaserSound);
     destroySound(&m_ZombieSound);
     Mix_CloseAudio();
  };
  
  void SoundManager::launchBackGroundMusic(const std::string & filename){
    //If a background music is running
    if(m_BackgroundMusic != NULL){
      Mix_FadeOutChannel(0, 1000);
    }
    destroySound(&m_BackgroundMusic);
    loadSound(&m_BackgroundMusic, filename);
    if(m_BackgroundMusic != NULL){
      	if(Mix_FadeInChannel(0, m_BackgroundMusic, -1, 1000) == -1){
	  std::cout << "SOUNDMANAGER : Impossible to play : " << filename << std::endl;
	} 
    } 
  }
  
  void SoundManager::playRandomLaserSound()const{
    if(m_LaserSound != NULL){
      	if(Mix_PlayChannel(1, m_LaserSound, 0) == -1){
	  std::cout << "SOUNDMANAGER : Impossible to play : the laser sound" << std::endl;
	}
    } 
  }
  
  void SoundManager::playRandomZombieSound()const{
    if(m_ZombieSound != NULL){
      	if(Mix_PlayChannel(2, m_ZombieSound, 0) == -1){
	  std::cout << "SOUNDMANAGER : Impossible to play : the zombie sound" << std::endl;
	}
    } 
  }
  
  void SoundManager::loadSound(Mix_Chunk ** musicRessource, const std::string & filename){
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SOUND MANAGER : Loading Sound : " << filename << std::endl;
    if(*musicRessource == NULL){
      *musicRessource = Mix_LoadWAV(filename.c_str());
      if(*musicRessource == NULL){
	  std::cout << "SOUNDMANAGER : Impossible to load : " << filename << std::endl;
      }
      else{
	std::cout << "SUCCESS" << std::endl;
      }
    }
    else{
      std::cout << "SoundManager : Trying to load a sound at a non NULL ressource : " << filename << std::endl;
    }
  }
  
  void SoundManager::destroySound(Mix_Chunk ** musicRessource){
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SOUND MANAGER : Destroying Sound " << std::endl;
    if(*musicRessource != NULL){
      Mix_FreeChunk(*musicRessource);
      *musicRessource = NULL;
      if(*musicRessource == NULL) std::cout << "SUCCES" << std::endl;
      else std::cout << "FAILURE" << std::endl;
    }
  }

}//namespace api