//
// Created by sst on 24.06.19.
//


#include <capnzero-base-msgs/string.capnp.h>
#include <capnzero/Common.h>
#include <capnp/message.h>

#include "NetworkSocketEventListener.h"


NetworkSocketEventListener::NetworkSocketEventListener(EventProxy* proxy) : proxy(proxy)
{}

NetworkSocketEventListener::~NetworkSocketEventListener()
{
  delete proxy;
}

void NetworkSocketEventListener::notify(const std::string& message)
{
  proxy->notifyClient(message);
}
