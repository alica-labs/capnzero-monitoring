//
// Created by sst on 24.06.19.
//

#ifndef ZMQMONITORING_MONITORCLIENT_H
#define ZMQMONITORING_MONITORCLIENT_H

#include <capnzero/CapnZero.h>
#include <event/Event.h>
#include <event/yamleventparser.h>

class MonitorClient
{
public:
  MonitorClient(void* zmqContext, const std::string& monitoringAddress = "127.0.0.1:9876", const std::string& monitoringGroup = "monitoring");

  ~MonitorClient();

  void start();

  const std::vector<const Event*> getEvents() const;

  void appendEvent(::capnp::FlatArrayMessageReader& reader);

private:
  capnzero::Subscriber subscriber;
  std::string monitoringAddress;
  std::string monitoringGroup;
  std::vector<const Event*> events;
  YamlEventParser yamlEventParser;
};


#endif //ZMQMONITORING_MONITORCLIENT_H
