//
// Created by sst on 24.06.19.
//

#ifndef ZMQMONITORING_MONITOREDSUBSCRIBER_H
#define ZMQMONITORING_MONITOREDSUBSCRIBER_H


#include "EventListener.h"

#include <capnp/serialize.h>
#include <capnzero/Subscriber.h>


class MonitoredSubscriber
{
public:
  MonitoredSubscriber(void* zmqContext, const std::string& group);

  void attachEventListener(EventListener *eventListener);

  void connect(capnzero::CommType commType, const std::string& address);

  void subscribe(void (* fun)(capnp::FlatArrayMessageReader&));

private:
  capnzero::Subscriber subscriber;
  EventListener *eventListener;
};


#endif //ZMQMONITORING_MONITOREDSUBSCRIBER_H
