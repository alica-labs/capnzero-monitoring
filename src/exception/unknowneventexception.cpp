#include "unknowneventexception.h"

UnknownEventException::UnknownEventException(const std::string& reason): reason{reason}
{

}

const char* UnknownEventException::what() const noexcept
{
  return reason.c_str();
}
