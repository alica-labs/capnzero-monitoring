//
// Created by sst on 7/8/19.
//

#ifndef CAPNZEROMONITORINGLIB_BINDEVENT_H
#define CAPNZEROMONITORINGLIB_BINDEVENT_H


#include <capnzero/Common.h>
#include "Event.h"

class BindEvent : public Event
{
public:
  BindEvent(const std::string& address, capnzero::CommType commType);

  const std::string toYaml() const override;

private:
  std::string address;
  capnzero::CommType commType;
};


#endif //CAPNZEROMONITORINGLIB_BINDEVENT_H
