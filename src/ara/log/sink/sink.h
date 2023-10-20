#pragma once
#include <ara/core/string_view.h>
#include <ara/log/common.h>
#include <iostream>
#include <memory>

namespace ara {
namespace log {

enum class SinkType {
  kConsole,
  kFile,
  kDlt,
};

class Sink {
public:
  virtual void RegisterContext(core::StringView ctxId, core::StringView &ctxDesc)  {
      (void)ctxId;
      (void)ctxDesc;
  }
  virtual void DoSink(const Message &message) = 0;
  virtual ~Sink() = default; //enable destroying derived by the Sink pointer
  protected:
  virtual std::string ToString(const Message &message);
};



} // namespace log
} // namespace ara
