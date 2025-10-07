#include "gtest/gtest.h"
#include <filesystem>
#include <optional>

#include "persistence/JsonItemRepository.hpp"

namespace ugame::test::infrastructure
{

class JsonItemRepositoryTest : public testing::Test
{
protected:
    ugame::infrastructure::JsonItemRepository repo{ "../../../../Items.json" };
};

TEST_F(JsonItemRepositoryTest, FindById)
{
    EXPECT_EQ(repo.findById(12345), std::nullopt);
}

TEST_F(JsonItemRepositoryTest, FindAll)
{
    EXPECT_EQ(repo.findAll().size(), 2);
}

} // !ugame::test::infrastructure
