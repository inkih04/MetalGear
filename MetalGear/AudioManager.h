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

    // Control de música
    void playMusic(const std::string& musicName, bool loop = true);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void setMusicVolume(float volume); // 0.0f a 1.0f

    // Control de efectos de sonido
    void playSound(const std::string& soundName, float volume = 1.0f);
    void setSoundVolume(float volume); // 0.0f a 1.0f

    // Cambio de música según el mapa
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
