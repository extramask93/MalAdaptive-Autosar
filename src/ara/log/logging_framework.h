#pragma once 
#include <vector>
#include <string>
#include <ara/log/common.h>
enum class SinkType {
    kConsole,
    kFile,
    kDlt,
};
struct Context {
    std::string contextId;
    std::string contextDescription;
    ara::log::LogLevel logLevel;
};
class LoggingFramework {
    public:
        LoggingFramework(std::string applicationID, LogLevel defaultLogSeverityLevel, SinkType sink) {
            //app id is supplied from manifest, it identifies application process
            //defult log severit level is set for every context, can be overriden for
            //each context
            //TODO register contexts against backend
        }
        //TODO crate example machine manifest containning ips of kDlt
        //
        //TODO create example execution manifest that contains log level and
        //category (sink)
        
        //TODO we should allow for remote change of log level
        //both application wide and per context
        ~LoggingFramework() {

            //Deregister contexts against backend
        }
    private:
        std::vector<Context> m_contexts;
};
