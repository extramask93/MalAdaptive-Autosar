#pragma once
#include <ara/core/error_domain.h>
#include <ara/core/exception.h>
#include <cassert>
namespace ara {
namespace core {
/*****************************************/
/***************ErrorCodes****************/
/*****************************************/
enum class CoreErrc : ErrorDomain::CodeType
{
 kInvalidArgument= 22,
 kInvalidMetaModelShortname= 137,
 kInvalidMetaModelPath= 138,
};
/*****************************************/
/***************Exception*****************/
/*****************************************/
class CoreException : public Exception {
    public:
explicit CoreException (ErrorCode err) noexcept: Exception{err}{}
};
/*****************************************/
/*************Error domain****************/
/*****************************************/
class CoreErrorDomain final : public ErrorDomain {
public:
  using Errc = CoreErrc;
  using Exception = CoreException;
  constexpr CoreErrorDomain()noexcept: ErrorDomain(0x8000'0000'0000'0014){}
  constexpr virtual const char *Name() const noexcept override{
    return "Core";
  };
  constexpr virtual const char *Message(CodeType errorCode) const noexcept override {
    switch (static_cast<CoreErrc>(errorCode)) {
        case CoreErrc::kInvalidArgument:
        {
            return "Invalid argument given";
        }
        case CoreErrc::kInvalidMetaModelPath:
        {
            return "Invalid meta model path";
        }
        case CoreErrc::kInvalidMetaModelShortname:
        {
            return "Invalid meta mode short name";
        }
        default:
        {
            assert(!"Unknown error code");
            return "";
        }
    }
  }
  virtual void ThrowAsException(const ErrorCode &errorCode) const
      noexcept(false) override { throw CoreException{errorCode};};
};

/*****************************************/
/*************Free functions**************/
/*****************************************/
constexpr const ErrorDomain &GetCoreErrorDomain() noexcept {
    const static CoreErrorDomain domain{};
    return domain;
}
constexpr ErrorCode MakeErrorCode(CoreErrc code,
                                  ErrorDomain::SupportDataType data) noexcept {
    ErrorCode error_code(static_cast<ErrorDomain::CodeType>(code),GetCoreErrorDomain());
    return error_code;
}

} // namespace core
} // namespace ara
