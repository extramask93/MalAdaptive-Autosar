#include <ara/log/log_stream.h>
#include <ara/log/logging_framework.h>
namespace ara {
namespace log {

void LoggingFramework::DoSink(Message &message) {
  message.appId = m_applicationID;
  m_sink->DoSink(message);
}
LoggingFramework &LoggingFramework::GetFramework() {
  static LoggingFramework framework;
  return framework;
}
} // namespace log
} // namespace ara
