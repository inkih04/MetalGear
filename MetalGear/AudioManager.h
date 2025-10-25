#ifndef _AUDIO_MANAGER_INCLUDE
#define _AUDIO_MANAGER_INCLUDE

#include <irrKlang.h>
#include <string>
#include <map>

using namespace irrklang;

class AudioManager
{
public:
    static AudioManager& instance()
    {
        static AudioManager AM;
        return AM;
    }

    void init();
    void cleanup();

    void playMusic(const std::string& musicName, bool loop = true);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void setMusicVolume(float volume); 

    void playSound(const std::string& soundName, float volume = 1.0f);
    void setSoundVolume(float volume); 

    
    void updateMusicForMap(int mapId);

private:
    AudioManager();
    ~AudioManager();

    ISoundEngine* engine;
    ISound* currentMusic;

    std::map<std::string, std::string> musicPaths;
    std::map<std::string, std::string> soundPaths;

    std::string currentMusicName;
    float musicVolume;
    float soundVolume;

    void loadAudioPaths();
};

#endif // _AUDIO_MANAGER_INCLUDE
