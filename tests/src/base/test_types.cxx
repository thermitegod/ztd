/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
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

#include <gtest/gtest.h>

#include <type_traits>

#include "ztd/ztd.hxx"

/**
 * unsigned
 */

TEST(literals_types, literal__u8)
{
    auto x = 420_u8;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::u8>));
}

TEST(literals_types, literal__const_u8)
{
    const auto x = 420_u8;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::u8>));
}

TEST(literals_types, literal__u16)
{
    auto x = 420_u16;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::u16>));
}

TEST(literals_types, literal__const_u16)
{
    const auto x = 420_u16;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::u16>));
}

TEST(literals_types, literal__u32)
{
    auto x = 420_u32;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::u32>));
}

TEST(literals_types, literal__const_u32)
{
    const auto x = 420_u32;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::u32>));
}

TEST(literals_types, literal__u64)
{
    auto x = 420_u64;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::u64>));
}

TEST(literals_types, literal__const_u64)
{
    const auto x = 420_u64;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::u64>));
}

TEST(literals_types, literal__u128)
{
    auto x = 420_u128;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::u128>));
}

TEST(literals_types, literal__const_u128)
{
    const auto x = 420_u128;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::u128>));
}

/**
 * signed
 */

TEST(literals_types, literal__i8)
{
    auto x = 420_i8;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::i8>));
}

TEST(literals_types, literal__const_i8)
{
    const auto x = 420_i8;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::i8>));
}

TEST(literals_types, literal__i16)
{
    auto x = 420_i16;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::i16>));
}

TEST(literals_types, literal__const_i16)
{
    const auto x = 420_i16;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::i16>));
}

TEST(literals_types, literal__i32)
{
    auto x = 420_i32;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::i32>));
}

TEST(literals_types, literal__const_i32)
{
    const auto x = 420_i32;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::i32>));
}

TEST(literals_types, literal__i64)
{
    auto x = 420_i64;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::i64>));
}

TEST(literals_types, literal__const_i64)
{
    const auto x = 420_i64;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::i64>));
}

TEST(literals_types, literal__i128)
{
    auto x = 420_i128;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::i128>));
}

TEST(literals_types, literal__const_i128)
{
    const auto x = 420_i128;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::i128>));
}

/**
 * float
 */

TEST(literals_types, literal__f32)
{
    auto x = 420.69_f32;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::f32>));
}

TEST(literals_types, literal__const_f32)
{
    const auto x = 420.69_f32;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::f32>));
}

TEST(literals_types, literal__f64)
{
    auto x = 420.69_f64;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::f64>));
}

TEST(literals_types, literal__const_f64)
{
    const auto x = 420.69_f64;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::f64>));
}

/**
 * size
 */

TEST(literals_types, literal__usize)
{
    auto x = 420_usize;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::usize>));
}

TEST(literals_types, literal__const_usize)
{
    const auto x = 420_usize;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::usize>));
}

TEST(literals_types, literal__isize)
{
    auto x = 420_isize;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::isize>));
}

TEST(literals_types, literal__const_isize)
{
    const auto x = 420_isize;

    EXPECT_TRUE((std::is_same_v<decltype(x), const ztd::isize>));
}
