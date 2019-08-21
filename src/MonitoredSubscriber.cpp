//
// Created by sst on 24.06.19.
//


#include <capnzero-base-msgs/string.capnp.h>
#include "MonitoredCallback.h"
#include "MonitoredSubscriber.h"
#include "RelayEventProxy.h"
#include "event/GroupJoinEvent.h"
#include "event/ConnectEvent.h"
#include "event/SubscribeEvent.h"

MonitoredSubscriber::MonitoredSubscriber(void* zmqContext, const std::string& group, EventListener* listener) :
  subscriber(zmqContext, group), eventListener(listener)
{
  GroupJoinEvent event(group);
  eventListener->notify(event);
}

MonitoredSubscriber::~MonitoredSubscriber()
{
  delete messageCallback;
  delete eventListener;
}

void MonitoredSubscriber::connect(capnzero::CommType commType, const std::string& address)
{
  subscriber.connect(commType, address);

  ConnectEvent event(address, commType);
  eventListener->notify(event);
}

void MonitoredSubscriber::subscribe(void (* callback)(capnp::FlatArrayMessageReader&))
{
  messageCallback = new MonitoredCallback(eventListener, callback);

  SubscribeEvent event;
  eventListener->notify(event);

  subscriber.subscribe(&MonitoredCallback::monitoredCallback, messageCallback);
}

template<class CallbackObjType>
void MonitoredSubscriber::subscribe(void (CallbackObjType::*callbackFunction)(capnp::FlatArrayMessageReader&), CallbackObjType* callbackObject)
{
  /*
    Unterscheidung in SimpleMonitoredCallback und ComplexMonitoredCallback, per Interface MonitoredCallback einbinden
    ComplexMonitoredCallback (notwendigerweise Template, da Objekttyp beliebig) erhält aufzurufende Funktion, Objekt und EventListener
    monitoredCallback-Methode des ComplexMonitoredCallback ruft übergebene Funktion auf übergebenem Objekt auf
   */

  SubscribeEvent event;
  eventListener->notify(event);

  subscriber.subscribe(&MonitoredCallback::monitoredCallback, messageCallback);
}
