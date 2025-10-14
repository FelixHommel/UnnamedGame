#include "gameLoop/EventBus.hpp"
#include "gameLoop/GameLoop.hpp"
#include "input/KeyboardInputAdapter.hpp"
#include "logging/SpdlogAdapter.hpp"

#include <memory>
#include <utility>

using namespace ugame::core;
using namespace ugame::infrastructure;

int main()
{
    std::unique_ptr<logging::SpdlogAdapter> logger{ std::make_unique<logging::SpdlogAdapter>() };
    std::unique_ptr<gameloop::EventBus> eventBus{ std::make_unique<gameloop::EventBus>() };
    std::unique_ptr<input::KeyboardInputAdapter> input{ std::make_unique<input::KeyboardInputAdapter>(*eventBus) };

    gameloop::GameLoop gameLoop(std::move(logger), *eventBus, std::move(input));

    gameLoop.run();

    return 0;
}
