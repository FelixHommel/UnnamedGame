#ifndef SRC_CORE_COMMON_I_EVENT_HPP
#define SRC_CORE_COMMON_I_EVENT_HPP

namespace ugame::core::common
{

/// \brief Sole purpose of this class is it to provide a common interface for events to derive from
///
/// This enables the enforcment and better and tighter managemnt of everythin that has to react to events
/// that are being published in the \ref EventBus. It alows for the utilization of concepts to further reinforce
/// and ensure type correctness.
///
/// \author Felix Hommel
/// \date 10/12/2025
struct IEvent {};

} // !ugame::core::common

#endif // !SRC_CORE_COMMON_I_EVENT_HPP
