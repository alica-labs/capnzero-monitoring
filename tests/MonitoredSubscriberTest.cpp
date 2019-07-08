//
// Created by sst on 7/8/19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <zmq.h>
#include <src/MonitorClient.h>
#include <src/MonitoredSubscriber.h>
#include <capnzero-base-msgs/string.capnp.h>

void subscriberCallback(capnp::FlatArrayMessageReader& reader)
{
  std::cout << "Called callback..." << std::endl;
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << message << std::endl;
}

TEST(MonitoredSubscriberSubscriberTest, singleMessageReceiving)
{
  void* zmqContext = zmq_ctx_new();

  MonitorClient monitor(zmqContext);
  monitor.start();

  MonitoredSubscriber subscriber(zmqContext, "newgroup");

  subscriber.connect(capnzero::CommType::UDP, "127.0.0.1:7890");

  subscriber.subscribe(&subscriberCallback);
}