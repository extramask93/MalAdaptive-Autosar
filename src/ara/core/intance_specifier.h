#include <ara/core/result.h>
#include <ara/core/string_view.h>

namespace ara {
namespace core {
class InstanceSpecifier final {
public:
  static Result<InstanceSpecifier>
  Create(StringView metaModelIdentifier);
  explicit InstanceSpecifier(StringView metaModelIdentifier);
  InstanceSpecifier(const InstanceSpecifier &other);
  InstanceSpecifier(InstanceSpecifier &&other) noexcept;
  InstanceSpecifier &operator=(const InstanceSpecifier &other);
  InstanceSpecifier &operator=(InstanceSpecifier &&other);
  ~InstanceSpecifier() noexcept;
  StringView ToString() const noexcept;
  bool operator==(const InstanceSpecifier &other) const noexcept;
  bool operator==(StringView other) const noexcept;
  bool operator!=(const InstanceSpecifier &other) const noexcept;
  bool operator!=(StringView other) const noexcept;
  bool operator<(const InstanceSpecifier &other) const noexcept;
};
} // namespace com
} // namespace ara
