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
        if (time >= tc.start && time <= tc.end && !tc.isActive) {
            tc.component->setVisible(true);
            tc.isActive = true;
        }
        if (time > tc.end && tc.isActive) {
            tc.component->setVisible(false);
            tc.isActive = false;
        }
        if (tc.isActive) {
            tc.component->update(dt);
        }
    }
}

void CompositeBulletGraphicsComponent::render() const {
    BulletGraphicsComponent::render(); 
    // the rest are *composed* so they render themselves through GraphicsComponentManager
}

void CompositeBulletGraphicsComponent::makeDone() {
    BulletGraphicsComponent::makeDone();
    for (auto& tc : components) {
        tc.component->makeDone();
    }
}