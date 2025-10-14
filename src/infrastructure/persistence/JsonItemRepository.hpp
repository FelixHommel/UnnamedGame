#ifndef SRC_INFRASTRUCTURE_PERSISTENCE_JSON_ITEM_REPOSITORY_HPP
#define SRC_INFRASTRUCTURE_PERSISTENCE_JSON_ITEM_REPOSITORY_HPP

#include "common/ILogger.hpp"
#include "common/IItemRepository.hpp"
#include "item/Item.hpp"

#include "nlohmann/json.hpp"

#include <filesystem>
#include <map>
#include <memory>
#include <vector>

namespace ugame::infrastructure::persistence
{
using namespace ugame::core::common;
using namespace ugame::core::item;

/// \brief Implementation of Item repositories using JSON format
///
/// \author Felix Hommel
/// \date 10/5/2025
class JsonItemRepository : public IItemRepository
{
public:
    /// \brief Construct a new ItemRepository by providing the path to the file's location
    explicit JsonItemRepository(const std::filesystem::path& filepath, std::shared_ptr<core::ILogger> logger);
    ~JsonItemRepository() override = default;

    JsonItemRepository(const JsonItemRepository&) = default;
    JsonItemRepository(JsonItemRepository&&) = default;
    JsonItemRepository& operator=(const JsonItemRepository&) = default;
    JsonItemRepository& operator=(JsonItemRepository&&) = default;

    const Item* findById(ItemID id) override;
    std::vector<const Item*> findAll() override;

private:
    std::filesystem::path m_filepath;
    std::shared_ptr<core::ILogger> m_logger;
    std::map<ItemID, Item> m_itemCache; // NOTE: potentially needs to be changed to unique_ptrs in the future

    void checkCache();
    void loadItemsFromFile();
    [[nodiscard]] bool validateJson(const nlohmann::json& itemJson) const;

    static constexpr auto SCHEMA_FILE_PATH{ "schemas/Items.schema.json" };
    static constexpr auto ITEM_ARRAY_FIELD{ "item_array" };
    static constexpr auto ID_FIELD{ "id" };
    static constexpr auto NAME_FIELD{ "name" };
    static constexpr auto TYPE_FIELD{ "type" };
    static constexpr auto STATS_FIELD{ "stats" };
    static constexpr auto STATS_HP_FIELD{ "hp" };
    static constexpr auto STATS_ATTACK_FIELD{ "attack" };
    static constexpr auto STATS_DEFENSE_FIELD{ "defense" };
    static constexpr auto STATS_SPEED_FIELD{ "speed" };
    static constexpr auto STATS_LUCK_FIELD{ "luck" };
};

} // !ugame::infrastructure::persistence

#endif // !SRC_INFRASTRUCTURE_PERSISTENCE_JSON_ITEM_REPOSITORY_HPP
