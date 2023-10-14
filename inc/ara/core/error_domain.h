#pragma once
#include <cstdint>

namespace ara {
namespace core {
class ErrorCode;
class ErrorDomain {
public:
  using IdType = std::uint64_t;
  using CodeType = std::int32_t;
  using SupportDataType = std::uint64_t;
  ErrorDomain(const ErrorDomain &) = delete;
  ErrorDomain(ErrorDomain &&) = delete;
  explicit constexpr ErrorDomain(IdType id) noexcept : m_id(id) {}
  ~ErrorDomain() noexcept = default;
  ErrorDomain &operator=(const ErrorDomain &) = delete;
  ErrorDomain &operator=(ErrorDomain &&) = delete;
  constexpr bool operator==(const ErrorDomain &other) const noexcept {
    return other.Id() == Id();
  }
  constexpr bool operator!=(const ErrorDomain &other) const noexcept {
    return !(*this == other);
  }
  constexpr IdType Id() const noexcept { return m_id; }
  virtual const char *Name() const noexcept = 0;
  virtual const char *Message(CodeType errorCode) const noexcept = 0;
  virtual void ThrowAsException(const ErrorCode &errorCode) const
      noexcept(false) = 0;
protected:
  IdType m_id;
};
} // namespace core
} // namespace ara
