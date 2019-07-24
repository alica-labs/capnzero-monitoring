//
// Created by sst on 24.06.19.
//


#include <capnzero-base-msgs/string.capnp.h>
#include <capnzero/Common.h>
#include <capnp/message.h>

#include "NetworkSocketEventListener.h"


NetworkSocketEventListener::NetworkSocketEventListener(EventProxy* proxy) : proxy(proxy)
{}

void NetworkSocketEventListener::notify(const Event& event)
{
  proxy->notifyClient(event);
}
