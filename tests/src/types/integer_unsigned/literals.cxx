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

#include <type_traits>

#include <doctest/doctest.h>

#include "ztd/detail/types.hxx"

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    TEST_CASE("literals")
    {
        SUBCASE("u8")
        {
            auto x = 100_u8;
            CHECK(std::is_same_v<ztd::v2::u8, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("i16")
        {
            auto x = 100_u16;
            CHECK(std::is_same_v<ztd::v2::u16, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("i32")
        {
            auto x = 100_u32;
            CHECK(std::is_same_v<ztd::v2::u32, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("i64")
        {
            auto x = 100_u64;
            CHECK(std::is_same_v<ztd::v2::u64, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("isize")
        {
            auto x = 100_usize;
            CHECK(std::is_same_v<ztd::v2::usize, decltype(x)>);
            CHECK_EQ(x, 100);
        }
    }

    TEST_CASE("constexpr")
    {
        SUBCASE("u8")
        {
            [[maybe_unused]] constexpr ztd::i8 p1 = 1_i8;
            [[maybe_unused]] constexpr ztd::i8 p2 = 2_i8;

            [[maybe_unused]] constexpr ztd::i8 n1 = -1_i8;
            [[maybe_unused]] constexpr ztd::i8 n2 = -2_i8;
        }

        SUBCASE("i16")
        {
            [[maybe_unused]] constexpr ztd::i16 p1 = 1_i16;
            [[maybe_unused]] constexpr ztd::i16 p2 = 2_i16;

            [[maybe_unused]] constexpr ztd::i16 n1 = -1_i16;
            [[maybe_unused]] constexpr ztd::i16 n2 = -2_i16;
        }

        SUBCASE("i32")
        {
            [[maybe_unused]] constexpr ztd::i32 p1 = 1_i32;
            [[maybe_unused]] constexpr ztd::i32 p2 = 2_i32;

            [[maybe_unused]] constexpr ztd::i32 n1 = -1_i32;
            [[maybe_unused]] constexpr ztd::i32 n2 = -2_i32;
        }

        SUBCASE("i64")
        {
            [[maybe_unused]] constexpr ztd::i64 p1 = 1_i64;
            [[maybe_unused]] constexpr ztd::i64 p2 = 2_i64;

            [[maybe_unused]] constexpr ztd::i64 n1 = -1_i64;
            [[maybe_unused]] constexpr ztd::i64 n2 = -2_i64;
        }

        SUBCASE("isize")
        {
            [[maybe_unused]] constexpr ztd::isize p1 = 1_isize;
            [[maybe_unused]] constexpr ztd::isize p2 = 2_isize;

            [[maybe_unused]] constexpr ztd::isize n1 = -1_isize;
            [[maybe_unused]] constexpr ztd::isize n2 = -2_isize;
        }
    }
}
