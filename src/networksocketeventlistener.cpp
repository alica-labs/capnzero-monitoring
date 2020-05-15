#include <networksocketeventlistener.h>

NetworkSocketEventListener::NetworkSocketEventListener(EventProxy *proxy) : proxy(proxy)
{
}

void NetworkSocketEventListener::notify(const Event &event)
{
  proxy->notifyClient(event);
}
