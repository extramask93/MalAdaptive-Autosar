#include <ara/core/error_code.h>
#include <exception>

namespace ara {
namespace core {
class Exception : public std::exception {
public:
  explicit Exception(ErrorCode err) noexcept : m_errorCode{err} {}
  /*Force compiler to create an implementation, cause we declare
   * virtual destructor*/
  Exception(Exception &&other) = default;
  Exception &operator=(Exception &&other) = default;
  virtual ~Exception() = default;
  const char *what() const noexcept override;
  const ErrorCode &Error() const noexcept { return m_errorCode;}
protected:
  /*Prevent accidental slicing*/
  Exception &operator=(const Exception &other) = default;
  Exception(const Exception &other) = default;
private:
  ErrorCode m_errorCode;
};
} // namespace core
} // namespace ara
