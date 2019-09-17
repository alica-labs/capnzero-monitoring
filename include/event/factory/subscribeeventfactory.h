#include <event/factory/eventfactory.h>

#include <event/SubscribeEvent.h>

#pragma once


class SubscribeEventFactory : public EventFactory
{
public:
  SubscribeEventFactory() = default;

  // EventFactory interface
public:
  const SubscribeEvent* factorFromString(const std::string& serializedEvent) const;
};

