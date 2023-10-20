#include <ara/core/core_error_domain.h>
#include <ara/core/error_code.h>
#include <ara/core/error_domain.h>
#include <ara/core/result.h>
#include <ara/log/logger.h>
#include <ara/log/log_stream.h>
#include <cstdlib>

int main(int argc, const char * argv[]) {
  ara::log::Logger &ctx0 =
      ara::log::CreateLogger("CTX0", "Context Description CTX0");
  ara::log::Logger &ctx1 =
      ara::log::CreateLogger("CTX1", "Context Description CTX1");
  ctx0.LogFatal() << std::string("Some log information") << 123;
  ara::log::LogStream localLogInfo = ctx1.LogFatal();
  localLogInfo << "Some log information" << 123;
  localLogInfo << "Some other information";
  localLogInfo.Flush();
  localLogInfo << "a new message..." << 456;
  return EXIT_SUCCESS;
}
