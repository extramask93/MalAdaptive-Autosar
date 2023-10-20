#pragma once
#include <ara/log/sink/sink.h>
#include <unordered_map>
#include <dlt.h>
#include <dlt_types.h>
#include <dlt_user.h>
namespace ara {
namespace log {
class DltSink : public Sink {
public:
  explicit DltSink(core::StringView appid, core::StringView appdesc) {
      DLT_REGISTER_APP(appid.data(),appdesc.data());
      DLT_VERBOSE_MODE();
  }

  void RegisterContext(core::StringView ctxId, core::StringView &ctxDesc) override {
      if(m_contexts.find(ctxId.data()) == m_contexts.end()) {
      m_contexts[std::string(ctxId)] = DltContext {};
      DLT_REGISTER_CONTEXT(m_contexts[ctxId.data()],ctxId.data(),ctxDesc.data());
      }
  }
  virtual void DoSink(const Message &message) override {
      DLT_LOG(m_contexts[std::string(message.ctxId)],(DltLogLevelType)message.level, DLT_STRING(message.messageArgs.data()));
  }
  virtual ~DltSink() override{
      for(auto & c : m_contexts) {
          DLT_UNREGISTER_CONTEXT(c.second);
      }
      DLT_UNREGISTER_APP();
  }
private:
  std::unordered_map<std::string,DltContext> m_contexts;
};
} // namespace log
} // namespace ara
