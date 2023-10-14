#include <ara/log/sink/sink.h>
namespace ara {
namespace log {
namespace sink {
std::unique_ptr<Sink> Sink::CreateSink(SinkType sink) {
    return std::make_unique<ConsoleSink>();
}
} // namespace sink
} // namespace log
} // namespace ara
