//
// Created by sst on 7/8/19.
//

#ifndef CAPNZEROMONITORINGLIB_SENDEVENT_H
#define CAPNZEROMONITORINGLIB_SENDEVENT_H


#include "Event.h"

class SendEvent : public Event
{
public:
  SendEvent(const std::string& message, const std::string& groupName);

  const std::string toYaml() const override;

private:
  std::string message;
  std::string groupName;
};


#endif //CAPNZEROMONITORINGLIB_SENDEVENT_H
