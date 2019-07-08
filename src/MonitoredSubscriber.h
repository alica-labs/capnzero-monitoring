//
// Created by sst on 24.06.19.
//

#ifndef ZMQMONITORING_MONITOREDSUBSCRIBER_H
#define ZMQMONITORING_MONITOREDSUBSCRIBER_H


#include <capnp/serialize.h>
#include <capnzero/Subscriber.h>
#include "NetworkSocketEventListener.h"

class MonitoredSubscriber
{
public:
  MonitoredSubscriber(void* zmqContext, const std::string& group);

  void connect(capnzero::CommType commType, const std::string& address);

  void subscribe(void (* fun)(capnp::FlatArrayMessageReader&));

private:
  capnzero::Subscriber subscriber;
  NetworkSocketEventListener eventListener;
};


#endif //ZMQMONITORING_MONITOREDSUBSCRIBER_H
