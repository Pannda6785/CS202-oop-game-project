#ifndef ORICHALCUM_MAIL_HPP
#define ORICHALCUM_MAIL_HPP

#include "Pattern.hpp"

/*
    B1: slow downward systematic rain
    B2: occasional expanding walls
*/

class OrichalcumMail : public Pattern {
    static constexpr int OWNER_ID = 2; // used for all bullets in of 3rd party pattern 
    static constexpr float DURATION = 30;
    
    static constexpr float B1_START_TIME = 2;
    static constexpr float B1_SPEED = 140;
    static constexpr float B1_RADIUS = 10;
    static constexpr float B1_HORIZONTAL_SPACING = 60;
    static constexpr float B1_VERTICAL_SPACING = 70;
    static constexpr float B1_FREQUENCY = B1_VERTICAL_SPACING / B1_SPEED;

    static constexpr float B2_START_TIME = 3;
    static constexpr float B2_SPEED = 160;
    static constexpr float B2_RADIUS = 15;
    static constexpr float B2_VERTICAL_SPACING = 60;
    static constexpr float B2_FREQUENCY = 5;

public:
    explicit OrichalcumMail(IBulletSpawner* spawner);

    void init() override;
    void update(float dt) override;

private:

    float timer;
};

#endif // ORICHALCUM_MAIL_HPP