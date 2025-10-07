#ifndef SRC_INFRASTRUCTURE_PERSISTENCE_JSON_ITEM_REPOSITORY_HPP
#define SRC_INFRASTRUCTURE_PERSISTENCE_JSON_ITEM_REPOSITORY_HPP

#include "item/IItemRepository.hpp"
#include "item/Item.hpp"

#include <filesystem>
#include <map>
#include <memory>
#include <optional>
#include <vector>

namespace ugame::infrastructure
{

/// \brief Implementation of Item repositories using JSON format
///
/// \author Felix Hommel
/// \date 10/5/2025
class JsonItemRepository : public core::IItemRepository
{
public:
    /// \brief Construct a new ItemRepository by providing the path to the file's location
    explicit JsonItemRepository(const std::filesystem::path& filepath);
    ~JsonItemRepository() override = default;

    JsonItemRepository(const JsonItemRepository&) = default;
    JsonItemRepository(JsonItemRepository&&) = delete;
    JsonItemRepository& operator=(const JsonItemRepository&) = default;
    JsonItemRepository& operator=(JsonItemRepository&&) = delete;

    std::optional<std::shared_ptr<core::Item>> findById(ItemID id) noexcept override;
    std::vector<std::shared_ptr<core::Item>> findAll() noexcept override;

private:
    std::filesystem::path m_filepath;
    std::map<ItemID, std::shared_ptr<core::Item>> m_itemCache;

    static constexpr std::string itemsField{ "items" };
    static constexpr std::string idField{ "id" };
    static constexpr std::string nameField{ "name" };
    static constexpr std::string typeField{ "type" };
    static constexpr std::string statsField{ "stats" };
    static constexpr std::string statsHpField{ "hp" };
    static constexpr std::string statsAttackField{ "attack" };
    static constexpr std::string statsDefenseField{ "defense" };
    static constexpr std::string statsSpeedField{ "speed" };
    static constexpr std::string statsLuckField{ "luck" };

    void loadItemsFromFile() noexcept;
};

} // !ugame::infrastructure

#endif // !SRC_INFRASTRUCTURE_PERSISTENCE_JSON_ITEM_REPOSITORY_HPP
