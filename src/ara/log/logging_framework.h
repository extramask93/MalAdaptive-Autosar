#pragma once
#include <ara/log/common.h>
#include <ara/log/logger.h>
#include <ara/log/sink/sink.h>
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
namespace ara {
namespace log {

struct Context {
  std::string contextId;
  std::optional<std::string> contextDescription;
  std::optional<ara::log::LogLevel> logLevel;
};
class LoggingFramework {

public:
    using ContextIDType = std::string;
  static LoggingFramework& GetFramework();
  void DoSink( Message &message);
  Logger &Register(ara::core::StringView ctxId, ara::core::StringView ctxDesc) {
      return Register(ctxId, ctxDesc, m_defaultSeverityLevel);
  }
  Logger &Register(ara::core::StringView ctxId, ara::core::StringView ctxDesc,
                   ara::log::LogLevel level) {
    // Create a logger
    auto [it, new_insertion] = m_loggers.emplace(
        std::make_pair(ctxId, ara::log::Logger(ctxId, ctxDesc, level,*this)));
    if (!new_insertion) {
      // TODO fill description and level
    }
    return it->second;
  }
  // app id is supplied from manifest, it identifies application process
  // defult log severit level is set for every context, can be overriden for
  // each context
  // TODO register contexts against backend
  // TODO crate example machine manifest containning ips of kDlt
  //
  // TODO create example execution manifest that contains log level and
  // category (sink)

  // TODO we should allow for remote change of log level
  // both application wide and per context
  ~LoggingFramework() {
    // Deregister contexts against backend
  }
private:
  std::unordered_map<ContextIDType, ara::log::Logger> m_loggers;
  std::string m_applicationID;
  LogLevel m_defaultSeverityLevel;
  std::unique_ptr<Sink> m_sink;
  LoggingFramework(core::StringView applicationID = "#APID",
                   LogLevel defaultLogSeverityLevel = LogLevel::kWarn,
                   SinkType sink = SinkType::kConsole)
      : m_applicationID(applicationID),
        m_defaultSeverityLevel(defaultLogSeverityLevel),
        m_sink(Sink::CreateSink(sink)){

        };
};
} // namespace log
} // namespace ara
