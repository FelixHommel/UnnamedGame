#ifndef SRC_CORE_COMMON_I_PLAYER_INPUT_HPP
#define SRC_CORE_COMMON_I_PLAYER_INPUT_HPP

#include "gameLoop/EventBus.hpp"

namespace ugame::core::common
{
using namespace ugame::core::gameloop;

/// \brief Interface that handles input from users
///
/// \author Felix Hommel
/// \date 10/13/2025
class IPlayerInput
{
public:
    explicit IPlayerInput(EventBus& publisher)
        : m_publisher(publisher)
    {}

    virtual ~IPlayerInput() = default;

    IPlayerInput(const IPlayerInput&) = default;
    IPlayerInput(IPlayerInput&&) = delete;
    IPlayerInput& operator=(const IPlayerInput&) = delete;
    IPlayerInput& operator=(IPlayerInput&&) = delete;

    /// \brief Poll for new input
    virtual void poll() = 0;

protected:
    EventBus& m_publisher;
};

} //!ugame::core::common

#endif //!SRC_CORE_COMMON_I_PLAYER_INPUT_HPP
