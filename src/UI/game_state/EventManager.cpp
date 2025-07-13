#include "EventManager.hpp"

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

void EventManager::subscribe(const Unit::GameEvent& eventType, EventCallback callback) {
    listeners[eventType].push_back(callback);
}

void EventManager::publish(const Unit::GameEvent& event) {
    auto it = listeners.find(event);
    if (it != listeners.end()) {
        for (const auto& callback : it->second) {
            callback(event);
        }
    }
}