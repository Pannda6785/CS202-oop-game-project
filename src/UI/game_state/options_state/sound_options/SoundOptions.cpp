#include "SoundOptions.hpp"
#include "../../GameStateManager.hpp"
#include "./volume_bar/VolumeBarManager.hpp"
#include "../../../../audio/AudioManager.hpp"

SoundOptions::SoundOptions(GameStateManager &gameStateManager, BehindDots &behindDots) :
gameStateManager(gameStateManager), behindDots(behindDots) {
    enter();
}

SoundOptions::~SoundOptions(){
    exit();
}

void SoundOptions::enter() {
    
    // Add buttons for sound options
    int buttonWidth = GraphicsComponentManager::NATIVE_WIDTH;
    int buttonHeight = 80;
    int coordYFirstButton = 200;
    int buttonSpacing = 15;
    int offset = 200;
    int deltaOffset = 0;
    int fontSize = 50;
    int dividerLineHeight = 2;
    int dividerLineLength = 600;
    int dividerLineThickness = 5;
    int headingPosY = 130;
    int dividerLineY = headingPosY + 60;
    int volumeBarPosX = 700;
    int volumeBarWidth = 500;
    int volumeBarHeight = 10;
    font = LoadFontEx("../assets/fonts/18thCentury.ttf", 256, 0, 0);

    heading.setHasHeading(true);
    heading.init("../assets/fonts/18thCentury.ttf", 
                 "OPTIONS", 
                 headingPosY, 
                 fontSize, 
                 {(GraphicsComponentManager::NATIVE_WIDTH - dividerLineLength) / 2.0f, dividerLineY * 1.0f, dividerLineLength * 1.0f, dividerLineThickness * 1.0f});
    
    // Master Volume button
    std::unique_ptr<Button> masterVolumeButton = std::make_unique<Button>(
        0,
        coordYFirstButton += buttonHeight + buttonSpacing,
        buttonWidth,
        buttonHeight,
        "MASTER VOLUME",
        fontSize,
        offset -= deltaOffset,
        -1,
        "../assets/fonts/18thCentury.ttf",
        false
    );
    buttonManager.addButton(std::move(masterVolumeButton));

    // Master volume bar
    std::unique_ptr<VolumeBar> masterVolumeBar = std::make_unique<VolumeBar>(
        Rectangle{ volumeBarPosX * 1.0f, coordYFirstButton + (buttonHeight - volumeBarHeight) / 2.0f, volumeBarWidth * 1.0f, volumeBarHeight * 1.0f }, 
        1.0f,
        buttonManager.getButton(0)
    );
    masterVolumeBar->setFont(&font);
    masterVolumeBar->setVolume(AudioManager::getInstance().getMasterVolume());
    volumeBarManager.addVolumeBar(std::move(masterVolumeBar));

    // Music Volume button
    std::unique_ptr<Button> musicVolumeButton = std::make_unique<Button>(
        0,
        coordYFirstButton += buttonHeight + buttonSpacing,
        buttonWidth,
        buttonHeight,
        "MUSIC VOLUME",
        fontSize,
        offset -= deltaOffset,
        -1,
        "../assets/fonts/18thCentury.ttf",
        false
    );
    buttonManager.addButton(std::move(musicVolumeButton));

    // Music volume bar
    std::unique_ptr<VolumeBar> musicVolumeBar = std::make_unique<VolumeBar>(
        Rectangle{ volumeBarPosX * 1.0f, coordYFirstButton + (buttonHeight - volumeBarHeight) / 2.0f, volumeBarWidth * 1.0f, volumeBarHeight * 1.0f }, 
        1.0f,
        buttonManager.getButton(1)
    );
    musicVolumeBar->setFont(&font);
    musicVolumeBar->setVolume(AudioManager::getInstance().getMusicVolume());
    volumeBarManager.addVolumeBar(std::move(musicVolumeBar));

    // Sfx Volume button
    std::unique_ptr<Button> sfxVolumeButton = std::make_unique<Button>(
        0,
        coordYFirstButton += buttonHeight + buttonSpacing,
        buttonWidth,
        buttonHeight,
        "SFX VOLUME",
        fontSize,
        offset -= deltaOffset,
        -1,
        "../assets/fonts/18thCentury.ttf",
        false
    );
    buttonManager.addButton(std::move(sfxVolumeButton));

    // Sfx volume bar
    std::unique_ptr<VolumeBar> sfxVolumeBar = std::make_unique<VolumeBar>(
        Rectangle{ volumeBarPosX * 1.0f, coordYFirstButton + (buttonHeight - volumeBarHeight) / 2.0f, volumeBarWidth * 1.0f, volumeBarHeight * 1.0f }, 
        1.0f,
        buttonManager.getButton(2)
    );
    sfxVolumeBar->setFont(&font);
    sfxVolumeBar->setVolume(AudioManager::getInstance().getSfxVolume());
    volumeBarManager.addVolumeBar(std::move(sfxVolumeBar));

    // Graphics options button
    std::unique_ptr<Button> backButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing,
        buttonWidth, 
        buttonHeight, 
        "BACK", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    backButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        gameStateManager.popState();
        std::cout << "Back" << std::endl;
    });
    backButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Graphics Options button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(backButton));
}

void SoundOptions::update(float dt) {
    // Update logic for sound options
    buttonManager.update(dt);
    volumeBarManager.setHoveredIndex(buttonManager.getHoveredIndex());
    volumeBarManager.update(dt);
    float masterVolume = volumeBarManager.getBar(0)->getVolume();
    AudioManager::getInstance().setMasterVolume(masterVolume);
    float musicVolume = volumeBarManager.getBar(1)->getVolume();
    AudioManager::getInstance().setMusicVolume(musicVolume);
    float sfxVolume = volumeBarManager.getBar(2)->getVolume();
    AudioManager::getInstance().setSfxVolume(sfxVolume);
    behindDots.update(dt);
}

void SoundOptions::exit() {
    // Cleanup logic if needed
    buttonManager.reset();
    heading.unload();
    UnloadFont(font);
}
