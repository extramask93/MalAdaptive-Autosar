#include <ara/log/logger.h>
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
  LogStream Logger::LogError() const noexcept{
      return WithLevel(LogLevel::kError);
  }

  LogStream Logger::LogWarn() const noexcept{
      return WithLevel(LogLevel::kWarn);
  }

  LogStream Logger::LogInfo() const noexcept{
      return WithLevel(LogLevel::kInfo);
  }

  LogStream Logger::LogDebug() const noexcept{
      return WithLevel(LogLevel::kDebug);
  }

  LogStream Logger::LogVerbose() const noexcept{
      return WithLevel(LogLevel::kVerbose);
  }

  bool Logger::IsEnabled(LogLevel logLevel) const noexcept {
      if(static_cast<uint8_t>(logLevel) <= static_cast<uint8_t>(m_logLevel)) {
          return true;
      }
      return false;
  }
  LogStream Logger::WithLevel(LogLevel logLevel) const noexcept {
      LogStream stream(logLevel, this);
      return stream;
  }
  void Logger::DoSink( Message &message) const noexcept {
      if(IsEnabled(message.level)) {
              message.ctxId = m_ctxId;
              m_framework.DoSink(message);
      }
  }
}
} // namespace ara
