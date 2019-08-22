#include <gtest/gtest.h>

#include <MockEventListener.h>
#include <MonitorClient.h>
#include <MonitoredPublisher.h>
#include <NetworkSocketEventListener.h>
#include <RelayEventProxy.h>

#include <event/yamleventparser.h>

TEST(MonitorClientTest, testReceiveSingleEvent)
{
  void* zmqCtx = zmq_ctx_new();

  RelayEventProxy *proxy = new RelayEventProxy(zmqCtx);
  NetworkSocketEventListener *listener = new NetworkSocketEventListener(proxy);
  MonitoredPublisher pub(zmqCtx, listener);
  EventParser* eventParser = new YamlEventParser();

  MonitorClient monitor(zmqCtx, eventParser);
  monitor.start();

  pub.bind(capnzero::CommType::UDP, "127.0.0.1:18923");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  std::vector<const Event*> monitorEvents = monitor.getEvents();

  ASSERT_EQ(monitorEvents.size(), 1);
}

TEST(MonitorClientTest, testReceiveMultipleEvents)
{
  void* zmqCtx = zmq_ctx_new();

  RelayEventProxy *proxy = new RelayEventProxy(zmqCtx);
  NetworkSocketEventListener *listener = new NetworkSocketEventListener(proxy);
  MonitoredPublisher pub(zmqCtx, listener);
  EventParser* eventParser = new YamlEventParser();

  MonitorClient monitor(zmqCtx, eventParser);
  monitor.start();

  pub.bind(capnzero::CommType::UDP, "127.0.0.1:18923");
  pub.send("testmessage", "groupname");

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  std::vector<const Event*> monitorEvents = monitor.getEvents();

  ASSERT_EQ(monitorEvents.size(), 2);
}
