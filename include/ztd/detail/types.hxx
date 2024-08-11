/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

// #define ZTD_SAFE_NUMERICS_TYPES

#include <cstdint>

#include <sys/types.h>

#if defined(ZTD_SAFE_NUMERICS_TYPES)
#include <format>
#include <functional>
#include <boost/safe_numerics/safe_integer.hpp>
#endif

// better type names
namespace ztd
{
inline namespace v1
{
// shared_ptr/unique_ptr like interface
template<typename T> using raw_ptr = T*;

#if !defined(ZTD_SAFE_NUMERICS_TYPES)
// clang-format off
using i8    = int8_t;
using i16   = int16_t;
using i32   = int32_t;
using i64   = int64_t;
using i128  = __int128_t;

using u8    = uint8_t;
using u16   = uint16_t;
using u32   = uint32_t;
using u64   = uint64_t;
using u128  = __uint128_t;

using f32   = float;
using f64   = double;

using usize = size_t;
using isize = ssize_t;
// clang-format on
#endif
} // namespace v1

#if defined(ZTD_SAFE_NUMERICS_TYPES)
inline namespace v2
{
// clang-format off
using i8    = boost::safe_numerics::safe<int8_t>;
using i16   = boost::safe_numerics::safe<int16_t>;
using i32   = boost::safe_numerics::safe<int32_t>;
using i64   = boost::safe_numerics::safe<int64_t>;
using i128  = boost::safe_numerics::safe<__int128_t>;

using u8    = boost::safe_numerics::safe<uint8_t>;
using u16   = boost::safe_numerics::safe<uint16_t>;
using u32   = boost::safe_numerics::safe<uint32_t>;
using u64   = boost::safe_numerics::safe<uint64_t>;
using u128  = boost::safe_numerics::safe<__uint128_t>;

using f32   = boost::safe_numerics::safe<float>;
using f64   = boost::safe_numerics::safe<double>;

using usize = boost::safe_numerics::safe<size_t>;
using isize = boost::safe_numerics::safe<ssize_t>;
// clang-format on
} // namespace v2
#endif
} // namespace ztd

namespace ztd::literals::type_literals
{
#if 1
// clang-format off
constexpr u8    operator"" _u8(unsigned long long v) { return v; }
constexpr u16   operator"" _u16(unsigned long long v) { return v; }
constexpr u32   operator"" _u32(unsigned long long v) { return v; }
constexpr u64   operator"" _u64(unsigned long long v) { return v; }
// constexpr u128  operator"" _u128(unsigned long long v) { return v; }

constexpr i8    operator"" _i8(unsigned long long v) { return v; }
constexpr i16   operator"" _i16(unsigned long long v) { return v; }
constexpr i32   operator"" _i32(unsigned long long v) { return v; }
constexpr i64   operator"" _i64(unsigned long long v) { return v; }
// constexpr i128  operator"" _i128(unsigned long long v) { return v; }

constexpr f32   operator"" _f32(long double v) { return v; }
constexpr f64   operator"" _f64(long double v) { return v; }

constexpr usize operator"" _usize(unsigned long long v) { return v; }
constexpr isize operator"" _isize(unsigned long long v) { return v; }
#endif
// clang-format on
} // namespace ztd::literals::type_literals

#if !defined(ZTD_DISABLE_GLOBAL_TYPES)

// clang-format off
using i8    = ztd::i8;
using i16   = ztd::i16;
using i32   = ztd::i32;
using i64   = ztd::i64;
using i128  = ztd::i128;

using u8    = ztd::u8;
using u16   = ztd::u16;
using u32   = ztd::u32;
using u64   = ztd::u64;
using u128  = ztd::u128;

using f32   = ztd::f32;
using f64   = ztd::f64;

using usize = ztd::usize;
using isize = ztd::isize;
// clang-format on

using namespace ztd::literals::type_literals;

#endif

#if defined(ZTD_SAFE_NUMERICS_TYPES)

// std::format support
template<typename T> struct std::formatter<boost::safe_numerics::safe<T>> : std::formatter<T>
{
    auto
    format(const boost::safe_numerics::safe<T>& t, std::format_context& ctx) const
    {
        return std::formatter<T>::format(static_cast<T>(t), ctx);
    }
};

// hash support
template<typename T> struct safe_numerics_hash
{
    std::size_t
    operator()(boost::safe_numerics::safe<T> const& t) const
    {
        return std::hash<T>()(t);
    }
};

#endif
