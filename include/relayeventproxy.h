#pragma once

#include <capnzero/Publisher.h>
#include <event/event.h>
#include <eventproxy.h>
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
