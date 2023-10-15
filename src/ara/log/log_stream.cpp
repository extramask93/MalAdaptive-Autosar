#include <ara/log/log_stream.h>
#include <ara/log/logger.h>
#include <utility>

namespace ara {
namespace log {
  LogStream& LogStream::WithTag (core::StringView tag) noexcept {
      m_message.tags.emplace_back(tag);
      return *this;
  }
  LogStream& LogStream::WithLocation (core::StringView file, int line) noexcept {
      m_message.loc = std::make_pair(file, line);
      return *this;
  }
  void LogStream::Flush()noexcept{
      m_message.messageArgs = m_ss.str();
      m_logger->DoSink(m_message);
  }

}
} // namespace ara
