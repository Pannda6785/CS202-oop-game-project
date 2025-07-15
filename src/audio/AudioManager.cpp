#include "AudioManager.hpp"
#include <iostream>

AudioManager::~AudioManager() {
    unload();
}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::init() {
    unload();
    Sound tickSound = LoadSound("../assets/raw_sounds/sound_tick.wav");
    sounds["tick"] = tickSound;
    
}

void AudioManager::play(const std::string& soundName) {
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        PlaySound(it->second);
    } else {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
}

void AudioManager::unload() {
    for (auto& pair : sounds) {
        UnloadSound(pair.second);
    }
    sounds.clear();
    initialized = false;
}