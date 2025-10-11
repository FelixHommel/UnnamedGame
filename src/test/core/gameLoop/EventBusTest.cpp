#include "gameLoop/EventBus.hpp"

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
    this->eventBus.subscribe<TypeParam>([](TypeParam value) { std::cout << "Got something: " << value <<  "\n"; ASSERT_FALSE(true); });
    this->eventBus.publish(TypeParam());
}

REGISTER_TYPED_TEST_SUITE_P(EventBusTest, subscribe);

using TypeList = ::testing::Types<int, float>;
INSTANTIATE_TYPED_TEST_SUITE_P(Test, EventBusTest, TypeList);

} // !ugame::test::core
