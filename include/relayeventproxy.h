#pragma once

#include <capnzero/Publisher.h>
#include <event/Event.h>
#include <EventProxy.h>
#include <config/monitorconfiguration.h>

class RelayEventProxy : public EventProxy
{
public:
  RelayEventProxy(void* zmqContext, MonitorConfiguration monitorConfig = MonitorConfiguration());

  void notifyClient(const Event& event) override;

private:
  capnzero::Publisher publisher;
  MonitorConfiguration configuration;
};
