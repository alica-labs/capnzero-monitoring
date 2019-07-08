//
// Created by sst on 7/8/19.
//

#ifndef CAPNZEROMONITORINGLIB_CONNECTEVENT_H
#define CAPNZEROMONITORINGLIB_CONNECTEVENT_H

#include <capnzero/Common.h>
#include "Event.h"

class ConnectEvent : public Event
{
public:
  ConnectEvent(const std::string& address, const capnzero::CommType commType);

  const std::string toYaml() const;

private:
  std::string address;
  capnzero::CommType commType;
};


#endif //CAPNZEROMONITORINGLIB_CONNECTEVENT_H
