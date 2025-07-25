#include "AudioManager.hpp"
#include <iostream>

AudioManager::~AudioManager() {
    unload();
}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::setMasterVolume(float volume) {
    masterVolume = volume;
    SetMasterVolume(masterVolume);
}

void AudioManager::setMusicVolume(float volume) {
    musicVolume = volume;
    SetMusicVolume(themeMusic, musicVolume);
}

void AudioManager::setSfxVolume(float volume) {
    sfxVolume = volume;
    for (auto& pair : sounds) {
        SetSoundVolume(pair.second, sfxVolume);
    }
}

float AudioManager::getMasterVolume() const {
    return masterVolume;
}

float AudioManager::getMusicVolume() const {
    return musicVolume;
}

float AudioManager::getSfxVolume() const {
    return sfxVolume;
}

void AudioManager::init() {
    unload();
    Sound clickButtonSound = LoadSound("../assets/audio/sound_tick.wav");
    sounds["ClickButton"] = clickButtonSound;
    Sound menuCursorSound = LoadSound("../assets/audio/sound_menu_cursor.wav");
    sounds["MenuCursor"] = menuCursorSound;
}

void AudioManager::loadThemeMusic(const std::string& musicPath) {
    if (initializedThemeMusic) {
        UnloadMusicStream(themeMusic);
    }
    themeMusic = LoadMusicStream(musicPath.c_str());
    initializedThemeMusic = true;
}

void AudioManager::unloadThemeMusic() {
    UnloadMusicStream(themeMusic);
    initializedThemeMusic = false;
}

void AudioManager::playSound(const std::string& soundName) {
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        PlaySound(it->second);
    } else {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
}

void AudioManager::update(float dt) {
    if(!IsWindowFocused()){
        SetMusicVolume(themeMusic, 0.0f);
        return;
    } else {
        SetMusicVolume(themeMusic, musicVolume);
    }
    if (IsMusicStreamPlaying(themeMusic)) {
        UpdateMusicStream(themeMusic);
    } else {
        PlayMusicStream(themeMusic);
        themeMusic.looping = true;
    }
}

void AudioManager::unload() {
    for (auto& pair : sounds) {
        UnloadSound(pair.second);
    }
    sounds.clear();
    initialized = false;
}