#ifndef HOT_BAR_FACTORY_HPP
#define HOT_BAR_FACTORY_HPP

#include "HotBar.hpp"
#include <string>
#include <memory>

class HotBarFactory {
public:
    static std::unique_ptr<HotBar> createForCharacter(const std::string& characterName, bool isLeftSide = true);
};

#endif // HOT_BAR_FACTORY_HPP