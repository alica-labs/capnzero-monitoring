//
// Created by sst on 24.06.19.
//

#ifndef ZMQMONITORING_MONITORCLIENT_H
#define ZMQMONITORING_MONITORCLIENT_H

#include "monitor_config.h"
#include <CapnZero.h>

class MonitorClient
{
public:
  MonitorClient(void* zmqContext);

  void start();

private:
  capnzero::Subscriber subscriber;
};


#endif //ZMQMONITORING_MONITORCLIENT_H
