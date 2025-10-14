#ifndef SRC_CORE_GAME_LOOP_GAME_LOOP_HPP
#define SRC_CORE_GAME_LOOP_GAME_LOOP_HPP

#include "common/ILogger.hpp"
#include "common/IPlayerInput.hpp"
#include "gameLoop/EventBus.hpp"
#include "gameLoop/events/PlayerInputReceivedEvent.hpp"

#include <memory>

namespace ugame::core::gameloop
{
using namespace ugame::core::common;

/// \brief The GameLoop is where the core gameplay loop happens
///
/// \author Felix Hommel
/// \date 10/5/2025
class GameLoop
{
public:
    /// \brief Construct the main component of the game
    ///
    /// \param logger any implementation of a Logger
    explicit GameLoop(std::unique_ptr<ILogger> logger, EventBus& bus, std::unique_ptr<IPlayerInput> input);
    ~GameLoop() = default;

    GameLoop(const GameLoop&) = delete;
    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;

    /// \brief Start the game
    void run();

private:
    std::unique_ptr<ILogger> m_logger;
    std::unique_ptr<IPlayerInput> m_input;

    bool m_shouldQuit{ false };

    void handlePlayerInput(const events::PlayerInputReceivedEvent& event);
};

} // !ugame::core::gameloop

#endif // !SRC_CORE_GAME_LOOP_GAME_LOOP_HPP
