#pragma once

#include <eventlistener.h>
#include <capnzero/Publisher.h>

class MonitoredPublisher
{
public:
  explicit MonitoredPublisher(const std::string &id, void *zmqContext, capnzero::Protocol protocol);

  void addAddress(const std::string &address);

  void attachEventListener(EventListener *listener);

  void setDefaultTopic(const std::string &topic);

  void send(const std::string &message);

  void send(const std::string &message, const std::string &topic);

private:
  capnzero::Publisher publisher;
  std::vector<EventListener *> eventListeners;
  std::string id;

  void notifyListeners(Event &event) const;
};
