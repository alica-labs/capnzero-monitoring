#include <gtest/gtest.h>
#include <mockeventlistener.h>
#include <monitoredpublisher.h>
#include <zmq.h>
#include <thread>

TEST(PublisherTest, singleMessageSending)
{
  void *zmqContext = zmq_ctx_new();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(3);

  MonitoredPublisher publisher("0", zmqContext, capnzero::Protocol::UDP);
  publisher.attachEventListener(listener);
  publisher.addAddress("127.0.0.1:7890");
  publisher.send("this is a message", "newgroup");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  delete listener;
}

TEST(PublisherTest, multipleMessageSending)
{
  void *zmqContext = zmq_ctx_new();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(11);

  MonitoredPublisher publisher("0", zmqContext, capnzero::Protocol::UDP);
  publisher.attachEventListener(listener);
  publisher.addAddress("127.0.0.1:7890");
  publisher.send("this is a message1", "newgroup");
  publisher.send("this is a message2", "newgroup");
  publisher.send("this is a message3", "newgroup");
  publisher.send("this is a message4", "newgroup");
  publisher.send("this is a message5", "newgroup");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  delete listener;
}
