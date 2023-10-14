#pragma once
#include <ara/core/string_view.h>
#include <ara/log/common.h>
#include <ara/log/logging_framework.h>
#include <cstdint>
#include <sstream>
namespace ara {
namespace log {
template <typename T> class Argument final {};
class Sink;
class LogStream final {
private:
  LogLevel m_level;
  LoggingFramework *m_framework;
  std::stringstream m_ss;
public:
  LogStream(LogLevel level, LoggingFramework *framework) : m_level{level}, m_framework{framework} {}
  LogStream(const LogStream &other) = delete;
  LogStream(LogStream &&other) = default;
  LogStream& operator=(const LogStream &other) = delete;
  LogStream& operator=( LogStream &&other) = delete;
  ~LogStream() { Flush(); }
  void Flush() noexcept {
      m_framework->Sink(m_ss.str());
  }
  LogStream &operator<<(bool value) noexcept {
    m_ss << value;
    return *this;
  }
  LogStream &operator<<(std::uint8_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(std::uint16_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(std::uint32_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(std::uint64_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(std::int8_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(std::int16_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(std::int32_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(std::int64_t value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(float value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(double value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(const core::StringView value) noexcept {
    m_ss << value;
    return *this;
  }

  LogStream &operator<<(const char *value) noexcept {
    m_ss << value;
    return *this;
  }
};
} // namespace log
} // namespace ara
