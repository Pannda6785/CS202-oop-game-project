#ifndef SILENT_REDHOOD_HEALTH_BAR_HPP
#define SILENT_REDHOOD_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class SilentRedhoodHealthBar : public HealthBar {
public:
    SilentRedhoodHealthBar(bool isLeftSide = true);
    ~SilentRedhoodHealthBar() override = default;
};

#endif // SILENT_REDHOOD_HEALTH_BAR_HPP