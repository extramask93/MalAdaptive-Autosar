#pragma once
#include <cstdint>
#include <ostream>
#include <optional>
#include <vector>
#include <ara/core/string_view.h>
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
struct Context {
    std::string ctxId;
    std::string ctxDesc;
};
struct Message {
    std::uint8_t privacy;
    LogLevel level;
    std::optional<size_t> timestamp;
    std::pair<std::string, int> loc;
    std::vector<std::string> tags;
    std::string ctxId;
    std::string messageArgs;
};
}
} // namespace ara
