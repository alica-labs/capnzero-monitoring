//
// Created by sst on 7/8/19.
//

#ifndef CAPNZEROMONITORINGLIB_EVENT_H
#define CAPNZEROMONITORINGLIB_EVENT_H


#include <string>

class Event
{
public:
  virtual ~Event() = default;

  virtual const std::string toYaml() const = 0;

  virtual void parse(const std::string& yamlSerializedEvent) = 0;

protected:
  std::string type;
};


#endif //CAPNZEROMONITORINGLIB_EVENT_H
