//
// Created by sst on 24.06.19.
//

#ifndef LIBZMQMONITORING_MONITOREDPUBLISHER_H
#define LIBZMQMONITORING_MONITOREDPUBLISHER_H

#include "NetworkSocketEventListener.h"

class MonitoredPublisher
{
public:
  MonitoredPublisher(void* zmqContext, const std::string& groupName);

  void bind(capnzero::CommType commType, const std::string& address);

  void send(const std::string& message);

private:
  capnzero::Publisher publisher;
  NetworkSocketEventListener eventListener;
};


#endif //LIBZMQMONITORING_MONITOREDPUBLISHER_H
