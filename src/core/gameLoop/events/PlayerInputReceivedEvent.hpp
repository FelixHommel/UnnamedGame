#ifndef SRC_CORE_GAME_LOOP_EVENTS_PLAYER_INPUT_RECEIVED_EVENT_HPP
#define SRC_CORE_GAME_LOOP_EVENTS_PLAYER_INPUT_RECEIVED_EVENT_HPP

#include "common/IEvent.hpp"

#include <string>

namespace ugame::core::gameloop::events
{
using namespace ugame::core::common;

///\brief This event is produced and published by children of \ref IPlayerInput
///
/// \author Felix Hommel
/// \date 10/12/2025
struct PlayerInputReceivedEvent : public IEvent
{
    std::string input;
};

} //!ugame::core::gameloop::events

#endif //!SRC_CORE_GAME_LOOP_EVENTS_PLAYER_INPUT_RECEIVED_EVENT_HPP
