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

#include <format>
#include <functional>
#include <type_traits>

// #include "types/floating.hxx"
#include "types/integer.hxx"
#include "types/integer_traits.hxx"

namespace ztd::v2::inline experimental
{
using i8 = ztd::integer<detail::i8_tag>;
using i16 = ztd::integer<detail::i16_tag>;
using i32 = ztd::integer<detail::i32_tag>;
using i64 = ztd::integer<detail::i64_tag>;
// using i128  = ztd::integer<detail::i128_tag>;
using isize = ztd::integer<detail::isize_tag>;

using u8 = ztd::integer<detail::u8_tag>;
using u16 = ztd::integer<detail::u16_tag>;
using u32 = ztd::integer<detail::u32_tag>;
using u64 = ztd::integer<detail::u64_tag>;
// using u128  = ztd::integer<detail::u128_tag>;
using usize = ztd::integer<detail::usize_tag>;

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

namespace ztd::detail
{
// std::format
template<typename T> struct formatter
{
    constexpr auto
    parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto
    format(const T& obj, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}", obj.data());
    }
};
} // namespace ztd::detail

// clang-format off
template <> struct std::formatter<ztd::v2::i8> : ztd::detail::formatter<ztd::v2::i8>{};
template <> struct std::formatter<ztd::v2::i16> : ztd::detail::formatter<ztd::v2::i16>{};
template <> struct std::formatter<ztd::v2::i32> : ztd::detail::formatter<ztd::v2::i32>{};
template <> struct std::formatter<ztd::v2::i64> : ztd::detail::formatter<ztd::v2::i64>{};
// template <> struct std::formatter<ztd::v2::i128> : ztd::detail::formatter<ztd::v2::i128>{};
template <> struct std::formatter<ztd::v2::isize> : ztd::detail::formatter<ztd::v2::isize>{};

template <> struct std::formatter<ztd::v2::u8> : ztd::detail::formatter<ztd::v2::u8>{};
template <> struct std::formatter<ztd::v2::u16> : ztd::detail::formatter<ztd::v2::u16>{};
template <> struct std::formatter<ztd::v2::u32> : ztd::detail::formatter<ztd::v2::u32>{};
template <> struct std::formatter<ztd::v2::u64> : ztd::detail::formatter<ztd::v2::u64>{};
// template <> struct std::formatter<ztd::v2::u128> : ztd::detail::formatter<ztd::v2::u128>{};
template <> struct std::formatter<ztd::v2::usize> : ztd::detail::formatter<ztd::v2::usize>{};

// template <> struct std::formatter<ztd::v2::f32> : ztd::detail::formatter<ztd::v2::f32>{};
// template <> struct std::formatter<ztd::v2::f64> : ztd::detail::formatter<ztd::v2::f64>{};

// clang-format on

// std::hash
template<typename T> struct std::hash<ztd::integer<T>>
{
    typename ztd::integer<T>::integer_type
    operator()(const ztd::integer<T>& obj) const
    {
        return std::hash<typename ztd::integer<T>::integer_type>()(obj.data());
    }
};

#if 0
template<typename T> struct std::hash<ztd::floating<T>>
{
    typename ztd::floating<T>::floating_type
    operator()(const ztd::floating<T>& obj) const
    {
        return std::hash<typename ztd::floating<T>::floating_type>()(obj.data());
    }
};
#endif

// clang-format off

namespace ztd
{
// type traits
template<typename T> struct is_arithmetic     {static constexpr bool value = false;};
template<typename T> struct is_integral       {static constexpr bool value = false;};
template<typename T> struct is_floating_point {static constexpr bool value = false;};
template<typename T> struct is_signed         {static constexpr bool value = false;};
template<typename T> struct is_unsigned       {static constexpr bool value = false;};

template<typename T> constexpr bool is_arithmetic_v     = is_arithmetic<T>::value;
template<typename T> constexpr bool is_integral_v       = is_integral<T>::value;
template<typename T> constexpr bool is_floating_point_v = is_floating_point<T>::value;
template<typename T> constexpr bool is_signed_v         = is_signed<T>::value;
template<typename T> constexpr bool is_unsigned_v       = is_unsigned<T>::value;
} // namespace ztd

