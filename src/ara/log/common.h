#pragma once
#include <cstdint>
namespace ara {
namespace log {
enum class LogLevel : std::uint8_t {
  kOff = 0x0,
  kFatal,
  kError,
  kWarn,
  kInfo,
  kDebug,
  kVerbose,
};
enum class ClientState : std::uint8_t {
    kUnknown,
    kNotConnected,
    kConnected,
};
}
} // namespace ara
