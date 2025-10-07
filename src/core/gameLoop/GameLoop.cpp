#include "GameLoop.hpp"

#include "common/ILogger.hpp"

#include <memory>
#include <utility>

namespace ugame::core
{

GameLoop::GameLoop(std::unique_ptr<ILogger> logger)
    : m_logger(std::move(logger))
{
}

void GameLoop::run()
{
    m_logger->info("game started");
    m_logger->info("game ended");
}

} // !ugame::core
