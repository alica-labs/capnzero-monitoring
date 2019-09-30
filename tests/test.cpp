#include <gtest/gtest.h>
#include <zmq.h>
#include <MockEventProxy.h>
#include <thread>
#include <MonitorClient.h>
#include <MonitoredPublisher.h>
#include <MonitoredSubscriber.h>
#include <MockEventListener.h>
#include <NetworkSocketEventListener.h>
#include <RelayEventProxy.h>
#include <event/yamleventparser.h>
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
  EXPECT_CALL(*pubListener, notify).Times(3);

  MonitoredSubscriber subscriber(ctx, capnzero::Protocol::UDP, subListener);
  subscriber.addAddress(address);
  subscriber.setTopic(topic);
  subscriber.subscribe(&callback);

  MonitoredPublisher publisher(ctx, capnzero::Protocol::UDP, pubListener);
  publisher.bind(address);
  publisher.send("This message should reach subscriber", topic);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


TEST(CombinationTest, testSinglePublishSubscribeWithoutMonitorClient)
{
  void* ctx = zmq_ctx_new();
  const std::string topic {"group"};
  const std::string address {"127.0.0.1:7890"};

  MockEventProxy *proxy = new MockEventProxy();
  EXPECT_CALL(*proxy, notifyClient).Times(5);

  NetworkSocketEventListener *listener = new NetworkSocketEventListener(proxy);
  MonitoredSubscriber subscriber(ctx, capnzero::Protocol::UDP, listener);
  subscriber.addAddress(address);
  subscriber.setTopic(topic);
  subscriber.subscribe(&callback);

  MockEventProxy *pubProxy = new MockEventProxy();
  EXPECT_CALL(*pubProxy, notifyClient).Times(3);

  NetworkSocketEventListener *pubListener = new NetworkSocketEventListener(pubProxy);
  MonitoredPublisher publisher(ctx, capnzero::Protocol::UDP, pubListener);
  publisher.bind(address);
  publisher.send("This message should reach subscriber", topic);

  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

TEST(CombinationTest, testSinglePublishSubscribe)
{
  void* ctx = zmq_ctx_new();
  const std::string topic {"group"};
  const std::string address {"127.0.0.1:7890"};
  EventParser* eventParser = new YamlEventParser();

  MonitorClient monitorClient(ctx, eventParser);
  monitorClient.start();

  RelayEventProxy *proxy = new RelayEventProxy(ctx);
  NetworkSocketEventListener *listener = new NetworkSocketEventListener(proxy);
  MonitoredSubscriber subscriber(ctx, capnzero::Protocol::UDP, listener);
  subscriber.addAddress(address);
  subscriber.setTopic(topic);
  subscriber.subscribe(&callback);

  RelayEventProxy *pubProxy = new RelayEventProxy(ctx);
  NetworkSocketEventListener *pubListener = new NetworkSocketEventListener(pubProxy);
  MonitoredPublisher publisher(ctx, capnzero::Protocol::UDP, pubListener);
  publisher.bind(address);
  publisher.send("This message should reach subscriber", topic);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  std::vector<const Event*> monitorEvents = monitorClient.retrieveEvents();

  ASSERT_EQ(monitorEvents.size(), 8);
}

