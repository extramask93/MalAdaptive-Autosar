
#pragma once
#include <ara/core/error_domain.h>
#include <ara/core/exception.h>
namespace ara {
namespace core {
/*****************************************/
/***************ErrorCodes****************/
/*****************************************/
enum class future_errc : ErrorDomain::CodeType
{
};
/*****************************************/
/***************Exception*****************/
/*****************************************/
class FutureException : public Exception {
    public:
explicit FutureException (ErrorCode err) noexcept: Exception{err}{}
};
/*****************************************/
/*************Error domain****************/
/*****************************************/
class FutureErrorDomain final : public ErrorDomain {
public:
  using Errc = future_errc;
  using Exception = FutureException;
  constexpr FutureErrorDomain()noexcept: ErrorDomain(0x8000'0000'0000'0014){}
  constexpr virtual const char *Name() const noexcept override{
    return "Core";
  };
  constexpr virtual const char *Message(CodeType errorCode) const noexcept override {
    return "todo";
  }
  virtual void ThrowAsException(const ErrorCode &errorCode) const
      noexcept(false) override { throw FutureException{errorCode};};
};

/*****************************************/
/*************Free functions**************/
/*****************************************/
constexpr const ErrorDomain &GetFutureErrorDomain() noexcept {
    const static FutureErrorDomain domain{};
    return domain;
}
constexpr ErrorCode MakeErrorCode(future_errc code,
                                  ErrorDomain::SupportDataType data) noexcept {
    ErrorCode error_code(static_cast<ErrorDomain::CodeType>(code),GetFutureErrorDomain());
    return error_code;
}

} // namespace core
} // namespace ara
