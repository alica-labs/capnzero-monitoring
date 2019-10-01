#include <client/debugmonitorclient.h>
#include <client/printdebugeventhandler.h>

int main(int argc, char* argv[])
{
  PrintDebugEventHandler* handler = new PrintDebugEventHandler();
  CapnzeroDebugEventProxy proxy(handler);
  DebugMonitorClient client(proxy);
  client.start();

  while(true);
}
