//
// Created by sst on 24.06.19.
//

#include <gtest/gtest.h>
#include <zmq.h>
#include <MockEventProxy.h>
#include <thread>
#include <src/MonitorClient.h>
#include <src/MonitoredPublisher.h>
#include <src/MonitoredSubscriber.h>
#include <capnzero-base-msgs/string.capnp.h>
#include "mocks/MockEventListener.h"

void callback(capnp::FlatArrayMessageReader& reader)
{
  std::cout << "Called callback..." << std::endl;
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << message << std::endl;
}

TEST(PublisherTest, singleMessageSending)
{
  void* zmqContext = zmq_ctx_new();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(2);

  MonitoredPublisher publisher(zmqContext, listener);
  publisher.bind(capnzero::CommType::UDP, "127.0.0.1:7890");
  publisher.send("this is a message", "newgroup");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(PublisherTest, multipleMessageSending)
{
  void* zmqContext = zmq_ctx_new();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(6);

  MonitoredPublisher publisher(zmqContext, listener);
  publisher.bind(capnzero::CommType::UDP, "127.0.0.1:7890");
  publisher.send("this is a message1", "newgroup");
  publisher.send("this is a message2", "newgroup");
  publisher.send("this is a message3", "newgroup");
  publisher.send("this is a message4", "newgroup");
  publisher.send("this is a message5", "newgroup");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(CombinationTest, publishSubscribeIsMonitored)
{
  void* ctx = zmq_ctx_new();
  const std::string group {"group"};
  const std::string address {"127.0.0.1:7890"};

  MockEventListener *subListener = new MockEventListener();
  EXPECT_CALL(*subListener, notify).Times(4);

  MockEventListener *pubListener = new MockEventListener();
  EXPECT_CALL(*pubListener, notify).Times(2);

  MonitoredSubscriber subscriber(ctx, group, subListener);
  subscriber.connect(capnzero::CommType::UDP, address);
  subscriber.subscribe(&callback);

  MonitoredPublisher publisher(ctx, pubListener);
  publisher.bind(capnzero::CommType::UDP, address);
  publisher.send("This message should reach subscriber", group);

  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}


TEST(CombinationTest, testSinglePublishSubscribeWithoutMonitorClient)
{
  void* ctx = zmq_ctx_new();
  const std::string group {"group"};
  const std::string address {"127.0.0.1:7890"};

  MockEventProxy *proxy = new MockEventProxy();
  EXPECT_CALL(*proxy, notifyClient).Times(4);

  NetworkSocketEventListener *listener = new NetworkSocketEventListener(proxy);
  MonitoredSubscriber subscriber(ctx, group, listener);
  subscriber.connect(capnzero::CommType::UDP, address);
  subscriber.subscribe(&callback);

  MockEventProxy *pubProxy = new MockEventProxy();
  EXPECT_CALL(*pubProxy, notifyClient).Times(2);

  NetworkSocketEventListener *pubListener = new NetworkSocketEventListener(pubProxy);
  MonitoredPublisher publisher(ctx, pubListener);
  publisher.bind(capnzero::CommType::UDP, address);
  publisher.send("This message should reach subscriber", group);

  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

TEST(CombinationTest, testSinglePublishSubscribe)
{
  void* ctx = zmq_ctx_new();
  const std::string group {"group"};
  const std::string address {"127.0.0.1:7890"};

  MonitorClient monitorClient(ctx);
  monitorClient.start();

  RelayEventProxy *proxy = new RelayEventProxy(ctx);
  NetworkSocketEventListener *listener = new NetworkSocketEventListener(proxy);
  MonitoredSubscriber subscriber(ctx, group, listener);
  subscriber.connect(capnzero::CommType::UDP, address);
  subscriber.subscribe(&callback);

  RelayEventProxy *pubProxy = new RelayEventProxy(ctx);
  NetworkSocketEventListener *pubListener = new NetworkSocketEventListener(pubProxy);
  MonitoredPublisher publisher(ctx, pubListener);
  publisher.bind(capnzero::CommType::UDP, address);
  publisher.send("This message should reach subscriber", group);

  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

