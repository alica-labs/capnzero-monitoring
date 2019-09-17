#pragma once

#include <event/factory/eventfactory.h>
#include <event/BindEvent.h>

class BindEventFactory : public EventFactory
{
public:
  BindEventFactory() = default;

  const BindEvent* factorFromString(const std::string& serializedEvent) const override;
};

