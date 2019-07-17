//
// Created by sst on 24.06.19.
//

#include <gtest/gtest.h>
#include <zmq.h>
#include <capnp/serialize.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <capnzero/Common.h>
#include <thread>
#include <src/MonitorClient.h>
#include <src/MonitoredPublisher.h>
#include <src/MonitoredSubscriber.h>

void callback(capnp::FlatArrayMessageReader& reader)
{
  std::cout << "Called callback..." << std::endl;
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << message << std::endl;
}

TEST(PublisherTest, singleMessageSending)
{
  void* zmqContext = zmq_ctx_new();

  MonitorClient monitor(zmqContext);
  monitor.start();

  MonitoredPublisher publisher(zmqContext);

  publisher.bind(capnzero::CommType::UDP, "127.0.0.1:7890");
  publisher.send("this is a message", "newgroup");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
  MonitoredSubscriber subscriber(ctx, group);
  subscriber.attachEventListener(listener);

  MonitoredPublisher publisher(ctx);

  subscriber.connect(capnzero::CommType::UDP, address);
  publisher.bind(capnzero::CommType::UDP, address);

  subscriber.subscribe(&callback);
  publisher.send("This message should reach subscriber", group);

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  delete listener;
  delete proxy;
}
