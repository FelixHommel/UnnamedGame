#include "gameLoop/EventBus.hpp"
#include "gameLoop/GameLoop.hpp"
#include "input/KeyboardInputAdapter.hpp"
#include "logging/SpdlogAdapter.hpp"

#include <memory>
#include <utility>

using namespace ugame;

int main()
{
    std::unique_ptr<infrastructure::SpdlogAdapter> logger{ std::make_unique<infrastructure::SpdlogAdapter>() };
    std::unique_ptr<core::EventBus> eventBus{ std::make_unique<core::EventBus>() };
    std::unique_ptr<infrastructure::KeyboardInputAdapter> input{ std::make_unique<infrastructure::KeyboardInputAdapter>(*eventBus) };

    core::GameLoop gameLoop(std::move(logger), *eventBus, std::move(input));

    gameLoop.run();

    return 0;
}
