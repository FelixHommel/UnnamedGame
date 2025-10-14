#ifndef SRC_CORE_GAME_LOOP_EVENTS_PLAYER_INPUT_RECEIVED_EVENT_HPP
#define SRC_CORE_GAME_LOOP_EVENTS_PLAYER_INPUT_RECEIVED_EVENT_HPP

#include "common/IEvent.hpp"

#include <string>

namespace ugame::core::events
{

struct PlayerInputReceivedEvent : public IEvent
{
    std::string input;
};

} //!ugame::core::events

#endif //!SRC_CORE_GAME_LOOP_EVENTS_PLAYER_INPUT_RECEIVED_EVENT_HPP
