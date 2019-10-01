#include <capnzero-base-msgs/string.capnp.h>
#include <client/printdebugeventhandler.h>
#include <iostream>

void PrintDebugEventHandler::handleDebugEvent(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();
  std::cout << message << std::endl;
}
