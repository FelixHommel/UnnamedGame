#ifndef SRC_TEST_CORE_ITEM_ItemRepositroyInterfaceTest
#define SRC_TEST_CORE_ITEM_ItemRepositroyInterfaceTest

#include "persistence/JsonItemRepository.hpp"

#include "gtest/gtest.h"

namespace ugame::test::core
{

template<typename TRepo>
class ItemRepositoryContractTest : public ::testing::Test
{
protected:
    TRepo repo; //NOLINT

public:
    ItemRepositoryContractTest() = default;
    static constexpr auto testSuiteName{ "ItemRepositoryContractTest" };
};

TYPED_TEST_SUITE_P(ItemRepositoryContractTest);

TYPED_TEST_P(ItemRepositoryContractTest, FindById)
{
}

REGISTER_TYPED_TEST_SUITE_P(ItemRepositoryContractTest, FindById);

using RepositoryImplementation = ::testing::Types<infrastructure::JsonItemRepository>;
INSTANTIATE_TYPED_TEST_SUITE_P(AllRepos, ItemRepositoryContractTest, RepositoryImplementation);

} //!ugame::test::core

#endif //!SRC_TEST_CORE_ITEM_ItemRepositroyInterfaceTest
