#include "eventfactory.h"
#include <event/BindEvent.h>

#pragma once


class BindEventFactory : public EventFactory
{
public:
  BindEventFactory();

  const BindEvent* factorFromString(const std::string& serializedEvent) const override;
};

