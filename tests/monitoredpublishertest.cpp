#include <gtest/gtest.h>
#include <MockEventListener.h>
#include <MonitoredPublisher.h>
#include <zmq.h>
#include <thread>

TEST(PublisherTest, singleMessageSending)
{
  void* zmqContext = zmq_ctx_new();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(3);

  MonitoredPublisher publisher(zmqContext, capnzero::Protocol::UDP, listener);
  publisher.bind("127.0.0.1:7890");
  publisher.send("this is a message", "newgroup");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(PublisherTest, multipleMessageSending)
{
  void* zmqContext = zmq_ctx_new();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(7);

  MonitoredPublisher publisher(zmqContext, capnzero::Protocol::UDP, listener);
  publisher.bind("127.0.0.1:7890");
  publisher.send("this is a message1", "newgroup");
  publisher.send("this is a message2", "newgroup");
  publisher.send("this is a message3", "newgroup");
  publisher.send("this is a message4", "newgroup");
  publisher.send("this is a message5", "newgroup");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
