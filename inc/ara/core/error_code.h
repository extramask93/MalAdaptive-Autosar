#pragma once
#include <ara/core/error_domain.h>
#include <type_traits>
#include <ara/core/string_view.h>

namespace ara {
namespace core {
class ErrorCode final {
    public:
    template<typename EnumT> requires std::is_enum_v<EnumT>
    constexpr ErrorCode (EnumT e, ErrorDomain::SupportDataType data =
                ErrorDomain::SupportDataType{}) noexcept;
    constexpr ErrorCode(ErrorDomain::CodeType value, const ErrorDomain &domain,
            ErrorDomain::SupportDataType data = ErrorDomain::SupportDataType{})
        noexcept;
    constexpr ErrorDomain::CodeType Value() const noexcept;
    constexpr const ErrorDomain& Domain() const noexcept;
    constexpr ErrorDomain::SupportDataType SupportData() const noexcept;
    StringView Message() const noexcept;
    void ThrowAsException() const;

};
constexpr bool operator==(const ErrorCode& lhs, const ErrorCode &rhs) noexcept
{
    return (lhs.Value() == rhs.Value()) && (lhs.Domain() == rhs.Domain());
}
constexpr bool operator!=(const ErrorCode& lhs, const ErrorCode &rhs) noexcept {
    return !(lhs == rhs);
}
} // namespace core
} // namespace ara
