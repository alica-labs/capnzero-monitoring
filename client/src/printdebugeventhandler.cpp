#include <printdebugeventhandler.h>
#include <iostream>

void PrintDebugEventHandler::handleDebugEvent(const Event* event)
{
  std::cout << event->toYaml() << std::endl;
}
