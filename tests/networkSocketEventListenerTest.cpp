//
// Created by sst on 7/7/19.
//

#include <src/NetworkSocketEventListener.h>
#include <tests/mocks/MockEventProxy.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(ListenerTest, testSimpleEvent)
{
  const std::string message {"got a message"};

  MockEventProxy* proxy = new MockEventProxy();
  EXPECT_CALL(*proxy, notifyClient(message));

  NetworkSocketEventListener listener(proxy);

  listener.notify(message);
}
