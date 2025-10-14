#include "gameLoop/EventBus.hpp"

#include "common/IEvent.hpp"

#include <gtest/gtest.h>

#include <string>

namespace ugame::test::core::eventBus
{
using namespace ugame::core;

struct TestEvent1 : public IEvent { int value; };
struct TestEvent2 : public IEvent { std::string value; };

class EventBusTest : public testing::Test
{
protected:
    EventBus eventBus;
};

TEST_F(EventBusTest, SingleSubscriberSingleEvent)
{
    const int testValue{ 65491 };
    int receivedValue{};

    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ receivedValue = event.value; });
    eventBus.publish(TestEvent1{ .value = testValue });

    EXPECT_EQ(receivedValue, testValue);
}

TEST_F(EventBusTest, MultipleSubscribersSingleEvent)
{
    const int testValue{ 76123 };
    int subscriber1{};
    int subscriber2{};

    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ subscriber1 = event.value; });
    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ subscriber2 = event.value; });
    eventBus.publish(TestEvent1{ .value = testValue });

    EXPECT_EQ(subscriber1, testValue);
    EXPECT_EQ(subscriber2, testValue);
}

TEST_F(EventBusTest, SingleSubscriberMultipleEvents)
{
    const int testValueEvent1{ 89124 };
    const std::string testValueEvent2{ "jhkasb" };
    int receivedValueEvent1{};
    std::string receivedValueEvent2{};

    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ receivedValueEvent1 = event.value; });
    eventBus.subscribe<TestEvent2>([&](const TestEvent2& event){ receivedValueEvent2 = event.value; });
    eventBus.publish(TestEvent1{ .value = testValueEvent1 });
    eventBus.publish(TestEvent2{ .value = testValueEvent2 });

    EXPECT_EQ(receivedValueEvent1, testValueEvent1);
    EXPECT_EQ(receivedValueEvent2, testValueEvent2);
}

TEST_F(EventBusTest, MultipleSubscribersMultipleEvents)
{
    const int testValueEvent1{ 124985 };
    const std::string testValueEvent2{ "asdfljbg" };
    int receivedValueEvent1Sub1{};
    int receivedValueEvent1Sub2{};
    std::string receivedValueEvent2Sub1{};
    std::string receivedValueEvent2Sub2{};

    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ receivedValueEvent1Sub1 = event.value; });
    eventBus.subscribe<TestEvent1>([&](const TestEvent1& event){ receivedValueEvent1Sub2 = event.value; });
    eventBus.subscribe<TestEvent2>([&](const TestEvent2& event){ receivedValueEvent2Sub1 = event.value; });
    eventBus.subscribe<TestEvent2>([&](const TestEvent2& event){ receivedValueEvent2Sub2 = event.value; });
    eventBus.publish(TestEvent1{ .value = testValueEvent1 });
    eventBus.publish(TestEvent2{ .value = testValueEvent2 });

    EXPECT_EQ(receivedValueEvent1Sub1, testValueEvent1);
    EXPECT_EQ(receivedValueEvent1Sub2, testValueEvent1);
    EXPECT_EQ(receivedValueEvent2Sub1, testValueEvent2);
    EXPECT_EQ(receivedValueEvent2Sub2, testValueEvent2);
}

} // !ugame::test::core
