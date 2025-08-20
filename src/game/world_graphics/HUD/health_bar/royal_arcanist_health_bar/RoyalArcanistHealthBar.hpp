#ifndef ROYAL_ARCANIST_HEALTH_BAR_HPP
#define ROYAL_ARCANIST_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class RoyalArcanistHealthBar : public HealthBar {
public:
    RoyalArcanistHealthBar(bool isLeftSide = true);
    ~RoyalArcanistHealthBar() override = default;
};

#endif // ROYAL_ARCANIST_HEALTH_BAR_HPP