#include "eventfactory.h"

#include <event/SendEvent.h>

#pragma once


class SendEventFactory : public EventFactory
{
public:
  SendEventFactory();

  // EventFactory interface
public:
  const SendEvent* factorFromString(const std::string& serializedEvent) const;
};

