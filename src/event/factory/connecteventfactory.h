#include "eventfactory.h"
#include <event/ConnectEvent.h>

#pragma once


class ConnectEventFactory : public EventFactory
{
public:
  ConnectEventFactory();

  // EventFactory interface
public:
  const ConnectEvent* factorFromString(const std::string& serializedEvent) const;
};

