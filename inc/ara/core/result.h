#include <ara/core/error_code.h>
#include <ara/core/optional.h>
#include <type_traits>
#include <functional>

namespace ara {
namespace core {
/*TODO move this to utils
 * taken from https://open-std.org/JTC1/SC22/WG21/docs/papers/2020/p2098r1.pdf
 * */
template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};
template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref>: std::true_type {};

template <typename T, typename E = ErrorCode> class Result final {
public:
  using value_type = T;
  using error_type = E;
  Result() = delete;
  Result(const T &t) : m_value{t} {}
  Result(T &&t) : m_value{std::move(t)} {}
  explicit Result(const E &e) : m_error{e} {}
  explicit Result(E &&e) : m_error{std::move(e)} {};
  Result(const Result &other) = default;
  Result(Result &&other) noexcept(
      std::is_nothrow_move_constructible<T>::value
          &&std::is_nothrow_move_constructible<E>::value) = default;
  ~Result() noexcept = default;
  static Result FromValue(const T &t) { return Result{t}; }
  static Result FromValue(T &&t) { return Result{std::move(t)}; }
  template <typename... Args> static Result FromValue(Args &&...args) {
    T value = T{args...};
    return Result{value};
  }

  static Result FromError(const E &e) { return Result{e}; }
  static Result FromError(E &&e) { return Result{std::move(e)}; }
  template <typename... Args> static Result FromError(Args &&...args) {
    E error = E{args...};
    return Result{error};
  }
  Result &operator=(const Result &other) = default;
  Result &operator=(Result &&other) noexcept(
      std::is_nothrow_move_constructible_v<T>
          &&std::is_nothrow_move_assignable_v<T>
              &&std::is_nothrow_move_constructible_v<E>
                  &&std::is_nothrow_move_assignable_v<E>) = default;
  template <typename... Args> void EmplaceValue(Args &&...args) {
    // todo
  }
  template <typename... Args> void EmplaceError(Args &&...args) {
    // todo
  }
  void Swap(Result &other) noexcept(
      std::is_nothrow_move_constructible_v<T>
          &&std::is_nothrow_move_assignable_v<T>
              &&std::is_nothrow_move_constructible_v<E>
                  &&std::is_nothrow_move_assignable_v<E>) {
    std::swap(*this, other);
  }
  bool HasValue() const noexcept { return m_value.has_value(); }
  explicit operator bool() const noexcept { return HasValue(); }
  /*const & means this overload would work for const/non-const lvalues*/
  const T &operator*() const & { return m_value.value(); }
  /*&& would be used only for rvalue objects of Result*/
  T &&operator*() && { return std::move(m_value).value(); }
  const T *operator->() const { return &(m_value.value()); }
  const T &Value() const & { m_value.value(); }
  T &Value() && { return std::move(m_value).value(); }
  const E &Error() const & { m_error.value(); }
  E &Error() && { return std::move(m_error).value(); }
  Optional<T> Ok() const & { return m_value; }
  Optional<T> Ok() && { return std::move(m_value); };
  Optional<E> Err() const & { return m_error; }
  Optional<E> Err() && { return std::move(m_error); }
  template <typename U> T ValueOr(U &&defaultValue) const & {
    return m_value.value_or(defaultValue);
  }
  template <typename U> T ValueOr(U &&defaultValue) && {
    return std::move(m_value).value_or(defaultValue);
  }
  template <typename G> E ErrorOr(G &&defaultError) const & {
    return m_error.value_or(defaultError);
  }
  template <typename G> E ErrorOr(G &&defaultError) && {
    return std::move(m_error).value_or(defaultError);
  }
  template <typename G> bool CheckError(G &&error) const {
    if (HasValue()) {
      return static_cast<E>(error) == Error();
    }
    return false;
  }
  const T &ValueOrThrow() const & noexcept(false) { m_value.value(); }
  T &&ValueOrThrow() && noexcept(false) { std::move(m_value).value(); }
  template <typename F>
  T Resolve(F &&f) const {
    if (HasValue()) {
      return Value();
    }
    return std::invoke(std::forward(f), Error());
  }


  /*works similar to and_then*/
  template <class F, class V = const T&, class U = std::remove_cvref_t<std::invoke_result_t<F, V>>>
  auto Bind(F &&f) const
  {
    if (HasValue()) {
        if constexpr (is_specialization<U,Result>::value) {
            return std::invoke(std::forward(f),Value());
        }
        else {
            return Result<decltype(f(Value())),E> {std::invoke(std::forward(f),Value())};
        }
      //if f returns Result return std::invoke(std::forward(f), Value())
    }
    else {
        return Result<decltype(f(Value())),E> {Error()};
    }
  }

private:
  Optional<T> m_value;
  Optional<E> m_error;
};

/****************************************/
/****************************************/
/****************************************/
/*Result<void,E> template specialization*/
/****************************************/
/****************************************/
/****************************************/
template <typename E> class Result<void, E> final {
public:
  using value_type = void;
  using error_type = E;
  Result() noexcept;
  explicit Result(const E &e);
  explicit Result(E &&e);
};

} // namespace core
} // namespace ara
