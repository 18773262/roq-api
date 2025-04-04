/* Copyright (c) 2017-2025, Hans Erik Thrane */

#pragma once

#include <optional>
#include <tuple>

namespace roq {

namespace detail {
// note! constexpr helper for static testing
template <typename... Args>
struct MapHelper final {
  constexpr explicit MapHelper(std::tuple<Args...> const &args) : args_{args} {}
  constexpr explicit MapHelper(Args &&...args_) : args_{std::forward<Args>(args_)...} {}

  template <typename R>
  constexpr operator std::optional<R>() const;

  template <typename R>
  constexpr bool operator==(R rhs) const {
    auto tmp = (*this).operator std::optional<R>();
    if (tmp.has_value())
      return tmp.value() == rhs;
    return false;
  }

 private:
  std::tuple<Args...> const args_;
};
}  // namespace detail

template <typename... Args>
struct Map final {
  inline explicit Map(Args &&...args) : args_{std::forward<Args>(args)...} {}
  inline explicit Map(Args const &...args) : args_{args...} {}

  Map(Map const &) = delete;

  template <typename R>
  inline operator R() const {
    return helper<R>().value();
  }

  template <typename R>
  inline R get() const {
    return helper<R>().value();
  }

 protected:
  template <typename R>
  std::optional<R> helper() const;

 private:
  std::tuple<Args...> const args_;
};

template <typename... Args>
inline auto map(Args &&...args) {
  return Map{std::forward<Args>(args)...};
}

}  // namespace roq
