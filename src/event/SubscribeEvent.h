//
// Created by sst on 7/8/19.
//

#ifndef CAPNZEROMONITORINGLIB_SUBSCRIBEEVENT_H
#define CAPNZEROMONITORINGLIB_SUBSCRIBEEVENT_H


#include <src/event/Event.h>

class SubscribeEvent : public Event
{
public:
  SubscribeEvent();

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;
};


#endif //CAPNZEROMONITORINGLIB_SUBSCRIBEEVENT_H
