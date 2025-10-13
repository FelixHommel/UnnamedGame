#include "GameLoop.hpp"

#include "common/ILogger.hpp"
#include "common/IPlayerInput.hpp"
#include "gameLoop/EventBus.hpp"
#include "gameLoop/events/PlayerInputReceivedEvent.hpp"

#include <memory>
#include <utility>

namespace ugame::core
{

GameLoop::GameLoop(std::unique_ptr<ILogger> logger, EventBus& bus, std::unique_ptr<IPlayerInput> input)
    : m_logger(std::move(logger))
    , m_input(std::move(input))
{
    bus.subscribe<events::PlayerInputReceivedEvent>([this](const events::PlayerInputReceivedEvent& event){ handlePlayerInput(event); });
}

void GameLoop::run()
{
    m_logger->info("game started");

    while(!m_shouldQuit)
    {
        m_input->poll();
    }

    m_logger->info("game ended");
}

/// \brief Callback function that is handling the \ref PlayerInputReceivedEvent
///
/// \param event input event that is being processed
void GameLoop::handlePlayerInput(const events::PlayerInputReceivedEvent& event)
{
    // TODO: needs actual input handling, for now echoing the input is enough
    m_logger->info("received input: {}", event.input);

    if(event.input == "q")
        m_shouldQuit = true;
}

} // !ugame::core
