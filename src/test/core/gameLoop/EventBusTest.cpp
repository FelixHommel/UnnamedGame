#include "gameLoop/EventBus.hpp"

#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

namespace ugame::test::core
{
using namespace ugame::core;

template<typename T>
class EventBusTest : public testing::Test
{
protected:
    EventBus eventBus;
};

TYPED_TEST_SUITE_P(EventBusTest);

TYPED_TEST_P(EventBusTest, subscribe)
{
    this->eventBus.subscribe<TypeParam>([](TypeParam) { std::cout << "Got something\n"; });
    ASSERT_TRUE(false);
}

REGISTER_TYPED_TEST_SUITE_P(EventBusTest, subscribe);

using TypeList = ::testing::Types<char, int, std::string, float>;
INSTANTIATE_TYPED_TEST_SUITE_P(Test, EventBusTest, TypeList);

} // !ugame::test::core
