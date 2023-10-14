#include <ara/log/logger.h>
#include <ara/log/sink/sink.h>
#include <ara/log/logging_framework.h>
#include <ara/log/log_stream.h>
#include <cassert>
namespace ara {
namespace log {

Logger &CreateLogger(ara::core::StringView ctxId,
                     ara::core::StringView ctxDescription,
                     LogLevel ctxDefLogLevel) noexcept {
    auto &framework = LoggingFramework::GetFramework();
    return framework.Register(ctxId,ctxDescription, ctxDefLogLevel);
}
Logger &CreateLogger(ara::core::StringView ctxId,
                     ara::core::StringView ctxDescription) noexcept {
    auto &framework = LoggingFramework::GetFramework();
    return framework.Register(ctxId,ctxDescription);
}
Logger &CreateLogger(const ara::core::InstanceSpecifier &is) noexcept {
    assert(!"Implement me");
}

  LogStream Logger::LogFatal() const noexcept {
      return WithLevel(LogLevel::kFatal);
  }
  LogStream LogError() const noexcept;
  LogStream LogWarn() const noexcept;
  LogStream LogInfo() const noexcept;
  LogStream LogDebug() const noexcept;
  LogStream LogVerbose() const noexcept;
  bool IsEnabled(LogLevel logLevel) const noexcept;
  LogStream WithLevel(LogLevel logLevel) const noexcept;
}
} // namespace ara
