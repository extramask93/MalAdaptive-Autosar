#pragma once
#include <ara/core/error_domain.h>
#include <ara/core/exception.h>
namespace ara {
namespace core {
enum class CoreErrc : ErrorDomain::CodeType
{
 kInvalidArgument= 22,
 kInvalidMetaModelShortname= 137,
 kInvalidMetaModelPath= 138,
};
class CoreException : public Exception {
    public:
explicit CoreException (ErrorCode err) noexcept: Exception{err}{}
};

class CoreErrorDomain final : public ErrorDomain {
public:
  using Errc = CoreErrc;
  using Exception = CoreException;
  constexpr CoreErrorDomain()noexcept: ErrorDomain(0x8000'0000'0000'0014){}
  virtual const char *Name() const noexcept override{ return "todo";};
  virtual const char *Message(CodeType errorCode) const noexcept override {return "todo";}
  virtual void ThrowAsException(const ErrorCode &errorCode) const
      noexcept(false) override { throw CoreException{errorCode};};
};
constexpr const ErrorDomain &GetCoreErrorDomain() noexcept;
constexpr ErrorCode MakeErrorCode(CoreErrc code, ErrorDomain::SupportDataType data) noexcept;

} // namespace core
} // namespace ara
