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

/// \brief Interface for Event channels
///
/// This is primarly usefull so that EventChannels can be stored generically in a container without mentioning
/// their type parameter.
///
/// \author Felix Hommel
/// \date 10/11/2025
class IEventChannel
{
public:
    IEventChannel() = default;
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
class EventBus
{
public:
    EventBus() = default;

    /// \brief subscribe to events of type \p EventType
    ///
    /// Subscribers of event will get their callback function executed each time a new event of the \p EventType type 
    /// are published
    ///
    /// \param EventType can be any type
    /// \param handler callback function that is executed when a new event is published
    template<typename EventType>
    void subscribe(std::function<void(const EventType&)> handler) const
    {
        getChannel<EventType>().subscribe(std::move(handler));
    }

    /// \brief Publish the occurence of a new event
    ///
    /// Give notice to all subscribers of \p EventType that a new event has happened
    ///
    /// \param EventType can be any type
    /// \param event the event that happened
    template<typename EventType>
    void publish(const EventType& event) const
    {
        auto it{ m_channels.find(typeid(EventType)) };

        if(it != m_channels.end())
            static_cast<EventChannel<EventType>*>(it->second.get())->publish(event);
    }

private:
    mutable std::unordered_map<std::type_index, std::unique_ptr<IEventChannel>> m_channels;

    /// \brief Safely access references to EventChannels
    ///
    /// The function first checks if there already is a channel for \p EventType. If there is it returns
    /// a reference to the channel, if not it first creates the channel for \p EventType and then returns a reference
    /// to the channel.
    ///
    /// \param EventType can be any type 
    ///
    /// \return reference to \ref EventChannel with the type of \p EventType
    template<typename EventType>
    EventChannel<EventType>& getChannel() const
    {
        auto& ptr{ m_channels[typeid(EventType)] };

        if(!ptr)
            ptr = std::make_unique<EventChannel<EventType>>();

        auto* typedPtr{ static_cast<EventChannel<EventType>*>(ptr.get()) };

        return *typedPtr;
    }
};

} //!ugame::core

#endif //!SRC_CORE_GAME_LOOP_EVENT_BUS_HPP
