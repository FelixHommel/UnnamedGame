#ifndef SRC_CORE_COMMON_DEFINITIONS_HPP
#define SRC_CORE_COMMON_DEFINITIONS_HPP

#include <cstdint>

namespace ugame::core::common
{

using ItemID = std::uint32_t;

using hp_t = std::uint16_t;
using attack_t = std::uint16_t;
using defense_t = std::uint16_t;
using speed_t = std::uint8_t;
using luck_t = std::uint8_t;

} // !ugmae::core::common

#endif // !SRC_CORE_COMMON_DEFINITIONS_HPP
