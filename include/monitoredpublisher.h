#pragma once

#include <eventlistener.h>
#include <capnzero/Publisher.h>

class MonitoredPublisher
{
public:
  explicit MonitoredPublisher(const std::string& id, void* zmqContext, capnzero::Protocol protocol, EventListener* listener);

  ~MonitoredPublisher();

  void addAddress(const std::string& address);

  void send(const std::string& message, const std::string& topic);

private:
  capnzero::Publisher publisher;
  EventListener* eventListener;
  std::string id;
};
