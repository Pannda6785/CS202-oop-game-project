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

void AudioManager::play(const std::string& soundName) {
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        PlaySound(it->second);
    } else {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
}

void AudioManager::update(float dt) {
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