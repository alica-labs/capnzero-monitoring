#include <gtest/gtest.h>
#include <zmq.h>
#include <mockeventproxy.h>
#include <thread>
#include <monitoredpublisher.h>
#include <monitoredsubscriber.h>
#include <tests/mocks/mockeventlistener.h>
#include <networksocketeventlistener.h>
#include <capnzero-base-msgs/string.capnp.h>

void callback(capnp::FlatArrayMessageReader& reader)
{
  std::cout << "Called callback..." << std::endl;
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << message << std::endl;
}

TEST(CombinationTest, publishSubscribeIsMonitored)
{
  void* ctx = zmq_ctx_new();
  const std::string topic {"group"};
  const std::string address {"127.0.0.1:7890"};

  MockEventListener *subListener = new MockEventListener();
  EXPECT_CALL(*subListener, notify).Times(5);

  MockEventListener *pubListener = new MockEventListener();
  EXPECT_CALL(*pubListener, notify).Times(4);

  MonitoredSubscriber subscriber("1", ctx, capnzero::Protocol::UDP, subListener);
  subscriber.addAddress(address);
  subscriber.setTopic(topic);
  subscriber.subscribe(&callback);

  MonitoredPublisher publisher("0", ctx, capnzero::Protocol::UDP, pubListener);
  publisher.addAddress(address);
  publisher.send("This message should reach subscriber", topic);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


TEST(CombinationTest, testSinglePublishSubscribe)
{
  void* ctx = zmq_ctx_new();
  const std::string topic {"group"};
  const std::string address {"127.0.0.1:7890"};

  MockEventProxy *proxy = new MockEventProxy();
  EXPECT_CALL(*proxy, notifyClient).Times(5);

  NetworkSocketEventListener *listener = new NetworkSocketEventListener(proxy);
  MonitoredSubscriber subscriber("1", ctx, capnzero::Protocol::UDP, listener);
  subscriber.addAddress(address);
  subscriber.setTopic(topic);
  subscriber.subscribe(&callback);

  MockEventProxy *pubProxy = new MockEventProxy();
  EXPECT_CALL(*pubProxy, notifyClient).Times(4);

  NetworkSocketEventListener *pubListener = new NetworkSocketEventListener(pubProxy);
  MonitoredPublisher publisher("0", ctx, capnzero::Protocol::UDP, pubListener);
  publisher.addAddress(address);
  publisher.send("This message should reach subscriber", topic);

  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}
