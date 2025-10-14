#ifndef SRC_CORE_ITEM_ITEM_HPP
#define SRC_CORE_ITEM_ITEM_HPP

#include "common/Definitions.hpp"
#include "stats/StatModifier.hpp"

#include <cstdint>
#include <string>

namespace ugame::core
{

/// \brief Classification of Items
///
/// \author Felix Hommel
/// \date 10/5/2025
enum class ItemType : std::uint8_t
{
    WEAPON, UNDEFINED
};

/// \brief Convert strings to \ref ItemType
static ItemType toItemType(std::string_view str)
{
    using enum ItemType;

    if(str == "WEAPON")
        return WEAPON;

    return UNDEFINED;
}

/// \brief Items are something the  Player can interact with or use
///
/// \author Felix Hommel
/// \date 10/5/2025
class Item
{
public:
    Item() = default;
    Item(ItemID id, const std::string& name, ItemType type, StatModifier stats);

    [[nodiscard]] ItemID getID() const noexcept { return m_id; }
    [[nodiscard]] std::string getName() const noexcept { return m_name; }
    [[nodiscard]] ItemType getType() const noexcept { return m_type; }
    [[nodiscard]] StatModifier getStats() const noexcept { return m_stats; }

private:
    ItemID m_id{};
    std::string m_name;
    ItemType m_type{};
    StatModifier m_stats{};
};

} // !ugame::core

#endif // !SRC_CORE_ITEM_ITEM_HPP
