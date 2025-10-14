#include "Item.hpp"

namespace ugame::core::item
{

Item::Item(ItemID id, const std::string& name, ItemType type, StatModifier stats)
    : m_id(id)
    , m_name{ name }
    , m_type{ type }
    , m_stats{ stats }
{}

} // !ugame::core::item
