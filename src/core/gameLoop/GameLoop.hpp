#ifndef SRC_CORE_GAME_LOOP_GAME_LOOP_HPP
#define SRC_CORE_GAME_LOOP_GAME_LOOP_HPP

#include "common/ILogger.hpp"

#include <memory>

namespace ugame::core
{

/// \brief The GameLoop is where the core gameplay loop happens
///
/// \author Felix Hommel
/// \date 10/5/2025
class GameLoop
{
public:
    /// \brief Construct the main component of the game, providing it with a valid logger implementation
    explicit GameLoop(std::unique_ptr<ILogger> logger);
    ~GameLoop() = default;

    GameLoop(const GameLoop&) = delete;
    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;

    /// \brief Start the game
    void run();

private:
    std::unique_ptr<ILogger> m_logger;
};

} // !ugame::core

#endif // !SRC_CORE_GAME_LOOP_GAME_LOOP_HPP
