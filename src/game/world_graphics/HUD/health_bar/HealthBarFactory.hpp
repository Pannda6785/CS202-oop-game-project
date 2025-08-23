#ifndef HEALTH_BAR_FACTORY_HPP
#define HEALTH_BAR_FACTORY_HPP

#include "HealthBar.hpp"
#include <string>
#include <memory>
#include <algorithm>

class HealthBarFactory {
public:
    /**
     * Creates a health bar for the specified character
     * 
     * @param characterName The name of the character (case-insensitive)
     * @param isLeftSide Whether the health bar should be positioned on the left side
     * @return A unique_ptr to the appropriate HealthBar subclass
     */
    static std::unique_ptr<HealthBar> createForCharacter(const std::string& characterName, bool isLeftSide = true);
};

#endif // HEALTH_BAR_FACTORY_HPP