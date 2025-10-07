#ifndef SRC_TEST_CORE_ITEM_ItemRepositroyInterfaceTest
#define SRC_TEST_CORE_ITEM_ItemRepositroyInterfaceTest

#include "gtest/gtest.h"

namespace ugame::test::core
{

template<typename TRepo>
class ItemRepositoryContractTest : public testing::Test
{
public:
    ItemRepositoryContractTest() = default;

    TRepo repo; //NOLINT
};

} //!ugame::test::core

#endif //!SRC_TEST_CORE_ITEM_ItemRepositroyInterfaceTest
