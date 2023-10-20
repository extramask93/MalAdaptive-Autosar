#pragma once
#include <ara/log/sink/console_sink.h>
#include <ara/log/sink/dlt_sink.h>
#include <ara/log/sink/sink.h>
#include <memory>

namespace ara {
namespace log {
template <typename... Args>
std::unique_ptr<Sink> make_sink(SinkType type, Args &&...args) {
  switch (type) {
  case SinkType::kConsole: {
    return std::make_unique<ConsoleSink>(std::forward<Args>(args)...);
    break;
  }
  case SinkType::kDlt: {
    return std::make_unique<DltSink>(std::forward<Args>(args)...);
    break;
  }
  case SinkType::kFile: {
    throw std::runtime_error("File sink not supported");
    break;
  }
  }
  throw std::runtime_error("Unknown sink type");
}
} // namespace log
} // namespace ara
