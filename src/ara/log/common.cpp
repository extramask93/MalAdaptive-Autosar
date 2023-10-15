#include <ara/log/common.h>

namespace ara {
namespace log {

std::ostream &operator<<(std::ostream &o, LogLevel lvl) {
  switch (lvl) {
  case LogLevel::kInfo: {
    o << "INFO";
    break;
  }
  case LogLevel::kWarn: {
    o << "WARN";
    break;
  }
  case LogLevel::kDebug: {
    o << "DEBUG";
    break;
  }
  case LogLevel::kFatal: {
    o << "FATAL";
    break;
  }
  case LogLevel::kOff: {
    o << "";
    break;
  }
  case LogLevel::kError: {
    o << "ERROR";
    break;
  }
  case LogLevel::kVerbose: {
    o << "VERBOSE";
    break;
  }
  }
  return o;
}
} // namespace log
} // namespace ara
