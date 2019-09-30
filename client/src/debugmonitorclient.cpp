#include <debugmonitorclient.h>

DebugMonitorClient::DebugMonitorClient(DebugEventProxy *proxy) : running {false}, proxy(proxy)
{
}

DebugMonitorClient::~DebugMonitorClient()
{
  delete proxy;
}

void DebugMonitorClient::start()
{
  running = true;
}

void DebugMonitorClient::stop()
{
  running = false;
}

bool DebugMonitorClient::isRunning() const
{
  return running;
}
