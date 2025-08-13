#ifndef DREADWYRM_HEIR_HEALTH_BAR_HPP
#define DREADWYRM_HEIR_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class DreadwyrmHeirHealthBar : public HealthBar {
public:
    DreadwyrmHeirHealthBar(bool isLeftSide = true);
    ~DreadwyrmHeirHealthBar() override = default;
};

#endif // DREADWYRM_HEIR_HEALTH_BAR_HPP