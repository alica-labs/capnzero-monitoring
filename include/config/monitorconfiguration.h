#pragma once

#include <string>

struct MonitorConfiguration
{
public:
  MonitorConfiguration();
  MonitorConfiguration(const std::string& address, const std::string& topic);

public:
  std::string address;
  std::string topic;
};

