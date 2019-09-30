#include "eventfactory.h"

#pragma once


class AddressEventFactory : public EventFactory
{
public:
  AddressEventFactory() = default;

  // EventFactory interface
public:
  const Event* factorFromString(const std::string& serializedEvent) const;
};

