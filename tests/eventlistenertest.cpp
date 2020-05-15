#include <networksocketeventlistener.h>
#include <mockeventproxy.h>
#include <event/sendevent.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <event/event.h>

MATCHER_P(eventEquals, event, "")
{
  return arg.toYaml() == event.toYaml();
}

TEST(ListenerTest, testSimpleEvent)
{
  const std::string type{"event"};
  const std::string data{"this is an event!"};
  SendEvent event("0", "message");

  MockEventProxy *proxy = new MockEventProxy();
  EXPECT_CALL(*proxy, notifyClient(eventEquals(event)));

  NetworkSocketEventListener listener(proxy);

  listener.notify(event);

  delete proxy;
}
