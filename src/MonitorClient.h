//
// Created by sst on 24.06.19.
//

#ifndef ZMQMONITORING_MONITORCLIENT_H
#define ZMQMONITORING_MONITORCLIENT_H

#include <capnzero/CapnZero.h>

class MonitorClient
{
public:
  MonitorClient(void* zmqContext, const std::string& monitoringAddress = "127.0.0.1:9876", const std::string& monitoringGroup = "monitoring");

  void start();

private:
  capnzero::Subscriber subscriber;
  std::string monitoringAddress;
  std::string monitoringGroup;
};


#endif //ZMQMONITORING_MONITORCLIENT_H
