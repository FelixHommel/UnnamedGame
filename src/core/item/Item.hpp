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

    void setID(ItemID id) noexcept { m_id = id; }
    void setName(const std::string& name) noexcept { m_name = name; }
    void setItemType(ItemType type) noexcept { m_type = type; }

private:
    ItemID m_id{};
    std::string m_name;
    ItemType m_type{};
    StatModifier m_stats{};
};

} // !ugame::core

#endif // !SRC_CORE_ITEM_ITEM_HPP
