#include <event/Event.h>
#include <event/yamleventparser.h>
#include <MonitorClient.h>

#pragma once

extern "C"
{
  void start_monitoring(const char* monitoring_address, const char* monitoring_topic)
  {
    MonitorConfiguration config(monitoring_address, monitoring_topic);
    MonitorClient client(zmq_ctx_new(), new YamlEventParser(), config);

    client.start();
  }

  void stop_monitoring()
  {

  }

  Event* get_next_event()
  {

  }
}
