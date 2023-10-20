#include <ara/log/sink/console_sink.h>
namespace ara {
namespace log {
void ConsoleSink::DoSink(const Message &message) {
  std::cout << ToString(message) << "\n";
}
} // namespace log
} // namespace ara
