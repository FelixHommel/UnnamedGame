#include "KeyboardInputAdapter.hpp"

#include "common/IPlayerInput.hpp"
#include "gameLoop/EventBus.hpp"
#include "gameLoop/events/PlayerInputReceivedEvent.hpp"

#include <iostream>
#include <string>

namespace ugame::infrastructure::input
{

KeyboardInputAdapter::KeyboardInputAdapter(EventBus& publisher)
    : IPlayerInput(publisher)
{}

void KeyboardInputAdapter::poll()
{
    std::string input{};
    if(std::getline(std::cin, input))
        m_publisher.publish(events::PlayerInputReceivedEvent{ .input = input });
}

} // !ugame::infrastructure::input
