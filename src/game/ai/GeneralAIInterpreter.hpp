#ifndef GENERAL_AI_INTERPRETER_HPP
#define GENERAL_AI_INTERPRETER_HPP

#include "../../Unit.hpp"
#include "../../input/InputInterpreter.hpp"

#include <vector>
#include <optional>

class IWorldView;

class GeneralAIInterpreter : public InputInterpreter {
    static constexpr float BULLET_THREAT_DISTANCE = 100.0f; // Distance to consider a bullet "near"
    static constexpr float BULLET_NEAR_DISTANCE = 200.0f; // Distance to consider a bullet "near"
    static constexpr float REVERSE_DIR_TIME = 0.1f;

public:
    GeneralAIInterpreter(const IWorldView* worldView) : worldView(worldView) {}

    void update(float dt) override;
    Unit::Vec2D getMovement() const override;
    bool isInputPressed(Unit::Input input) const override;
    bool isInputReleased(Unit::Input input) const override;
    bool isInputDown(Unit::Input input) const override;
    bool isInputUp(Unit::Input input) const override;

private:
    const IWorldView* worldView;

    struct Action {
        Unit::Input input;
        float duration;
        bool rapidTap;
        float elapsedTime = 0.0f;
        Action(Unit::Input input, float duration, bool rapidTap) : input(input), duration(duration), rapidTap(rapidTap) {}
    };

    std::vector<std::pair<float, Action>> actionPool = { // (weight, action)
        {10.0f, Action(Unit::Input::Basic, 3, true)},
        {2.0f, Action(Unit::Input::Basic, 1.5f, false)},
        {10.0f, Action(Unit::Input::Wide, 3, true)},
        {2.0f, Action(Unit::Input::Wide, 1.5f, false)},
        {7.0f, Action(Unit::Input::Offensive, 2, true)},
        {3.0f, Action(Unit::Input::Offensive, 2, false)},
        {1.0f, Action(Unit::Input::Defensive, 1, true)}
    };
    std::optional<Action> currentAction = std::nullopt;
    Unit::Vec2D curDir = {0.0f, 0.0f};
    float reverseDirTimer;

    bool isBulletNear() const; // if some bullet->getPosition() is <= BULLET_NEAR_DISTANCE
    bool isBulletThreatening() const; // if some bullet with hitbox is <= BULLET_THREAT_DISTANCE, check by creating a hitbox and check collsion
    Unit::Vec2D getAwayFromBullets() const; // for isBulletNear(), try to choose a direction, weighted depending on 3 nearest bullets
    Unit::Vec2D weaveBetweenBullets() const; // for isBulletThreatening(), try to choose a direction, preferably within curDir, that doesn't run into bullets radius
    // in the end, the direction returned from above functions are used if curDir = 0, otherwise, if it somewhat align with curDir then take the average, if it is backward then do a timer for 0.1f continuing current direction until stop
};

#endif // GENERAL_AI_INTERPRETER_HPP