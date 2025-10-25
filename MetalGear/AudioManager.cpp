#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
    engine = nullptr;
    currentMusic = nullptr;
    currentMusicName = "";
    musicVolume = 0.05f;
    soundVolume = 0.05f;
}

AudioManager::~AudioManager()
{
    cleanup();
}

void AudioManager::init()
{
    engine = createIrrKlangDevice();

    if (!engine)
    {
        std::cout << "Error: Could not initialize audio engine" << std::endl;
        return;
    }

    std::cout << "Audio engine initialized successfully" << std::endl;
    loadAudioPaths();
}

void AudioManager::cleanup()
{
    if (currentMusic)
    {
        currentMusic->stop();
        currentMusic->drop();
        currentMusic = nullptr;
    }

    if (engine)
    {
        engine->drop();
        engine = nullptr;
    }
}

void AudioManager::loadAudioPaths()
{
    musicPaths["music_menu"] = "music/music_menu.mp3";
    musicPaths["music_overworld"] = "music/music_overworld.mp3";
    musicPaths["music_cave"] = "music/music_cave.mp3";
    musicPaths["music_mansion"] = "music/music_mansion.mp3";
    musicPaths["music_boss"] = "music/music_boss.mp3";
    musicPaths["music_gameover"] = "music/music_gameover.mp3";

    soundPaths["sound_punch"] = "music/sound_punch.mp3";
    soundPaths["sound_gothit"] = "music/sound_gothit.mp3";
    soundPaths["sound_pistol"] = "music/sound_pistol.mp3";
    soundPaths["sound_nopistol"] = "music/sound_nopistol.mp3";
    soundPaths["sound_shot"] = "music/sound_shot.mp3";
    soundPaths["sound_get_item"] = "music/sound_get_item.mp3";
    soundPaths["sound_pikachu"] = "music/sound_pikachu.mp3";
    soundPaths["sound_geodude"] = "music/sound_geodude.mp3";
    soundPaths["sound_charizard"] = "music/sound_charizard.mp3";
    soundPaths["sound_fireball"] = "music/sound_fireball.mp3";
    soundPaths["sound_reload"] = "music/sound_reload.mp3";
    soundPaths["sound_heal"] = "music/sound_heal.mp3";
    soundPaths["sound_button"] = "music/sound_button.mp3";
}

void AudioManager::playMusic(const std::string& musicName, bool loop)
{
    if (!engine) return;

    if (currentMusicName == musicName && currentMusic && !currentMusic->isFinished())
        return;


    if (currentMusic)
    {
        currentMusic->stop();
        currentMusic->drop();
        currentMusic = nullptr;
    }


    if (musicPaths.find(musicName) != musicPaths.end())
    {
        currentMusic = engine->play2D(musicPaths[musicName].c_str(), loop, false, true);
        if (currentMusic)
        {
            currentMusic->setVolume(musicVolume);
            currentMusicName = musicName;
            std::cout << "Playing music: " << musicName << std::endl;
        }
    }
    else
    {
        std::cout << "Music not found: " << musicName << std::endl;
    }
}

void AudioManager::stopMusic()
{
    if (!engine || !currentMusic) return;

    currentMusic->stop();
    currentMusic->drop();
    currentMusic = nullptr;
    currentMusicName = "";
}

void AudioManager::pauseMusic()
{
    if (!engine || !currentMusic) return;
    currentMusic->setIsPaused(true);
}

void AudioManager::resumeMusic()
{
    if (!engine || !currentMusic) return;
    currentMusic->setIsPaused(false);
}

void AudioManager::setMusicVolume(float volume)
{
    musicVolume = volume;
    if (currentMusic)
        currentMusic->setVolume(musicVolume);
}

void AudioManager::playSound(const std::string& soundName, float volume)
{
    if (!engine) return;

    if (soundPaths.find(soundName) != soundPaths.end())
    {
        ISound* sound = engine->play2D(soundPaths[soundName].c_str(), false, false, true);
        if (sound)
        {
            sound->setVolume(volume * soundVolume);
            sound->drop();
        }
    }
    else
    {
        std::cout << "Sound not found: " << soundName << std::endl;
    }
}

void AudioManager::setSoundVolume(float volume)
{
    soundVolume = volume;
}

void AudioManager::updateMusicForMap(int mapId)
{
    if (!engine) return;

    std::string newMusic = "";

    if (mapId >= 1 && mapId <= 6 || mapId == 9)
    {
        newMusic = "music_overworld";
    }
    else if (mapId == 7 || mapId == 8)
    {
        newMusic = "music_cave";
    }
    else if (mapId >= 10 && mapId <= 13)
    {
        newMusic = "music_mansion";
    }
    else if (mapId == 14)
    {
        newMusic = "music_boss";
    }

    if (!newMusic.empty() && newMusic != currentMusicName)
    {
        playMusic(newMusic, true);
    }
}