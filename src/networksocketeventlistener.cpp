#include <capnzero-base-msgs/string.capnp.h>
#include <capnzero/Common.h>
#include <capnp/message.h>
#include <networksocketeventlistener.h>

NetworkSocketEventListener::NetworkSocketEventListener(EventProxy* proxy) : proxy(proxy)
{}

NetworkSocketEventListener::~NetworkSocketEventListener()
{
  delete proxy;
}

void NetworkSocketEventListener::notify(const Event& event)
{
  proxy->notifyClient(event);
}
