#include "gameLoop/EventBus.hpp"

#include <gtest/gtest.h>

#include <string>

namespace ugame::test::core::eventBus
{
using namespace ugame::core;

struct TestEvent1 { int value; };
struct TestEvent2 { std::string value; };

class EventBusTest : public testing::Test
{
protected:
    EventBus eventBus;
};

TEST_F(EventBusTest, SingleSubscriberReceivesEvent)
{
    const int testValue{ 65491 };
    int receivedValue{};

    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ receivedValue = event.value; });
    eventBus.publish(TestEvent1(testValue));

    EXPECT_EQ(receivedValue, testValue);
}

TEST_F(EventBusTest, MultipleSubscribersReceiveEvent)
{
    const int testValue{ 76123 };
    int subscriber1{};
    int subscriber2{};

    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ subscriber1 = event.value; });
    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ subscriber2 = event.value; });
    eventBus.publish(TestEvent1(testValue));

    EXPECT_EQ(subscriber1, testValue);
    EXPECT_EQ(subscriber2, testValue);
}

} // !ugame::test::core
