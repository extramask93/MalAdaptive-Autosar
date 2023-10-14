#pragma once
#include <ara/core/string_view.h>
#include <iostream>
#include <memory>

namespace ara {
namespace log {
namespace sink {

enum class SinkType {
  kConsole,
  kFile,
  kDlt,
};
class Sink {
public:
  virtual void sink(core::StringView message) = 0;
  static std::unique_ptr<Sink> CreateSink(SinkType sink);
};
class ConsoleSink: public Sink {
    public:
        virtual void sink(core::StringView message) override {
            std::cout<<message;
        }
};
class FileSink {};
class DltSink {};

} // namespace sink
} // namespace log
} // namespace ara
