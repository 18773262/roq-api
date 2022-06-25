/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <fmt/format.h>

#include <range/v3/view.hpp>

#include "roq/market_by_price_update.hpp"

#include "roq/json/datetime.hpp"
#include "roq/json/mbp_update.hpp"

namespace roq {
namespace json {

struct MarketByPriceUpdate final {
  explicit MarketByPriceUpdate(roq::MarketByPriceUpdate const &value) : value_(value) {}

  template <typename Context>
  auto format_to(Context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"("stream_id":{},)"
        R"("exchange":"{}",)"
        R"("symbol":"{}",)"
        R"("bids":[{}],)"
        R"("asks":[{}],)"
        R"("update_type":"{}",)"
        R"("exchange_time_utc":"{}",)"
        R"("exchange_sequence":{})"
        R"(}})"sv,
        value_.stream_id,
        value_.exchange,
        value_.symbol,
        fmt::join(ranges::views::transform(value_.bids, [](auto const &v) { return MBPUpdate(v); }), ","),
        fmt::join(ranges::views::transform(value_.asks, [](auto const &v) { return MBPUpdate(v); }), ","),
        value_.update_type,
        DateTime{value_.exchange_time_utc},
        value_.exchange_sequence);
    // note! remaining fields are internal
  }

 private:
  roq::MarketByPriceUpdate const &value_;
};

}  // namespace json
}  // namespace roq

template <>
struct fmt::formatter<roq::json::MarketByPriceUpdate> {
  template <typename Context>
  constexpr auto parse(Context &context) {
    return std::begin(context);
  }
  template <typename Context>
  auto format(roq::json::MarketByPriceUpdate const &value, Context &context) {
    return value.format_to(context);
  }
};
