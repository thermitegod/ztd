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

#include <concepts>
#include <format>
#include <functional>

// #include "types/floating.hxx"
#include "types/integer.hxx"
#include "types/integer_type.hxx"

namespace ztd::v2::inline experimental
{
using i8 = ztd::integer<detail::i8>;
using i16 = ztd::integer<detail::i16>;
using i32 = ztd::integer<detail::i32>;
using i64 = ztd::integer<detail::i64>;
// using i128  = ztd::integer<detail::i128>;
using isize = ztd::integer<detail::isize>;

using u8 = ztd::integer<detail::u8>;
using u16 = ztd::integer<detail::u16>;
using u32 = ztd::integer<detail::u32>;
using u64 = ztd::integer<detail::u64>;
// using u128  = ztd::integer<detail::u128>;
using usize = ztd::integer<detail::usize>;

// using f32 = ztd::floating<std::float_t>;
// using f64 = ztd::floating<std::double_t>;
using f32 = std::float_t;
using f64 = std::double_t;
} // namespace ztd::v2::inline experimental

namespace ztd::literals::inline v2::inline experimental::type_literals
{
// clang-format off
consteval ztd::v2::i8    operator""_i8(unsigned long long v) { return ztd::v2::i8{static_cast<ztd::v2::i8::integer_type>(v)}; }
consteval ztd::v2::i16   operator""_i16(unsigned long long v) { return ztd::v2::i16{static_cast<ztd::v2::i16::integer_type>(v)}; }
consteval ztd::v2::i32   operator""_i32(unsigned long long v) { return ztd::v2::i32{static_cast<ztd::v2::i32::integer_type>(v)}; }
consteval ztd::v2::i64   operator""_i64(unsigned long long v) { return ztd::v2::i64{static_cast<ztd::v2::i64::integer_type>(v)}; }
// consteval ztd::v2::u128  operator""_i128(unsigned long long v) { return ztd::v2::i128{static_cast<ztd::v2::i128::integer_type>(v)}; }
consteval ztd::v2::isize operator""_isize(unsigned long long v) { return ztd::v2::isize{static_cast<ztd::v2::isize::integer_type>(v)}; }

consteval ztd::v2::u8    operator""_u8(unsigned long long v) { return ztd::v2::u8{static_cast<ztd::v2::u8::integer_type>(v)}; }
consteval ztd::v2::u16   operator""_u16(unsigned long long v) { return ztd::v2::u16{static_cast<ztd::v2::u16::integer_type>(v)}; }
consteval ztd::v2::u32   operator""_u32(unsigned long long v) { return ztd::v2::u32{static_cast<ztd::v2::u32::integer_type>(v)}; }
consteval ztd::v2::u64   operator""_u64(unsigned long long v) { return ztd::v2::u64{static_cast<ztd::v2::u64::integer_type>(v)}; }
// consteval ztd::v2::u128  operator""_u128(unsigned long long v) { return ztd::v2::u128{static_cast<ztd::v2::u128::integer_type>(v)}; }
consteval ztd::v2::usize operator""_usize(unsigned long long v) { return ztd::v2::usize{static_cast<ztd::v2::usize::integer_type>(v)}; }

consteval ztd::v2::f32   operator""_f32(long double v) { return ztd::v2::f32{static_cast<std::float_t>(v)}; }
consteval ztd::v2::f64   operator""_f64(long double v) { return ztd::v2::f64{static_cast<std::double_t>(v)}; }
// clang-format on
} // namespace ztd::literals::inline v2::inline experimental::type_literals

// clang-format off

namespace ztd::inline experimental
{
template<typename T>
struct integer_traits
{
    static constexpr bool is_arithmetic          = false;
    static constexpr bool is_integer             = false;
    static constexpr bool is_floating            = false;
    static constexpr bool is_signed_integer      = false;
    static constexpr bool is_unsigned_integer    = false;
};

template<typename T> concept is_arithmetic       = integer_traits<T>::is_arithmetic;
template<typename T> concept is_integer          = integer_traits<T>::is_integer;
template<typename T> concept is_floating         = integer_traits<T>::is_floating;
template<typename T> concept is_signed_integer   = integer_traits<T>::is_signed_integer;
template<typename T> concept is_unsigned_integer = integer_traits<T>::is_unsigned_integer;

template<>
struct integer_traits<ztd::v2::i8>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = true;
    static constexpr bool is_unsigned_integer = false;
};

