#include <monitoredpublisher.h>
#include <networksocketeventlistener.h>
#include <relayeventproxy.h>
#include <thread>

int main(int argc, const char *argv[])
{
  const std::string topic{"a_topic"};

  void *ctx = zmq_ctx_new();
  EventProxy *proxy = new RelayEventProxy(ctx);
  EventListener *eventListener = new NetworkSocketEventListener(proxy);
  MonitoredPublisher publisher("0", ctx, capnzero::Protocol::UDP);
  publisher.attachEventListener(eventListener);

  publisher.addAddress("127.0.0.1:7890");

  int counter = 0;
  std::string message;
  while (true)
  {
    message = "message" + std::to_string(counter++);

    std::cout << "sending message \"" << message << "\"" << std::endl;
    publisher.send(message, topic);

    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
}
