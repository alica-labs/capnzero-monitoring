//
// Created by sst on 7/8/19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MonitoredPublisher.h>
#include <zmq.h>
#include <src/MonitorClient.h>
#include <src/MonitoredSubscriber.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <tests/mocks/MockEventListener.h>

void subscriberCallback(capnp::FlatArrayMessageReader& reader)
{
  std::cout << "Called callback..." << std::endl;
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << message << std::endl;
}

TEST(MonitoredSubscriberTest, connectAndSubscribeAreNotified)
{
  void* zmqContext = zmq_ctx_new();

  MonitorClient monitor(zmqContext);
  monitor.start();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(2);

  MonitoredSubscriber subscriber(zmqContext, "newgroup");
  subscriber.attachEventListener(listener);

  subscriber.connect(capnzero::CommType::UDP, "127.0.0.1:7890");

  subscriber.subscribe(&subscriberCallback);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  delete listener;
}

TEST(MonitoredSubscriberTest, singleMessageReceiving)
{
  void* zmqContext = zmq_ctx_new();
  const std::string address{"127.0.0.1:7890"};
  const std::string group{"newgroup"};

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(3);

  MonitoredPublisher publisher(zmqContext);
  publisher.bind(capnzero::CommType::UDP, address);

  MonitoredSubscriber subscriber(zmqContext, group);
  subscriber.attachEventListener(listener);

  subscriber.connect(capnzero::CommType::UDP, address);

  subscriber.subscribe(&subscriberCallback);
  publisher.send("Message", group);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  delete listener;
}
