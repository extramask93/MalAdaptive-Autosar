#pragma once
#include <ara/core/error_domain.h>
#include <functional>
#include <type_traits>
#include <stdexcept>
#include <ara/core/string_view.h>

namespace ara {
namespace core {
class ErrorCode final {
    public:
    /* No idea how to support a constructor w/o specifying ErrorDomain
     * Maybe create a concrete class like NoDomain and make it default to that?
     * UPDATE
     * Ok, got it now. Each new domain shall define a MakeErrorCode free function
     * in it's namespace. The template would be instantiated, and due to not erased
     * type of EnumT and ADL it would find the MakeErrorCode in a EnumT namespace*/
    template<typename EnumT>
        requires std::is_enum_v<EnumT> && 
        std::copyable<EnumT>
    constexpr ErrorCode (EnumT e, ErrorDomain::SupportDataType data =
                ErrorDomain::SupportDataType{}) noexcept {
        *this = MakeErrorCode(e, data);
    }
    constexpr ErrorCode(ErrorDomain::CodeType value, const ErrorDomain &domain,
            ErrorDomain::SupportDataType data = ErrorDomain::SupportDataType{})
        noexcept : m_value(value), m_support(data), m_domain(domain){}
    constexpr ErrorDomain::CodeType Value() const noexcept {return m_value;}
    constexpr const ErrorDomain& Domain() const noexcept {return m_domain;}
    constexpr ErrorDomain::SupportDataType SupportData() const noexcept  {return m_support;}
    StringView Message() const noexcept {return m_domain.get().Message(m_value);}
    void ThrowAsException() const {
        throw std::runtime_error{std::string(Message())};
    }
private:
    ErrorDomain::CodeType m_value;
    ErrorDomain::SupportDataType m_support;
    std::reference_wrapper<const ErrorDomain> m_domain;

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
