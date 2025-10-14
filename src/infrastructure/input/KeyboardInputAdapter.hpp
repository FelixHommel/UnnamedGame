#ifndef SRC_INFRASTRUCTURE_PLAYER_INPUT_KEYBOARD_INPUT_ADAPTER_HPP
#define SRC_INFRASTRUCTURE_PLAYER_INPUT_KEYBOARD_INPUT_ADAPTER_HPP

#include "common/IPlayerInput.hpp"
#include "gameLoop/EventBus.hpp"

namespace ugame::infrastructure
{
using namespace ugame::core;

/// \brief Provides keyboard input via console standard input
///
/// \author Felix Hommel
/// \date 10/13/2025
class KeyboardInputAdapter : public IPlayerInput
{
public:
    explicit KeyboardInputAdapter(EventBus& publisher);
    ~KeyboardInputAdapter() override = default;

    KeyboardInputAdapter(const KeyboardInputAdapter&) = default;
    KeyboardInputAdapter(KeyboardInputAdapter&&) = delete;
    KeyboardInputAdapter& operator=(const KeyboardInputAdapter&) = delete;
    KeyboardInputAdapter& operator=(KeyboardInputAdapter&&) = delete;

    void poll() override;
};

} //!ugame::infrastructure

#endif //!SRC_INFRASTRUCTURE_PLAYER_INPUT_KEYBOARD_INPUT_ADAPTER_HPP
