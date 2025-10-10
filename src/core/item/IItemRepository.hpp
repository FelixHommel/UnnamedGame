#ifndef SRC_CORE_ITEM_I_ITEM_REPOSITORY_HPP
#define SRC_CORE_ITEM_I_ITEM_REPOSITORY_HPP

#include "common/Definitions.hpp"
#include "Item.hpp"

#include <vector>

namespace ugame::core
{

/// \brief Interface to access the avilable items
///
/// ItemRepositories are responsible for providing callers with information about items they are requesting.
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

    /// \brief retrieve a item specified by it's ID
    ///
    /// \param id \ref ItemID of the requested Item
    ///
    /// \return pointer to const Item, nullptr if no Item matches \p id
    virtual const Item* findById(ItemID id) = 0;
    /// \brief retrieve all items
    ///
    /// \return all avaialble items in a \ref std::vector of pointers to const Item
    virtual std::vector<const Item*> findAll() = 0;
};

} // !ugame::core

#endif // !SRC_CORE_ITEM_I_ITEM_REPOSITORY_HPP
