#ifndef SRC_CORE_GAME_LOOP_EVENT_BUS_HPP
#define SRC_CORE_GAME_LOOP_EVENT_BUS_HPP

#include "common/IEvent.hpp"
#include "common/IEventChannel.hpp"

#include <algorithm>
#include <concepts>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ugame::core::gameloop
{
using namespace ugame::core::common;

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

    /// \brief Register a new callback function
    ///
    /// \param handler callback function
    void subscribe(std::function<void(const EventType&)> handler)
    {
        m_handlers.push_back(std::move(handler));
    }

    /// \brief Execute all callback functions with the new event
    ///
    /// \param event newly published event
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
class EventBus //: public IEventPublisher
{
public:
    EventBus() = default;
    ~EventBus() = default;

    EventBus(const EventBus&) = default;
    EventBus(EventBus&&) = delete;
    EventBus& operator=(const EventBus&) = default;
    EventBus& operator=(EventBus&&) = delete;

    /// \brief subscribe to events of type \p EventType
    ///
    /// Subscribers of event will get their callback function executed each time a new event of the \p EventType type 
    /// are published
    ///
    /// \param EventType any type that inherits from IEvent 
    /// \param handler callback function that is executed when a new event is published
    template<typename EventType>
        requires std::derived_from<EventType, IEvent>
    void subscribe(std::function<void(const EventType&)> handler) const
    {
        getChannel<EventType>().subscribe(std::move(handler));
    }

    /// \brief Publish the occurence of a new event
    ///
    /// Give notice to all subscribers of \p EventType that a new event has happened
    ///
    /// \param EventType any type that inherits from IEvent 
    /// \param event the event that happened
    template<typename EventType>
        requires std::derived_from<EventType, IEvent>
    void publish(const EventType& event) const
    {
        getChannel<EventType>().publish(event);
    }

private:
    mutable std::unordered_map<std::type_index, std::unique_ptr<IEventChannel>> m_channels;

    /// \brief Safely access references to EventChannels
    ///
    /// The function first checks if there already is a channel for \p EventType. If there is it returns
    /// a reference to the channel, if not it first creates the channel for \p EventType and then returns a reference
    /// to the channel.
    ///
    /// \param EventType any type that inherits from IEvent 
    ///
    /// \return reference to \ref EventChannel with the type of \p EventType
    template<typename EventType>
        requires std::derived_from<EventType, IEvent>
    EventChannel<EventType>& getChannel() const
    {
        auto& ptr{ m_channels[typeid(EventType)] };

        if(!ptr)
            ptr = std::make_unique<EventChannel<EventType>>();

        auto* typedPtr{ static_cast<EventChannel<EventType>*>(ptr.get()) };

        return *typedPtr;
    }
};

} //!ugame::core::gameloop

#endif //!SRC_CORE_GAME_LOOP_EVENT_BUS_HPP
