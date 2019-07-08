//
// Created by sst on 24.06.19.
//

#ifndef LIBZMQMONITORING_SOCKETEVENTLISTENER_H
#define LIBZMQMONITORING_SOCKETEVENTLISTENER_H

#include <string>
#include <src/event/Event.h>
#include "monitor_config.h"
#include "EventProxy.h"
#include "RelayEventProxy.h"

class NetworkSocketEventListener
{
public:
  explicit NetworkSocketEventListener(EventProxy* proxy);

  ~NetworkSocketEventListener();

  void notify(const Event& event);

private:
  EventProxy* proxy;
};


#endif //LIBZMQMONITORING_SOCKETEVENTLISTENER_H
