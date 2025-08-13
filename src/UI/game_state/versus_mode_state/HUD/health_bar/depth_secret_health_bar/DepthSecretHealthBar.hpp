#ifndef DEPTH_SECRET_HEALTH_BAR_HPP
#define DEPTH_SECRET_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class DepthSecretHealthBar : public HealthBar {
public:
    DepthSecretHealthBar(bool isLeftSide = true);
    ~DepthSecretHealthBar() override = default;
};

#endif // DEPTH_SECRET_HEALTH_BAR_HPP