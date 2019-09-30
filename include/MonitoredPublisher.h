#pragma once

#include <EventListener.h>
#include <capnzero/Publisher.h>

class MonitoredPublisher
{
public:
  explicit MonitoredPublisher(void* zmqContext, capnzero::Protocol protocol, EventListener* listener);

  ~MonitoredPublisher();

  void addAddress(const std::string& address);

  void send(const std::string& message, const std::string& groupName);

private:
  capnzero::Publisher publisher;
  EventListener* eventListener;
};
