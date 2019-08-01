//
// Created by sst on 7/8/19.
//

#ifndef CAPNZEROMONITORINGLIB_GROUPJOINEVENT_H
#define CAPNZEROMONITORINGLIB_GROUPJOINEVENT_H


#include "Event.h"

class GroupJoinEvent : public Event
{
public:
  GroupJoinEvent();

  GroupJoinEvent(const std::string& groupName);

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string groupName;
};


#endif //CAPNZEROMONITORINGLIB_GROUPJOINEVENT_H
