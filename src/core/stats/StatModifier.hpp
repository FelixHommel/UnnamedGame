#ifndef SRC_CORE_STATS_STAT_MODIFIER_HPP
#define SRC_CORE_STATS_STAT_MODIFIER_HPP

#include "common/Definitions.hpp"

namespace ugame::core
{

/// \brief describes how something affects the Players stats
///
/// The values in StatModifier will be added additively to the Players stats
///
/// \author Felix Hommel
/// \date 10/6/2025
struct StatModifier
{
    hp_t hp;
    attack_t attack;
    defense_t defense;
    speed_t speed;
    luck_t luck;
};

} //!ugame::core

#endif //!SRC_CORE_STATS_STAT_MODIFIER_HPP
