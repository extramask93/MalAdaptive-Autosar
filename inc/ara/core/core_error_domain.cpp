#include <ara/core/core_error_domain.h>

namespace ara {
namespace core {
const static CoreErrorDomain domain{};
constexpr const ErrorDomain &GetCoreErrorDomain() noexcept {
    return domain;
}
constexpr ErrorCode MakeErrorCode(CoreErrc code,
                                  ErrorDomain::SupportDataType data) noexcept {
    ErrorCode error_code(static_cast<ErrorDomain::CodeType>(code),GetCoreErrorDomain());
    return error_code;
}
} // namespace core
} // namespace ara
