#include "CompositeBulletGraphicsComponent.hpp"
#include "BulletGraphicsComponent.hpp"

void CompositeBulletGraphicsComponent::addComponent(std::unique_ptr<BulletGraphicsComponent> component, float start, float end) {
    component->registerBullet(bullet);
    component->setVisible(false);
    components.push_back(TimedComponent{std::move(component), start, end});
}

void CompositeBulletGraphicsComponent::update(float dt) {
    time += dt;
    for (auto& tc : components) {
        if (time - 2 * dt < tc.start && time >= tc.start) {
            tc.component->setVisible(true);
        }
        if (time - 2 * dt < tc.end && time >= tc.end) {
            tc.component->setVisible(false);
        }
        if (tc.component->isVisible()) {
            tc.component->update(dt);
        }
    }
}

void CompositeBulletGraphicsComponent::render() const {
    BulletGraphicsComponent::render(); 
    // the rest are *composed* so they render themselves through GraphicsComponentManager
}