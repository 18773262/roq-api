/* Copyright (c) 2017-2021, Hans Erik Thrane */

#pragma once

// goals:
// - require the use of format strings (reason: making compile checks possible)
// - perhaps support both fmt::format and std::format

#include <fmt/format.h>

#include <string>
#include <string_view>
#include <utility>

#include "roq/format_str.h"
#include "roq/literals.h"

namespace roq {

// format

template <typename... Args>
inline std::string format(const format_str &fmt, Args &&... args) {
  return fmt::format(static_cast<std::string_view>(fmt), std::forward<Args>(args)...);
}

// format_to

template <typename OutputIt, typename... Args>
inline constexpr auto format_to(OutputIt out, const format_str &fmt, Args &&... args) {
  return fmt::format_to(out, static_cast<std::string_view>(fmt), std::forward<Args>(args)...);
}

// format_to_n

template <typename OutputIt, typename... Args>
inline constexpr auto format_to_n(OutputIt out, size_t n, const format_str &fmt, Args &&... args) {
  return fmt::format_to_n(out, n, static_cast<std::string_view>(fmt), std::forward<Args>(args)...);
}

// formatted_size

template <typename... Args>
inline constexpr auto formatted_size(const format_str &fmt, Args &&... args) {
  return fmt::formatted_size(static_cast<std::string_view>(fmt), std::forward<Args>(args)...);
}

// join

template <typename Range>
inline constexpr auto join(Range &&range, const std::string_view &sep) {
  return fmt::join(range, sep);
}

// formatter

struct formatter {
  template <typename Context>
  constexpr auto parse(Context &context) {
    return context.begin();
  }
};

}  // namespace roq
