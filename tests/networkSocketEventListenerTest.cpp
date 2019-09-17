#include <NetworkSocketEventListener.h>
#include "mocks/MockEventProxy.h"
#include <event/SendEvent.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <event/Event.h>

MATCHER_P(eventEquals, event, "")
{
  return arg.toYaml() == event.toYaml();
}

TEST(ListenerTest, testSimpleEvent)
{
  const std::string type{"event"};
  const std::string data{"this is an event!"};
  SendEvent event("message", "group");

  MockEventProxy* proxy = new MockEventProxy();
  EXPECT_CALL(*proxy, notifyClient(eventEquals(event)));

  NetworkSocketEventListener listener(proxy);

  listener.notify(event);
}
