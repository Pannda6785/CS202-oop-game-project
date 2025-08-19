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

        for (int i = 0; i <= 6; i++) {
            std::string path = "../assets/audio/attack/sound_generic_attack_" + std::to_string(i) + ".wav";
            std::string name = "Attack" + std::to_string(i);
            Sound attack = LoadSound(path.c_str());
            sounds[name] = attack;
        }

        Sound heroCharge = LoadSound("../assets/audio/attack/sound_fencer_stun_1.wav");
        Sound heroStun = LoadSound("../assets/audio/attack/sound_fencer_stun_2.wav");
        Sound heroRoll = LoadSound("../assets/audio/attack/sound_fencer_dodge_1.wav");
        sounds["HeroCharge"] = heroCharge;
        sounds["HeroStun"] = heroStun;
        sounds["HeroRoll"] = heroRoll;

        Sound wyrmShoot = LoadSound("../assets/audio/attack/sound_flower_bf_2.wav");
        Sound wyrmCharge = LoadSound("../assets/audio/attack/sound_dragon_maj_1.wav");
        Sound wyrmBlast = LoadSound("../assets/audio/attack/sound_dragon_laser_2.wav");
        Sound wyrmChargeTransform = LoadSound("../assets/audio/attack/sound_dragon_laser_1.wav");
        Sound wyrmTransform = LoadSound("../assets/audio/attack/sound_magnus_start.wav");
        Sound wyrmDetransform = LoadSound("../assets/audio/attack/sound_paralyze.wav");
        sounds["WyrmShoot"] = wyrmShoot;
        sounds["WyrmCharge"] = wyrmCharge;
        sounds["WyrmBlast"] = wyrmBlast;
        sounds["WyrmChargeTransform"] = wyrmChargeTransform;
        sounds["WyrmTransform"] = wyrmTransform;
        sounds["WyrmDetransform"] = wyrmDetransform;

        Sound priestessBasic1 = LoadSound("../assets/audio/attack/sound_flower_rose_1.wav");
        Sound priestessBasic2 = LoadSound("../assets/audio/attack/sound_fencer_stun_2.wav");
        Sound priestessDefensive = LoadSound("../assets/audio/attack/sound_flower_rose_2.wav");
        sounds["PriestessBasic1"] = priestessBasic1;
        sounds["PriestessBasic2"] = priestessBasic2;
        sounds["PriestessDefensive"] = priestessDefensive;

        Sound lichOffensive = LoadSound("../assets/audio/attack/sound_flower_bf_1.wav");
        Sound lichDefensive1 = LoadSound("../assets/audio/attack/sound_flower_rose_1.wav");
        Sound lichDefensive2 = LoadSound("../assets/audio/attack/sound_flower_rose_2.wav");
        sounds["LichOffensive"] = lichOffensive;
        sounds["LichDefensive1"] = lichDefensive1;
        sounds["LichDefensive2"] = lichDefensive2;

        Sound depthBasic1 = LoadSound("../assets/audio/attack/sound_flower_rose_1.wav");
        Sound depthBasic2 = LoadSound("../assets/audio/attack/sound_flower_rose_2.wav");
        Sound depthDefensive1 = LoadSound("../assets/audio/attack/sound_flower_rose_1.wav");
        Sound depthDefensive2 = LoadSound("../assets/audio/attack/sound_hydra_head.wav");
        sounds["DepthBasic1"] = depthBasic1;
        sounds["DepthBasic2"] = depthBasic2;
        sounds["DepthDefensive1"] = depthDefensive1;
        sounds["DepthDefensive2"] = depthDefensive2;

        Sound arcanistOffensive1 = LoadSound("../assets/audio/attack/sound_generic_attack_3.wav");
        Sound arcanistOffensive2 = LoadSound("../assets/audio/attack/sound_flower_rose_2.wav");
        Sound arcanistClockWind = LoadSound("../assets/audio/attack/sound_clock_wind.wav");
        Sound arcanistClockStop = LoadSound("../assets/audio/attack/sound_clock_stop.wav");
        Sound arcanistClockTick = LoadSound("../assets/audio/attack/sound_clock_tick.wav");
        sounds["ArcanistOffensive1"] = arcanistOffensive1;
        sounds["ArcanistOffensive2"] = arcanistOffensive2;
        sounds["ArcanistClockWind"] = arcanistClockWind;
        sounds["ArcanistClockStop"] = arcanistClockStop;
        sounds["ArcanistClockTick"] = arcanistClockTick;

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
        std::cerr << "Warning: Sound not found: " << soundName << std::endl;
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