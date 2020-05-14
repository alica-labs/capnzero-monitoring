#include <monitoredsubscriber.h>
#include <networksocketeventlistener.h>
#include <relayeventproxy.h>

void callback(capnp::FlatArrayMessageReader &reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << "subscriber received: " << message << std::endl;
}

int main(int argc, char *argv[])
{
  void *ctx = zmq_ctx_new();

  EventProxy *proxy = new RelayEventProxy(ctx);
  EventListener *eventListener = new NetworkSocketEventListener(proxy);
  MonitoredSubscriber subscriber("1", ctx, capnzero::Protocol::UDP);
  subscriber.attachEventListener(eventListener);
  subscriber.setTopic("a_topic");
  subscriber.addAddress("127.0.0.1:7890");
  subscriber.subscribe(&callback);

  while (true)
    ;
}
