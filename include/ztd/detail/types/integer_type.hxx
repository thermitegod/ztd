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

namespace ztd
{
namespace detail
{
// clang-format off
struct i8{};
struct i16{};
struct i32{};
struct i64{};
struct isize{};
struct u8{};
struct u16{};
struct u32{};
struct u64{};
struct usize{};

// use to disable sign conversion for a type
// requires(!std::same_as<sign_conversion, ztd::detail::sign_conversion_disabled>)
struct sign_conversion_disabled{};

// Math modes
struct math_strict{};
struct math_overflow{};
// clang-format on

#if ZTD_DEFAULT_MATH_MODE == 1
using default_math = math_strict;
#elif ZTD_DEFAULT_MATH_MODE == 2
using default_math = math_overflow;
#else
#error ZTD_DEFAULT_MATH_MODE invalid value. valid values are 1, or 2
#endif
} // namespace detail

template<typename Tag> struct integer_type;

template<> struct integer_type<detail::i8>
{
    using type = std::int8_t;
    using sign_conversion = detail::u8;
};

template<> struct integer_type<detail::i16>
{
    using type = std::int16_t;
    using sign_conversion = detail::u16;
};

template<> struct integer_type<detail::i32>
{
    using type = std::int32_t;
    using sign_conversion = detail::u32;
};

template<> struct integer_type<detail::i64>
{
    using type = std::int64_t;
    using sign_conversion = detail::u64;
};

template<> struct integer_type<detail::isize>
{
    using type = std::ptrdiff_t;
    using sign_conversion = detail::usize;
};

template<> struct integer_type<detail::u8>
{
    using type = std::uint8_t;
    using sign_conversion = detail::i8;
};

template<> struct integer_type<detail::u16>
{
    using type = std::uint16_t;
    using sign_conversion = detail::i16;
};

template<> struct integer_type<detail::u32>
{
    using type = std::uint32_t;
    using sign_conversion = detail::i32;
};

template<> struct integer_type<detail::u64>
{
    using type = std::uint64_t;
    using sign_conversion = detail::i64;
};

template<> struct integer_type<detail::usize>
{
    using type = std::size_t;
    using sign_conversion = detail::isize;
};
} // namespace ztd
