#ifndef SRC_CORE_GAME_LOOP_EVENT_BUS_HPP
#define SRC_CORE_GAME_LOOP_EVENT_BUS_HPP

#include <algorithm>
#include <any>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ugame::core
{

/// \brief A simple implementation of an event bus for event driven communication
///
/// The EventBus is used by the core to process player input by reacting to events that are published by inputs.
///
/// \author Felix Hommel
/// \date 10/11/2025
class EventBus
{
public:
    EventBus();
    ~EventBus() = default;

    EventBus(const EventBus&) = delete;
    EventBus(EventBus&&) = delete;
    EventBus& operator=(const EventBus&) = delete;
    EventBus& operator=(EventBus&&) = delete;

    template<typename E>
    using Handler = std::function<void(const E&)>;

    template<typename E>
    void subscribe(Handler<E> handler)
    {
        auto& handlers{ m_subscribers[typeid(E)] };
        handlers.push_back(
            [h = std::move(handler)](const auto& event) {
                h(static_cast<const E&>(event));
            }
        );
    }

    template<typename E>
    void publish(const E& event)
    {
        auto it{ m_subscribers.find(typeid(E)) };

        if(it == m_subscribers.end())
            return;

        for(auto& f : it->second)
            f(event);
    }

private:
    using GenericHandler = std::function<void(const std::any&)>;
    std::unordered_map<std::type_index, std::vector<GenericHandler>> m_subscribers;
};

} //!ugame::core

#endif //!SRC_CORE_GAME_LOOP_EVENT_BUS_HPP
