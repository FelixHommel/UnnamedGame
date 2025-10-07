#include "gameLoop/GameLoop.hpp"
#include "logging/SpdlogAdapter.hpp"

#include <memory>
#include <utility>

using namespace ugame;

int main()
{
    std::unique_ptr<infrastructure::SpdlogAdapter> logger{ std::make_unique<infrastructure::SpdlogAdapter>() };

    core::GameLoop gameLoop(std::move(logger));

    gameLoop.run();

    return 0;
}
