#include <config/monitorconfiguration.h>

MonitorConfiguration::MonitorConfiguration() :
  address{"127.0.0.1:9876"}, topic{"monitoring"}
{}

MonitorConfiguration::MonitorConfiguration(const std::string& address, const std::string& topic):
  address(address), topic(topic)
{}
