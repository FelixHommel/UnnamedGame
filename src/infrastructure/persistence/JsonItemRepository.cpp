#include "JsonItemRepository.hpp"

#include "common/Definitions.hpp"
#include "item/Item.hpp"
#include "nlohmann/json.hpp"
#include "stats/StatModifier.hpp"

#include <fstream>
#include <memory>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

namespace ugame::infrastructure
{

JsonItemRepository::JsonItemRepository(const std::filesystem::path& filepath)
    : m_filepath{ filepath }
{}

std::optional<std::shared_ptr<core::Item>> JsonItemRepository::findById(ItemID id) noexcept
{
    if(m_itemCache.empty())
        loadItemsFromFile();

    if(m_itemCache.contains(id))
        return std::make_optional(m_itemCache[id]);

    return std::nullopt;
}

std::vector<std::shared_ptr<core::Item>> JsonItemRepository::findAll() noexcept
{
    if(m_itemCache.empty())
        loadItemsFromFile();

    return std::accumulate(m_itemCache.cbegin(), m_itemCache.cend(), std::vector<std::shared_ptr<core::Item>>(m_itemCache.size()), [](auto vec, const auto& entry) {
        vec.push_back(entry.second);
        return vec;
    });
}

/// \brief Load all items from the file
void JsonItemRepository::loadItemsFromFile() noexcept
{
    std::ifstream in(m_filepath);

    nlohmann::json j{};

    in >> j;

    for(auto& element : j[itemsField])
    {
        core::StatModifier mods {
            .hp = element[statsField][statsHpField].get<hp_t>(),
            .attack = element[statsField][statsAttackField].get<attack_t>(),
            .defense = element[statsField][statsDefenseField].get<defense_t>(),
            .speed = element[statsField][statsSpeedField].get<speed_t>(),
            .luck = element[statsField][statsLuckField].get<luck_t>()
        };

        m_itemCache.insert({element[idField].get<ItemID>(), std::make_shared<core::Item>(
            element[idField].get<ItemID>(),
            element[nameField].get<std::string>(),
            element[typeField].get<core::ItemType>(),
            mods
        )});
    }

    in.close();
}

} // !ugame::infrastructure
