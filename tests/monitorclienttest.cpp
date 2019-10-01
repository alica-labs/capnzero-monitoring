#include <gtest/gtest.h>
#include <thread>
#include <monitoredpublisher.h>
#include <networksocketeventlistener.h>
#include <relayeventproxy.h>
#include <client/capnzerodebugeventproxy.h>
#include <client/debugmonitorclient.h>
#include <client/printdebugeventhandler.h>

TEST(MonitorClientTest, testReceiveSingleEvent)
{
  void* zmqCtx = zmq_ctx_new();

  PrintDebugEventHandler* handler = new PrintDebugEventHandler();
  CapnzeroDebugEventProxy capnzeroProxy(handler);

  DebugMonitorClient client(capnzeroProxy);
  client.start();

  RelayEventProxy* proxy = new RelayEventProxy(zmqCtx);
  NetworkSocketEventListener* listener = new NetworkSocketEventListener(proxy);
  MonitoredPublisher pub(zmqCtx, capnzero::Protocol::UDP, listener);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  client.stop();
}