// i8
template<> struct ztd::is_arithmetic     <ztd::v2::i8> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::i8> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::i8> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::i8> : std::true_type{};
template<> struct ztd::is_unsigned       <ztd::v2::i8> : std::false_type{};

// i16
template<> struct ztd::is_arithmetic     <ztd::v2::i16> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::i16> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::i16> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::i16> : std::true_type{};
template<> struct ztd::is_unsigned       <ztd::v2::i16> : std::false_type{};

// i32
template<> struct ztd::is_arithmetic     <ztd::v2::i32> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::i32> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::i32> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::i32> : std::true_type{};
template<> struct ztd::is_unsigned       <ztd::v2::i32> : std::false_type{};

// i64
template<> struct ztd::is_arithmetic     <ztd::v2::i64> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::i64> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::i64> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::i64> : std::true_type{};
template<> struct ztd::is_unsigned       <ztd::v2::i64> : std::false_type{};

// i128
// template<> struct ztd::is_arithmetic     <ztd::v2::i128> : std::true_type{};
// template<> struct ztd::is_integral       <ztd::v2::i128> : std::true_type{};
// template<> struct ztd::is_floating_point <ztd::v2::i128> : std::false_type{};
// template<> struct ztd::is_signed         <ztd::v2::i128> : std::false_type{};
// template<> struct ztd::is_unsigned       <ztd::v2::i128> : std::true_type{};

// isize
template<> struct ztd::is_arithmetic     <ztd::v2::isize> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::isize> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::isize> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::isize> : std::true_type{};
template<> struct ztd::is_unsigned       <ztd::v2::isize> : std::false_type{};

// u8
template<> struct ztd::is_arithmetic     <ztd::v2::u8> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::u8> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::u8> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::u8> : std::false_type{};
template<> struct ztd::is_unsigned       <ztd::v2::u8> : std::true_type{};

// u16
template<> struct ztd::is_arithmetic     <ztd::v2::u16> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::u16> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::u16> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::u16> : std::false_type{};
template<> struct ztd::is_unsigned       <ztd::v2::u16> : std::true_type{};

// u32
template<> struct ztd::is_arithmetic     <ztd::v2::u32> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::u32> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::u32> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::u32> : std::false_type{};
template<> struct ztd::is_unsigned       <ztd::v2::u32> : std::true_type{};

// u64
template<> struct ztd::is_arithmetic     <ztd::v2::u64> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::u64> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::u64> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::u64> : std::false_type{};
template<> struct ztd::is_unsigned       <ztd::v2::u64> : std::true_type{};

// u128
// template<> struct ztd::is_arithmetic     <ztd::v2::u128> : std::true_type{};
// template<> struct ztd::is_integral       <ztd::v2::u128> : std::true_type{};
// template<> struct ztd::is_floating_point <ztd::v2::u128> : std::false_type{};
// template<> struct ztd::is_signed         <ztd::v2::u128> : std::false_type{};
// template<> struct ztd::is_unsigned       <ztd::v2::u128> : std::true_type{};

// usize
template<> struct ztd::is_arithmetic     <ztd::v2::usize> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::usize> : std::true_type{};
template<> struct ztd::is_floating_point <ztd::v2::usize> : std::false_type{};
template<> struct ztd::is_signed         <ztd::v2::usize> : std::false_type{};
template<> struct ztd::is_unsigned       <ztd::v2::usize> : std::true_type{};

// f32
template<> struct ztd::is_arithmetic     <ztd::v2::f32> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::f32> : std::false_type{};
template<> struct ztd::is_floating_point <ztd::v2::f32> : std::true_type{};
template<> struct ztd::is_signed         <ztd::v2::f32> : std::true_type{};
template<> struct ztd::is_unsigned       <ztd::v2::f32> : std::false_type{};

// f64
template<> struct ztd::is_arithmetic     <ztd::v2::f64> : std::true_type{};
template<> struct ztd::is_integral       <ztd::v2::f64> : std::false_type{};
template<> struct ztd::is_floating_point <ztd::v2::f64> : std::true_type{};
template<> struct ztd::is_signed         <ztd::v2::f64> : std::true_type{};
template<> struct ztd::is_unsigned       <ztd::v2::f64> : std::false_type{};
// clang-format on

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
