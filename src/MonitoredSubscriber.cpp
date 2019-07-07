//
// Created by sst on 24.06.19.
//


#include "MonitoredSubscriber.h"

MonitoredSubscriber::MonitoredSubscriber(void* zmqContext, const std::string& group) : subscriber(zmqContext, group),
                                                                                       eventListener(zmqContext)
{
  eventListener.notify("LOG: new subscriber on group " + group);
}

void MonitoredSubscriber::connect(capnzero::CommType commType, const std::string& address)
{
  subscriber.connect(commType, address);

  eventListener
  .notify("LOG: Subscriber connected to address " + address + " with communication type " + std::to_string(commType));
}

void MonitoredSubscriber::subscribe(void (* fun)(capnp::FlatArrayMessageReader&))
{
  subscriber.subscribe(fun);
  
  eventListener.notify("LOG: Subscriber subscribed");
}
