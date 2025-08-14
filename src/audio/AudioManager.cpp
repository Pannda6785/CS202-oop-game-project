#include "AudioManager.hpp"
#include <iostream>
#include <chrono>
#include <thread>

AudioManager::AudioManager() = default;

AudioManager::~AudioManager() {
    stopAudioThread();
    unload();
}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::setMasterVolume(float volume) {
    std::lock_guard<std::mutex> lock(audioMutex);
    masterVolume = volume;
    SetMasterVolume(masterVolume);
}

void AudioManager::setMusicVolume(float volume) {
    std::lock_guard<std::mutex> lock(audioMutex);
    musicVolume = volume;
    if (initializedThemeMusic) {
        SetMusicVolume(themeMusic, musicVolume);
    }
}

void AudioManager::setSfxVolume(float volume) {
    std::lock_guard<std::mutex> lock(audioMutex);
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
    
    {
        std::lock_guard<std::mutex> lock(audioMutex);
        Sound clickButtonSound = LoadSound("../assets/audio/sound_tick.wav");
        sounds["ClickButton"] = clickButtonSound;
        Sound menuCursorSound = LoadSound("../assets/audio/sound_menu_cursor.wav");
        sounds["MenuCursor"] = menuCursorSound;
        Sound confirmSelectChar = LoadSound("../assets/audio/sound_charselect_confirm.wav");
        sounds["ConfirmSelectChar"] = confirmSelectChar;
        Sound charSelectRibbon = LoadSound("../assets/audio/sound_charselect_ribbon.wav");
        sounds["CharSelectRibbon"] = charSelectRibbon;
        Sound hitPlayer = LoadSound("../assets/audio/sound_hit_player.wav");
        sounds["HitPlayer"] = hitPlayer;
        Sound healthBreak = LoadSound("../assets/audio/sound_health_break.wav");
        sounds["HealthBreak"] = healthBreak;
        initialized = true;
    }
    
    // Start the audio thread
    startAudioThread();
}

void AudioManager::loadThemeMusic(const std::string& musicPath) {
    std::lock_guard<std::mutex> lock(audioMutex);
    if (initializedThemeMusic) {
        UnloadMusicStream(themeMusic);
    }
    themeMusic = LoadMusicStream(musicPath.c_str());
    initializedThemeMusic = true;
}

void AudioManager::unloadThemeMusic() {
    std::lock_guard<std::mutex> lock(audioMutex);
    if (initializedThemeMusic) {
        UnloadMusicStream(themeMusic);
        initializedThemeMusic = false;
    }
}

void AudioManager::playSound(const std::string& soundName) {
    std::lock_guard<std::mutex> lock(audioMutex);
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        PlaySound(it->second);
    } else {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
}

void AudioManager::update(float dt) {
    // Main thread update - no longer needed for audio processing
    // Left as a placeholder in case you need it for other purposes
}

void AudioManager::unload() {
    std::lock_guard<std::mutex> lock(audioMutex);
    for (auto& pair : sounds) {
        UnloadSound(pair.second);
    }
    sounds.clear();
    
    if (initializedThemeMusic) {
        UnloadMusicStream(themeMusic);
        initializedThemeMusic = false;
    }
    
    initialized = false;
}

// Thread management functions
void AudioManager::startAudioThread() {
    if (!threadRunning) {
        threadShouldExit = false;
        audioThread = std::thread(&AudioManager::audioThreadFunc, this);
        threadRunning = true;
    }
}

void AudioManager::stopAudioThread() {
    threadShouldExit = true;
    
    if (audioThread.joinable()) {
        audioThread.join();
    }
    
    threadRunning = false;
}

void AudioManager::audioThreadFunc() {
    while (!threadShouldExit) {
        {
            std::lock_guard<std::mutex> lock(audioMutex);
            
            if (initializedThemeMusic) {
                if (!IsWindowFocused()) {
                    SetMusicVolume(themeMusic, 0.0f);
                } else {
                    SetMusicVolume(themeMusic, musicVolume);
                }
                
                if (themeMusicShouldPlay) {
                    if (IsMusicStreamPlaying(themeMusic)) {
                        UpdateMusicStream(themeMusic);
                    } else {
                        PlayMusicStream(themeMusic);
                        themeMusic.looping = true;
                    }
                }
            }
        }
        
        // Sleep to prevent CPU hogging (10ms = 100 updates per second)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void AudioManager::stopThemeMusic() {
    std::lock_guard<std::mutex> lock(audioMutex);
    if (initializedThemeMusic && IsMusicStreamPlaying(themeMusic)) {
        StopMusicStream(themeMusic);
        themeMusicShouldPlay = false;
    }
}

void AudioManager::playThemMusic() {
    std::lock_guard<std::mutex> lock(audioMutex);
    if (initializedThemeMusic && !IsMusicStreamPlaying(themeMusic)) {
        PlayMusicStream(themeMusic);
        themeMusic.looping = true;
        themeMusicShouldPlay = true;
    }
}