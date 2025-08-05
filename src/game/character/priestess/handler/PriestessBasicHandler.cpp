#include "PriestessBasicHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"

#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/DecorateGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"

PriestessBasicHandler::PriestessBasicHandler(PriestessGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void PriestessBasicHandler::update(float deltaTime, const InputBufferer* input) {
    comboHold = std::max(0.0f, comboHold - deltaTime);
    if (comboHold < Unit::EPS) {
        step = 0;
    }
}

void PriestessBasicHandler::listen(Unit::Move move) {
    if (move != Unit::Move::Basic) {
        comboHold = 0;
        step = 0;
    }
}

void PriestessBasicHandler::tap(bool isFocusing) {
    graphics->useBasic();

    spawnBullet(isFocusing);

    step++;
    player->applyImplicitMoveLock();
    player->applyLock(Unit::moveToLock(move), step < 3 ? SHORT_LOCK : LONG_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyModifier(Unit::Modifier::ArrowModifier, step < 3 ? SHORT_ARROW_MODIFIER_DURATION : LONG_ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);
    if (step < 3) {
        comboHold = COMBO_HOLD;
    } else {
        step = 0;
        comboHold = 0;
    }
}

void PriestessBasicHandler::spawnBullet(bool isFocusing) {
    // calculate trajectory and startup
    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D arrow = player->getArrow();
    Unit::Vec2D target = player->getTargetPosition();

    float toTravel = arrow.dot(target - pos);
    float startupTime = BASE_STARTUP;
    if (isFocusing) {
        toTravel = std::max(0.0f, toTravel - FOCUS_DISTANCE_SHORTENING);
        startupTime = FOCUS_STARTUP;
    }
    startupTime += DISTANCE_SCALAR * toTravel;
    float last_t = 0;

    std::cerr << startupTime << std::endl;

    // texture
    std::string path = "../assets/sprites/priestess/bullet/";
    std::vector<const Texture*> startupAnim = {
        TextureManager::instance().getTexture(path + "spr_prs_6_p1_0.png"),
        TextureManager::instance().getTexture(path + "spr_prs_6_p1_1.png")
    };
    constexpr float visibleRatioStartup = 0.75f;
    float resizeStartup = (RADIUS * 2.0f) / (startupAnim[0]->width * visibleRatioStartup);
    std::vector<const Texture*> activeAnim = {
        TextureManager::instance().getTexture(path + "spr_prs_1_p1_0.png"),
        TextureManager::instance().getTexture(path + "spr_prs_1_p1_1.png"),
        TextureManager::instance().getTexture(path + "spr_prs_1_p1_2.png")
    };
    constexpr float visibleRatioActive = 0.77f;
    float resizeActive = (RADIUS * 2.0f) / (activeAnim[0]->width * visibleRatioActive);

    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        pos,
        arrow,
        [toTravel, last_t](float t) mutable {
            float dt = t - last_t;
            last_t = t;
            if (toTravel > Unit::EPS) { 
                float d = toTravel / SPEED;
                d = std::min(d, dt);
                toTravel -= SPEED * d;
                return d / dt * SPEED;
            }
            return 0.0f;
        },
        startupTime + ACTIVE_TIME + 0.15f
    );

    auto* composite = dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics());

    // Startup animation (Layer::Bullet)
    auto startupGraphics = std::make_unique<TextureBulletGraphicsComponent>(startupAnim, 6, resizeStartup);
    startupGraphics->setLayer(Unit::Layer::Bullet);
    startupGraphics->addFadein(0.0f, 0.35f);
    std::array<int, 4> startupTint = graphics->getSignatureColor();
    if (isFocusing) { // make tint darker: the values that are small will be smaller
        for (int i = 0; i < 3; i++) {
            startupTint[i] = 255 * (startupTint[i] / 255.0f) * (startupTint[i] / 255.0f);
        }
    }
    startupGraphics->addTint(startupTint);
    composite->addComponent(std::move(startupGraphics), 0.0f, startupTime - 0.08f);
    
    // Overlay for startup
    auto startupDecorate = std::make_unique<DecorateGraphicsComponent>();
    startupDecorate->setLayer(Unit::Layer::Bullet - 5);
    startupTint[3] = 50; startupDecorate->addCircle(startupTint, RADIUS);
    startupTint[3] = 70; startupDecorate->addRing(startupTint, RADIUS + 2, 6);
    composite->addComponent(std::move(startupDecorate), 0.0f, startupTime - 0.12f);

    // Active damaging bullet animation (Layer::Underlay)
    auto activeGraphics = std::make_unique<TextureBulletGraphicsComponent>(activeAnim, 6, resizeActive);
    activeGraphics->setLayer(Unit::Layer::Underlay);
    activeGraphics->addBloom(0, 0.15f);
    activeGraphics->addDebloom(0.15f + ACTIVE_TIME, 0.15f + ACTIVE_TIME + 0.15f);
    composite->addComponent(std::move(activeGraphics), startupTime - 0.15f, startupTime + ACTIVE_TIME + 0.15f);

    // Overlay for active
    auto activeDecorate = std::make_unique<DecorateGraphicsComponent>();
    std::array<int, 4> ringTint = graphics->getSignatureColor(); ringTint[3] = 120;
    activeDecorate->addRing(ringTint, RADIUS + 4, 5);
    composite->addComponent(std::move(activeDecorate), startupTime - 0.1f, startupTime + ACTIVE_TIME);

    // Hitboxes
    bullet->addDamagingHitbox(startupTime, std::make_unique<CircleHitbox>(pos + arrow * toTravel, RADIUS));
    bullet->removeDamagingHitbox(startupTime + ACTIVE_TIME);

    player->spawnBullet(std::move(bullet));
}
