//
// Created by sst on 24.06.19.
//

#ifndef LIBZMQMONITORING_SOCKETEVENTLISTENER_H
#define LIBZMQMONITORING_SOCKETEVENTLISTENER_H

#include <string>
#include <event/Event.h>
#include "EventListener.h"
#include "EventProxy.h"
#include "RelayEventProxy.h"

class NetworkSocketEventListener : public EventListener
{
public:
  explicit NetworkSocketEventListener(EventProxy* proxy);

  ~NetworkSocketEventListener();

  void notify(const Event& event) override;

private:
  EventProxy* proxy;
};


#endif //LIBZMQMONITORING_SOCKETEVENTLISTENER_H
