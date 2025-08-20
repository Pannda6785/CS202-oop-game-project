#ifndef HUD_HPP
#define HUD_HPP

#include <memory>
#include <string>

class IWorldView;
class HotBar;
class HealthBar;

class HUD {
public:
    HUD(const IWorldView* worldView);
    ~HUD();

    void update(float dt);
    
private:
    std::unique_ptr<HotBar> leftHotBar;
    std::unique_ptr<HotBar> rightHotBar;
    
    std::unique_ptr<HealthBar> leftHealthBar;
    std::unique_ptr<HealthBar> rightHealthBar;

    void init(const IWorldView* worldView);
};

#endif // HUD_HPP
