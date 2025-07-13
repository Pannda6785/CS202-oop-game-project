#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <string>
#include <map>
#include <vector>
#include "../../Unit.hpp"

class EventManager {
public:
    // Singleton pattern
    static EventManager& getInstance();

    using EventCallback = std::function<void(const Unit::GameEvent&)>;
    void subscribe(const Unit::GameEvent &eventType, EventCallback callback);
    void publish(const Unit::GameEvent& event);

private:
    EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    std::map<Unit::GameEvent, std::vector<EventCallback>> listeners;
};

#endif // EVENT_MANAGER_HPP