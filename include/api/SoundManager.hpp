#ifndef __SOUNDMANAGER_HPP__
#define __SOUNDMANAGER_HPP__

//SDL mixer includes
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

//Other includes
#include <string>

//Entity class
namespace api {
class SoundManager {
public:
    //Constructor
    SoundManager();
    ~SoundManager();
    
    //Public methods
    void launchBackGroundMusic(const std::string & filename);
    void playRandomLaserSound()const;
protected:
    //Private methods
    void loadSound(Mix_Chunk ** musicRessource, const std::string & filename);
    void destroySound(Mix_Chunk ** musicRessource);
    //Attribute
    //Background music
    Mix_Chunk * m_BackgroundMusic;
    
    //Laser sound
    Mix_Chunk * m_LaserSound1;
};
} // namespace api
#endif // __SOUNDMANAGER_HPP__
