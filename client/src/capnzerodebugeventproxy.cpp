#include <capnzerodebugeventproxy.h>

#include <capnzero-base-msgs/string.capnp.h>

#include <event/yamleventparser.h>

CapnzeroDebugEventProxy::CapnzeroDebugEventProxy(MonitorConfiguration config) :
  configuration(config), eventHandler(nullptr), subscriber(zmq_ctx_new(), capnzero::Protocol::UDP)
{
  subscriber.setTopic(configuration.topic);
  subscriber.addAddress(configuration.address);
}

void CapnzeroDebugEventProxy::startListening()
{
  subscriber.subscribe(&CapnzeroDebugEventProxy::capnzeroCallback, this);
}

void CapnzeroDebugEventProxy::stopListening()
{
  std::cout << "Not implemented in capnzero subscriber" << std::endl;
}

void CapnzeroDebugEventProxy::addEventHandler(DebugEventHandler* eventHandler)
{
  this->eventHandler = eventHandler;
}

void CapnzeroDebugEventProxy::notify(const Event* event)
{
  eventHandler->handleDebugEvent(event);
}

void CapnzeroDebugEventProxy::capnzeroCallback(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  YamlEventParser parser;
  const Event* event = parser.parse(message);

  this->notify(event);
}
