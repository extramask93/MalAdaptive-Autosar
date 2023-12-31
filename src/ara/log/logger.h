#pragma once
#include <ara/core/intance_specifier.h>
#include <ara/core/string_view.h>
#include <ara/log/sink/sink.h>
#include <ara/log/common.h>
#include <cstdint>
namespace ara {
namespace log {
class Message;
class Logger;
class LogStream;
class LoggingFramework;

template <typename T> class Argument;
enum class Fmt : std::uint16_t {
  kDefault,
  kDec,
  kOct,
  kHex,
  kBin,
  kDecFloat,
  kEngFloat,
  kHexFloat,
  kAutoFloat,
};

struct Format final {
  Fmt fmt;
  std::uint16_t precision;
};
constexpr Format Dflt() noexcept { return Format{.fmt = Fmt::kDefault}; }
constexpr Format Dec() noexcept { return Format{.fmt = Fmt::kDec}; }
constexpr Format Dec(std::uint16_t precision) noexcept {
  return Format{.fmt = Fmt::kDec, .precision = precision};
}
constexpr Format Oct() noexcept { return Format{.fmt = Fmt::kOct}; }
constexpr Format Oct(std::uint16_t precision) noexcept {
  return Format{.fmt = Fmt::kOct, .precision = precision};
}
constexpr Format Hex() noexcept { return Format{.fmt = Fmt::kHex}; }
constexpr Format Hex(std::uint16_t precision) noexcept {
  return Format{.fmt = Fmt::kHex, .precision = precision};
}
constexpr Format Bin() noexcept { return Format{.fmt = Fmt::kBin}; }
constexpr Format Bin(std::uint16_t precision) noexcept {
  return Format{.fmt = Fmt::kBin, .precision = precision};
}
constexpr Format DecFloat(std::uint16_t precision = 6) noexcept {
  return Format{.fmt = Fmt::kDecFloat, .precision = precision};
}
constexpr Format DecFloatMax() noexcept {
  return Format{.fmt = Fmt::kDecFloat, .precision = 17};
}
constexpr Format EngFloat(std::uint16_t precision = 6) noexcept {
  return Format{.fmt = Fmt::kEngFloat, .precision = precision};
}
constexpr Format EngFloatMax() noexcept {
  return Format{.fmt = Fmt::kEngFloat, .precision = 17};
}
constexpr Format HexFloat(std::uint16_t precision = 6) noexcept {
  return Format{.fmt = Fmt::kHexFloat, .precision = precision};
}
constexpr Format HexFloatMax() noexcept {
  return Format{.fmt = Fmt::kHexFloat, .precision = 17};
}
constexpr Format AutoFloat(std::uint16_t precision = 6) noexcept {
  return Format{.fmt = Fmt::kAutoFloat, .precision = precision};
}
constexpr Format AutoFloatMax() noexcept {
  return Format{.fmt = Fmt::kAutoFloat, .precision = 17};
}
Logger &CreateLogger(ara::core::StringView ctxId,
                     ara::core::StringView ctxDescription,
                     LogLevel ctxDefLogLevel) noexcept;
Logger &CreateLogger(ara::core::StringView ctxId,
                     ara::core::StringView ctxDescription) noexcept;
Logger &CreateLogger(const ara::core::InstanceSpecifier &is) noexcept;

void RegisterConnectionStateHandler(
    std::function<void(ClientState)> callback) noexcept;

  template <typename T> struct asserter : std::false_type {};
template <typename T>
Argument<T> Arg(T &&arg, const char *name = nullptr, const char *unit = nullptr,
                Format fmt = Dflt()) noexcept {}
class Logger {
private:
  std::string m_ctxId;
  std::string m_ctxDescription;
  LogLevel m_logLevel;
  Sink &m_sink;

public:
  void DoSink(Message &message) const noexcept;
  Logger(core::StringView ctxId, core::StringView ctxDesc, LogLevel lvl,
         Sink &sink)
      : m_ctxId{ctxId}, m_ctxDescription{ctxDesc}, m_logLevel{lvl},
        m_sink{sink} {}
  LogStream LogFatal() const noexcept;
  LogStream LogError() const noexcept;
  LogStream LogWarn() const noexcept;
  LogStream LogInfo() const noexcept;
  LogStream LogDebug() const noexcept;
  LogStream LogVerbose() const noexcept;
  bool IsEnabled(LogLevel logLevel) const noexcept;
  LogStream WithLevel(LogLevel logLevel) const noexcept;
  template <typename MsgId, typename... Params>
  void Log(const MsgId &id, const Params &...args) noexcept {
    static_assert(asserter<MsgId>::value, "Non verbose messages not supported");
  }
  template <typename... Attrs, typename MsgId, typename... Params>
  void LogWith(const std::tuple<Attrs...> &attrs, const MsgId &id,
               const Params &...params) noexcept {
    static_assert(asserter<MsgId>::value, "Non verbose messages not supported");
  }
  void SetThreshold(LogLevel threshold) noexcept;
};
} // namespace log
} // namespace ara
