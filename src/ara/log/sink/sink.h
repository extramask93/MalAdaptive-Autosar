#pragma once
#include <ara/core/string_view.h>
#include <iostream>
#include <memory>

namespace ara {
namespace log {
class Message;
enum class SinkType {
  kConsole,
  kFile,
  kDlt,
};
class Sink {
public:
  virtual void DoSink(const Message &message) = 0;
  virtual std::string ToString(const Message &message);
  static std::unique_ptr<Sink> CreateSink(SinkType sink);
};
class ConsoleSink : public Sink {
public:
  virtual void DoSink(const Message &message) override;
};
class FileSink {};

} // namespace log
} // namespace ara
