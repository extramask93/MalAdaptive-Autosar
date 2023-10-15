#pragma once
#include <cstdint>
#include <ostream>
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
std::ostream& operator<<(std::ostream &o, LogLevel lvl);
enum class ClientState : std::uint8_t {
    kUnknown,
    kNotConnected,
    kConnected,
};
}
} // namespace ara
