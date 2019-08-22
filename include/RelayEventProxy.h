#pragma once

#include <capnzero/Publisher.h>
#include <event/Event.h>
#include <EventProxy.h>

class RelayEventProxy : public EventProxy
{
public:
  explicit RelayEventProxy(void* zmqContext, const std::string& monitoringGroup = "monitoring", const std::string& monitoringAddress = "127.0.0.1:9876");

  void notifyClient(const Event& event) override;

private:
  capnzero::Publisher publisher;
  std::string monitoringGroup;
  std::string monitoringAddress;
};