template<>
struct integer_traits<ztd::v2::i16>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = true;
    static constexpr bool is_unsigned_integer = false;
};

template<>
struct integer_traits<ztd::v2::i32>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = true;
    static constexpr bool is_unsigned_integer = false;
};

template<>
struct integer_traits<ztd::v2::i64>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = true;
    static constexpr bool is_unsigned_integer = false;
};

template<>
struct integer_traits<ztd::v2::isize>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = true;
    static constexpr bool is_unsigned_integer = false;
};

template<>
struct integer_traits<ztd::v2::u8>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = false;
    static constexpr bool is_unsigned_integer = true;
};

template<>
struct integer_traits<ztd::v2::u16>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = false;
    static constexpr bool is_unsigned_integer = true;
};

template<>
struct integer_traits<ztd::v2::u32>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = false;
    static constexpr bool is_unsigned_integer = true;
};

template<>
struct integer_traits<ztd::v2::u64>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = false;
    static constexpr bool is_unsigned_integer = true;
};

template<>
struct integer_traits<ztd::v2::usize>
{
    static constexpr bool is_arithmetic       = true;
    static constexpr bool is_integer          = true;
    static constexpr bool is_floating         = false;
    static constexpr bool is_signed_integer   = false;
    static constexpr bool is_unsigned_integer = true;
};

// template<>
// struct integer_traits<ztd::v2::f32>
// {
//     static constexpr bool is_arithmetic       = true;
//     static constexpr bool is_integer          = false;
//     static constexpr bool is_floating         = true;
//     static constexpr bool is_signed_integer   = false;
//     static constexpr bool is_unsigned_integer = false;
// };
//
// template<>
// struct integer_traits<ztd::v2::f64>
// {
//     static constexpr bool is_arithmetic       = true;
//     static constexpr bool is_integer          = false;
//     static constexpr bool is_floating         = true;
//     static constexpr bool is_signed_integer   = false;
//     static constexpr bool is_unsigned_integer = false;
// };
}

// clang-format on

// std::format
template<typename T>
    requires(ztd::is_integer<T>)
struct std::formatter<T>
{
    std::formatter<typename T::integer_type> inner_;

    constexpr auto
    parse(std::format_parse_context& ctx)
    {
        return inner_.parse(ctx);
    }

    auto
    format(const T& obj, std::format_context& ctx) const
    {
        return inner_.format(obj.data(), ctx);
    }
};

// std::hash
template<typename T>
    requires(ztd::is_integer<T>)
struct std::hash<T>
{
    typename T::integer_type
    operator()(const T& obj) const
    {
        return std::hash<typename T::integer_type>()(obj.data());
    }
};

namespace ztd
{
using i8 = ztd::v2::i8;
using i16 = ztd::v2::i16;
using i32 = ztd::v2::i32;
using i64 = ztd::v2::i64;
// using i128  = ztd::v2::i128;
using isize = ztd::v2::isize;

using u8 = ztd::v2::u8;
using u16 = ztd::v2::u16;
using u32 = ztd::v2::u32;
using u64 = ztd::v2::u64;
// using u128  = ztd::v2::u128;
using usize = ztd::v2::usize;

using f32 = ztd::v2::f32;
using f64 = ztd::v2::f64;
} // namespace ztd

// clang-format on

#if !defined(ZTD_DISABLE_GLOBAL_TYPES)

using i8 = ztd::i8;
using i16 = ztd::i16;
using i32 = ztd::i32;
using i64 = ztd::i64;
// using i128  = ztd::i128;
using isize = ztd::isize;

using u8 = ztd::u8;
using u16 = ztd::u16;
using u32 = ztd::u32;
using u64 = ztd::u64;
// using u128  = ztd::u128;
using usize = ztd::usize;

using f32 = ztd::f32;
using f64 = ztd::f64;

#endif

using namespace ztd::literals::type_literals;

#undef ZTD_TYPES_VERSION
