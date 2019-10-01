#include <client/capnzerodebugeventproxy.h>
#include <client/debugmonitorclient.h>

DebugMonitorClient::DebugMonitorClient(CapnzeroDebugEventProxy& proxy): proxy(proxy)
{

}

void DebugMonitorClient::start()
{
  running = true;
  proxy.startListening();
}

void DebugMonitorClient::stop()
{
  running = false;
  proxy.stopListening();
}

bool DebugMonitorClient::isRunning() const
{
  return running;
}
