#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <monitoredpublisher.h>
#include <zmq.h>
#include <monitoredsubscriber.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <tests/mocks/mockeventlistener.h>

class MyComplexCallback
{
public:
  MyComplexCallback() : counter {0}
  {}

  void monitor(capnp::FlatArrayMessageReader& reader)
  {
    const std::string message = reader.getRoot<capnzero::String>().getString();
    std::cout << "Message received: \"" << message << "\"" << std::endl;

    counter++;
  }

  int counter;
};

void subscriberCallback(capnp::FlatArrayMessageReader& reader)
{
  std::cout << "Called callback..." << std::endl;
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << message << std::endl;
}

TEST(MonitoredSubscriberTest, connectAndSubscribeAreNotified)
{
  void* zmqContext = zmq_ctx_new();

  MockEventListener *listener = new MockEventListener();
  EXPECT_CALL(*listener, notify).Times(4);

  MonitoredSubscriber subscriber("1", zmqContext, capnzero::Protocol::UDP, listener);
  subscriber.addAddress("127.0.0.1:7890");
  subscriber.setTopic("newgroup");
  subscriber.subscribe(&subscriberCallback);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(MonitoredSubscriberTest, singleMessageReceiving)
{
  void* zmqContext = zmq_ctx_new();
  const std::string address{"127.0.0.1:7890"};
  const std::string topic{"newgroup"};

  MockEventListener *subListener = new MockEventListener();
  EXPECT_CALL(*subListener, notify).Times(5);

  MockEventListener *pubListener = new MockEventListener();

  MonitoredSubscriber subscriber("1", zmqContext, capnzero::Protocol::UDP, subListener);
  subscriber.addAddress(address);
  subscriber.setTopic(topic);
  subscriber.subscribe(&subscriberCallback);

  MonitoredPublisher publisher("0", zmqContext, capnzero::Protocol::UDP, pubListener);
  publisher.addAddress(address);
  publisher.send("Message", topic);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


TEST(MonitoredSubscriberTest, singleMessageReceivingWithComplexCallback)
{
  void* zmqContext = zmq_ctx_new();
  const std::string address{"127.0.0.1:7890"};
  const std::string topic{"newgroup"};

  MockEventListener *subListener = new MockEventListener();
  EXPECT_CALL(*subListener, notify).Times(5);

  MockEventListener *pubListener = new MockEventListener();

  MonitoredPublisher publisher("0", zmqContext, capnzero::Protocol::UDP, pubListener);
  publisher.addAddress(address);

  MonitoredSubscriber subscriber("1", zmqContext, capnzero::Protocol::UDP, subListener);
  subscriber.addAddress(address);
  subscriber.setTopic(topic);

  MyComplexCallback* callbackObject = new MyComplexCallback();
  subscriber.subscribe<MyComplexCallback>(&MyComplexCallback::monitor, callbackObject);

  publisher.send("Message", topic);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(callbackObject->counter, 1);
  delete callbackObject;
}
