#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <string>
#include <map>
#include <raylib.h>

class AudioManager {
public:
    static AudioManager& getInstance();

    // Initialize with a map of sound names to file paths
    void init();

    // Play a sound by its name
    void play(const std::string& soundName);

    // Unload all loaded sounds
    void unload();

private:
    AudioManager() = default;
    ~AudioManager();

    // Prevent copy/move
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    std::map<std::string, Sound> sounds;
    std::map<std::string, std::string> soundPaths;
    bool initialized = false;
};

#endif // AUDIO_MANAGER_HPP