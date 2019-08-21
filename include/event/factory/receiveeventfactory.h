#include "eventfactory.h"

#include <event/ReceiveEvent.h>

#pragma once


class ReceiveEventFactory : public EventFactory
{
public:
  ReceiveEventFactory();

  // EventFactory interface
public:
  const ReceiveEvent* factorFromString(const std::string& serializedEvent) const;
};

