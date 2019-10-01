#include <client/capnzerodebugeventproxy.h>
#include <capnzero-base-msgs/string.capnp.h>

#include <event/yamleventparser.h>

CapnzeroDebugEventProxy::CapnzeroDebugEventProxy(DebugEventHandler* handler, MonitorConfiguration config) :
  configuration(config), eventHandler(handler), subscriber(zmq_ctx_new(), capnzero::Protocol::UDP)
{
  subscriber.setTopic(configuration.topic);
  subscriber.addAddress(configuration.address);
}

CapnzeroDebugEventProxy::~CapnzeroDebugEventProxy()
{
  delete eventHandler;
}

void CapnzeroDebugEventProxy::startListening()
{
  subscriber.subscribe(&DebugEventHandler::handleDebugEvent, eventHandler);
}

void CapnzeroDebugEventProxy::stopListening()
{
  std::cout << "Not implemented in capnzero subscriber" << std::endl;
}
