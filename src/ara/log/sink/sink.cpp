#include <ara/log/log_stream.h>
#include <ara/log/sink/sink.h>
#include <sstream>
namespace ara {
namespace log {
std::unique_ptr<Sink> Sink::CreateSink(SinkType sink) {
  return std::make_unique<ConsoleSink>();
}
std::string Sink::ToString(const Message &message) {
  std::ostringstream ss;
  if (message.timestamp.has_value()) {
    ss << "[" << message.timestamp.value() << "]";
  }
  ss << "[" << message.level << "]";
  for (const auto &tag : message.tags) {
    ss << "[" << tag << "]";
  }
  ss << "[" << message.appId << "]";
  ss << "[" << message.ctxId << "]";
  ss << message.messageArgs;
  return ss.str();
}
void ConsoleSink::DoSink(const Message &message) {
  std::cout << ToString(message);
}
} // namespace log
} // namespace ara
