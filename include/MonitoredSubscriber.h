//
// Created by sst on 24.06.19.
//

#ifndef ZMQMONITORING_MONITOREDSUBSCRIBER_H
#define ZMQMONITORING_MONITOREDSUBSCRIBER_H


#include "EventListener.h"
#include "SimpleMonitoredCallback.h"

#include <capnp/serialize.h>
#include <capnzero/Subscriber.h>


class MonitoredSubscriber
{
public:
  MonitoredSubscriber(void* zmqContext, const std::string& group, EventListener* listener);

  ~MonitoredSubscriber();

  void connect(capnzero::CommType commType, const std::string& address);

  void subscribe(void (* fun)(capnp::FlatArrayMessageReader&));

  template <class CallbackObjType>
  void subscribe(void (CallbackObjType::*callbackFunction)(::capnp::FlatArrayMessageReader&), CallbackObjType* callbackObject);

private:
  capnzero::Subscriber subscriber;
  EventListener *eventListener;
  SimpleMonitoredCallback* messageCallback;
};


#endif //ZMQMONITORING_MONITOREDSUBSCRIBER_H
