#include "gtest/gtest.h"

#include "common/Definitions.hpp"
#include "common/ILogger.hpp"
#include "common/exceptions/RepositoryException.hpp"
#include "item/Item.hpp"
#include "logging/SpdlogAdapter.hpp"
#include "persistence/JsonItemRepository.hpp"

#include <memory>
#include <string>
#include <vector>

namespace ugame::test::infrastructure
{
using namespace ugame::infrastructure;
using namespace ugame::core::common;

/// \brief Class to test \ref JsonItemRepository
///
/// \author Felix Hommel
/// \date 10/9/2025
class JsonItemRepositoryTest : public testing::Test
{
protected:
    std::shared_ptr<ILogger> m_logger{ std::make_shared<logging::SpdlogAdapter>() };
    persistence::JsonItemRepository repo{ std::string(RESOURCE_DIR) + JSON_ITEM_FILE , m_logger };

private:
    static constexpr auto JSON_ITEM_FILE{ "Items.json" };
};

TEST_F(JsonItemRepositoryTest, FindById)
{
    const ItemID queriedId{ 0 };

    const core::Item* queryResult{};
    ASSERT_NO_THROW({ queryResult = repo.findById(queriedId); });

    ASSERT_NE(queryResult, nullptr);
    EXPECT_EQ(queryResult->getID(), queriedId);
}

TEST_F(JsonItemRepositoryTest, FindByIdNonExistentId)
{
    const ItemID queriedId{ 1234 };

    const core::Item* queryResult{};
    ASSERT_NO_THROW({ queryResult = repo.findById(queriedId); });

    EXPECT_EQ(queryResult, nullptr);
}

TEST_F(JsonItemRepositoryTest, FindAll)
{
    std::vector<const core::Item*> queryResult;
    ASSERT_NO_THROW({ queryResult = repo.findAll(); });

    EXPECT_EQ(queryResult.size(), 2);
}

TEST_F(JsonItemRepositoryTest, LoadNonExistentFile)
{
    persistence::JsonItemRepository invalidRepo("./NonExistentFile", m_logger);
    ItemID queriedId{ 0 };

    ASSERT_THROW({ invalidRepo.findById(queriedId); }, core::RepositroyException);
    ASSERT_THROW({ invalidRepo.findAll(); }, core::RepositroyException);
}

TEST_F(JsonItemRepositoryTest, LoadInvalidSchemeFile)
{
    persistence::JsonItemRepository invalidRepo(std::string(RESOURCE_DIR) + "InvalidSchemeItemFile.json", m_logger);
    ItemID queriedId{ 0 };

    ASSERT_THROW({ invalidRepo.findById(queriedId); }, core::RepositroyException);
    ASSERT_THROW({ invalidRepo.findAll(); }, core::RepositroyException);
}

} // !ugame::test::infrastructure
