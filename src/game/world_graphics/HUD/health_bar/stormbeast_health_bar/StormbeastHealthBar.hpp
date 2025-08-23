#ifndef STORMBEAST_HEALTH_BAR_HPP
#define STORMBEAST_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class StormbeastHealthBar : public HealthBar {
public:
    StormbeastHealthBar(bool isLeftSide = true);
    ~StormbeastHealthBar() override = default;
};

#endif // STORMBEAST_HEALTH_BAR_HPP