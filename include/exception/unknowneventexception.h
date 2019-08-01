#include <exception>
#include <string>

#pragma once

class UnknownEventException : public std::exception
{
public:
  explicit UnknownEventException(const std::string& reason);

  const char* what() const noexcept override;

private:
  std::string reason;
};

