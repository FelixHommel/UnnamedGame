#ifndef SRC_CORE_GAME_LOOP_EVENT_BUS_HPP
#define SRC_CORE_GAME_LOOP_EVENT_BUS_HPP

#include <algorithm>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ugame::core
{

class IEventChannel
{
public:
    virtual ~IEventChannel() = default;

    IEventChannel(const IEventChannel&) = default;
    IEventChannel(IEventChannel&&) = delete;
    IEventChannel& operator=(const IEventChannel&) = default;
    IEventChannel& operator=(IEventChannel&&) = delete;
};

/// \brief EventChannel interface for the \ref EventBus to access subscribers of a certain event uniformly
///
/// EventChannles are something the \ref EventBus is interacting with to access all handlers that have
/// subscribed to a certain type of event. Therefore every event has it's own Channel.
///
/// \author Felix Hommel
/// \date 10/11/2025
template<typename EventType>
class EventChannel : public IEventChannel
{
public:
    EventChannel() = default;

    void subscribe(std::function<void(const EventType&)> handler)
    {
        m_handlers.push_back(std::move(handler));
    }

    void publish(const EventType& event) const
    {
        for(auto& h : m_handlers)
            h(event);
    }

private:
    std::vector<std::function<void(const EventType&)>> m_handlers{};
};

/// \brief A simple implementation of an event bus for event driven communication
///
/// The EventBus is used by the core to process player input by reacting to events that are published by inputs.
///
/// \author Felix Hommel
/// \date 10/11/2025
class EventBus
{
public:
    EventBus() = default;

    template<typename EventType>
    void subscribe(std::function<void(const EventType&)> handler) const
    {
        getChannel<EventType>().subscribe(std::move(handler));
    }

    template<typename EventType>
    void publish(const EventType& event) const
    {
        auto it{ m_channels.find(typeid(EventType)) };

        // TODO: refactor out pointerness
        if(it != m_channels.end())
            static_cast<EventChannel<EventType>*>(it->second.get())->publish(event);
    }

private:
    mutable std::unordered_map<std::type_index, IEventChannel> m_channels;

    template<typename EventType>
    EventChannel<EventType>& getChannel() const
    {
        auto it{ m_channels.find(typeid(EventType)) };

        // TODO: create the getChannel function
    }
};

} //!ugame::core

#endif //!SRC_CORE_GAME_LOOP_EVENT_BUS_HPP
