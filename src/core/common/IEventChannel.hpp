#ifndef SRC_CORE_COMMON_I_EVENT_CHANNEL_HPP
#define SRC_CORE_COMMON_I_EVENT_CHANNEL_HPP

namespace ugame::core::common
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

} // !ugame::core::common

#endif // !SRC_CORE_COMMON_I_EVENT_CHANNEL_HPP
