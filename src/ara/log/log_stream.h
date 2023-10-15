#pragma once
#include <ara/core/string_view.h>
#include <ara/log/common.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
namespace ara {
namespace log {
class Logger;
struct Message {
    std::uint8_t privacy;
    LogLevel level;
    std::optional<size_t> timestamp;
    std::pair<std::string, int> loc;
    std::vector<std::string> tags;
    std::string ctxId;
    std::string appId;
    std::string messageArgs;
};

template <typename T> class Argument final {};
class LogStream final {
private:
  const Logger * const m_logger;
  std::stringstream m_ss;
  Message m_message;
public:
  LogStream(LogLevel level, const Logger * const logger) : m_logger{logger} {
      m_message.level = level;
  }
  LogStream(const LogStream &other) = delete;
  LogStream(LogStream &&other) = default;
  LogStream& operator=(const LogStream &other) = delete;
  LogStream& operator=( LogStream &&other) = delete;
  LogStream& WithTag (core::StringView tag) noexcept;
  LogStream& WithLocation (core::StringView file, int line) noexcept;
  template <typename T>
  LogStream& WithPrivacy (T value) noexcept {
      m_message.privacy = static_cast<uint8_t>(value & 0xFF); 
      return *this;
  }
  ~LogStream() { Flush(); }
  void Flush() noexcept;
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
