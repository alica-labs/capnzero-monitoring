#pragma once

class DebugEventProxy
{
public:
  virtual ~DebugEventProxy() = default;

  virtual void startListening() = 0;

  virtual void stopListening() = 0;
};

