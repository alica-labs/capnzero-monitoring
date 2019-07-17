//
// Created by sst on 24.06.19.
//

#ifndef LIBZMQMONITORING_MONITOREDPUBLISHER_H
#define LIBZMQMONITORING_MONITOREDPUBLISHER_H

#include "NetworkSocketEventListener.h"

class MonitoredPublisher
{
public:
  explicit MonitoredPublisher(void* zmqContext);

  ~MonitoredPublisher();

  void bind(capnzero::CommType commType, const std::string& address);

  void send(const std::string& message, const std::string& groupName);

  void attachEventListener(EventListener* listener);

private:
  capnzero::Publisher publisher;
  EventListener* eventListener;
};


#endif //LIBZMQMONITORING_MONITOREDPUBLISHER_H
