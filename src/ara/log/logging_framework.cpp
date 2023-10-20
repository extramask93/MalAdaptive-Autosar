#include <ara/log/log_stream.h>
#include <ara/log/logging_framework.h>
namespace ara {
namespace log {

LoggingFramework &LoggingFramework::GetFramework() {
  static LoggingFramework framework(std::make_unique<ConsoleSink>());
  return framework;
}
} // namespace log
} // namespace ara
