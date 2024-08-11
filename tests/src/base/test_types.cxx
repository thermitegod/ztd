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

#include <gtest/gtest.h>

#include <type_traits>

#include "ztd/detail/types.hxx"

/**
 * unsigned type_literals
 */
TEST(literals_types, literal__u8)
{
    auto x = 42_u8;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::u8>));
}

TEST(literals_types, literal__const_u8)
{
    const auto x = 42_u8;

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

/**
 * signed type_literals
 */

TEST(literals_types, literal__i8)
{
    auto x = 42_i8;

    EXPECT_TRUE((std::is_same_v<decltype(x), ztd::i8>));
}

TEST(literals_types, literal__const_i8)
{
    const auto x = 42_i8;

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

/**
 * float type_literals
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
 * size type_literals
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

/**
 * std::format support
 */

TEST(format_types, types__literals)
{
    EXPECT_EQ(std::format("{}", 100_u8), "100");
    EXPECT_EQ(std::format("{}", 100_u16), "100");
    EXPECT_EQ(std::format("{}", 100_u32), "100");
    EXPECT_EQ(std::format("{}", 100_u64), "100");
    // EXPECT_EQ(std::format("{}", 100_u128), "100");

    EXPECT_EQ(std::format("{}", 100_i8), "100");
    EXPECT_EQ(std::format("{}", 100_i16), "100");
    EXPECT_EQ(std::format("{}", 100_i32), "100");
    EXPECT_EQ(std::format("{}", 100_i64), "100");
    // EXPECT_EQ(std::format("{}", 100_i128), "100");

    EXPECT_EQ(std::format("{}", 100_usize), "100");
    EXPECT_EQ(std::format("{}", 100_isize), "100");

    EXPECT_EQ(std::format("{}", 100.0_f32), "100");
    EXPECT_EQ(std::format("{}", 100.0_f64), "100");
}

TEST(format_types, types__variables)
{
    auto u8 = 100_u8;
    auto u16 = 100_u16;
    auto u32 = 100_u32;
    auto u64 = 100_u64;
    // auto u128 = 100_u128;
    EXPECT_EQ(std::format("{}", u8), "100");
    EXPECT_EQ(std::format("{}", u16), "100");
    EXPECT_EQ(std::format("{}", u32), "100");
    EXPECT_EQ(std::format("{}", u64), "100");
    // EXPECT_EQ(std::format("{}", u128), "100");

    auto i8 = 100_i8;
    auto i16 = 100_i16;
    auto i32 = 100_i32;
    auto i64 = 100_i64;
    // auto i128 = 100_i128;
    EXPECT_EQ(std::format("{}", i8), "100");
    EXPECT_EQ(std::format("{}", i16), "100");
    EXPECT_EQ(std::format("{}", i32), "100");
    EXPECT_EQ(std::format("{}", i64), "100");
    // EXPECT_EQ(std::format("{}", i128), "100");

    auto usize = 100_usize;
    auto isize = 100_isize;
    EXPECT_EQ(std::format("{}", usize), "100");
    EXPECT_EQ(std::format("{}", isize), "100");

    auto f32 = 100.5_f32;
    auto f64 = 100.5_f64;
    EXPECT_EQ(std::format("{}", f32), "100.5");
    EXPECT_EQ(std::format("{}", f64), "100.5");
}
