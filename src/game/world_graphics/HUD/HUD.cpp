#include "HUD.hpp"

#include "hot_bar/HotBar.hpp"
#include "hot_bar/HotBarFactory.hpp"
#include "health_bar/HealthBar.hpp"
#include "health_bar/HealthBarFactory.hpp"
#include "../../IWorldView.hpp"
#include "../../player/Player.hpp"

HUD::HUD(const IWorldView* worldView)
    : leftHotBar(nullptr), rightHotBar(nullptr),
      leftHealthBar(nullptr), rightHealthBar(nullptr)
{
    init(worldView);
}

HUD::~HUD() = default;

void HUD::init(const IWorldView* worldView) {
    std::string leftCharName = worldView->getPlayers()[0]->getName();
    std::string rightCharName = worldView->getPlayers()[1]->getName();

    // HotBars
    leftHotBar = HotBarFactory::createForCharacter(leftCharName, true);
    leftHotBar->setWorldView(worldView);

    rightHotBar = HotBarFactory::createForCharacter(rightCharName, false);
    rightHotBar->setWorldView(worldView);

    // HealthBars
    leftHealthBar = HealthBarFactory::createForCharacter(leftCharName, true);
    leftHealthBar->setWorldView(worldView);

    rightHealthBar = HealthBarFactory::createForCharacter(rightCharName, false);
    rightHealthBar->setWorldView(worldView);
}

void HUD::update(float dt) {
    if (leftHotBar)   leftHotBar->update(dt);
    if (rightHotBar)  rightHotBar->update(dt);

    if (leftHealthBar)  leftHealthBar->update(dt);
    if (rightHealthBar) rightHealthBar->update(dt);
}
