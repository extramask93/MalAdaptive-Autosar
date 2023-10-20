#pragma once
#include <ara/log/sink/sink.h>
namespace ara {
namespace log {
class ConsoleSink : public Sink {
public:
  virtual void DoSink(const Message &message) override;
};
} // namespace log
} // namespace ara
