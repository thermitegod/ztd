/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <cstdint>

#if !defined(ZTD_DEFAULT_MATH_MODE)
#define ZTD_DEFAULT_MATH_MODE 1
#endif

namespace ztd::detail
{
// clang-format off
struct i8_tag{};
struct i16_tag{};
struct i32_tag{};
struct i64_tag{};
struct i128_tag{};
struct isize_tag{};
struct u8_tag{};
struct u16_tag{};
struct u32_tag{};
struct u64_tag{};
struct u128_tag{};
struct usize_tag{};

// use to disable sign conversion for a type
// requires(!std::is_same_v<sign_conversion_tag, ztd::detail::sign_conversion_disabled_tag>)
struct sign_conversion_disabled_tag{};

// Math modes
struct math_strict_tag{};
struct math_overflow_tag{};
// clang-format on

#if ZTD_DEFAULT_MATH_MODE == 1
using default_math_tag = math_strict_tag;
#elif ZTD_DEFAULT_MATH_MODE == 2
using default_math_tag = math_overflow_tag;
#else
#error ZTD_DEFAULT_MATH_MODE invalid value. valid values are 1, or 2
#endif

template<typename Tag> struct integer_traits;

template<> struct integer_traits<i8_tag>
{
    using integer_type = std::int8_t;
    using sign_conversion_tag = u8_tag;
};

template<> struct integer_traits<i16_tag>
{
    using integer_type = std::int16_t;
    using sign_conversion_tag = u16_tag;
};

template<> struct integer_traits<i32_tag>
{
    using integer_type = std::int32_t;
    using sign_conversion_tag = u32_tag;
};

template<> struct integer_traits<i64_tag>
{
    using integer_type = std::int64_t;
    using sign_conversion_tag = u64_tag;
};

#if 0
template<> struct integer_traits<i128_tag>
{
    using integer_type = __int128_t;
    using sign_conversion_tag = u128_tag;
};
#endif

template<> struct integer_traits<isize_tag>
{
    using integer_type = std::ptrdiff_t;
    using sign_conversion_tag = usize_tag;
};

template<> struct integer_traits<u8_tag>
{
    using integer_type = std::uint8_t;
    using sign_conversion_tag = i8_tag;
};

template<> struct integer_traits<u16_tag>
{
    using integer_type = std::uint16_t;
    using sign_conversion_tag = i16_tag;
};

template<> struct integer_traits<u32_tag>
{
    using integer_type = std::uint32_t;
    using sign_conversion_tag = i32_tag;
};

template<> struct integer_traits<u64_tag>
{
    using integer_type = std::uint64_t;
    using sign_conversion_tag = i64_tag;
};

#if 0
template<> struct integer_traits<u128_tag>
{
    using integer_type = __uint128_t;
    using sign_conversion_tag = i128_tag;
};
#endif

template<> struct integer_traits<usize_tag>
{
    using integer_type = std::size_t;
    using sign_conversion_tag = isize_tag;
};
} // namespace ztd::detail
