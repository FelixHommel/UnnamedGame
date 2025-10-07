#ifndef SRC_CORE_ITEM_I_ITEM_REPOSITORY_HPP
#define SRC_CORE_ITEM_I_ITEM_REPOSITORY_HPP

#include "common/Definitions.hpp"
#include "Item.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace ugame::core
{

/// \brief Interface to access the avilable items
///
/// \author Felix Hommel
/// \date 10/5/2025
class IItemRepository
{
public:
    constexpr explicit IItemRepository() = default;
    virtual ~IItemRepository() = default;

    IItemRepository(const IItemRepository&) = default;
    IItemRepository(IItemRepository&&) = default;
    IItemRepository& operator=(const IItemRepository&) = default;
    IItemRepository& operator=(IItemRepository&&) = default;

    /// \brief retrieve the item specified by it's ID
    virtual std::optional<std::shared_ptr<Item>> findById(ItemID id) noexcept = 0;
    /// \brief retrieve all items
    virtual std::vector<std::shared_ptr<Item>> findAll() noexcept = 0;
};

} // !ugame::core

#endif // !SRC_CORE_ITEM_I_ITEM_REPOSITORY_HPP
