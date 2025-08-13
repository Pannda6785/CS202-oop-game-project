#ifndef LICH_OF_FLOWERS_HEALTH_BAR_HPP
#define LICH_OF_FLOWERS_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class LichOfFlowersHealthBar : public HealthBar {
public:
    LichOfFlowersHealthBar(bool isLeftSide = true);
    ~LichOfFlowersHealthBar() override = default;
};

#endif // LICH_OF_FLOWERS_HEALTH_BAR_HPP