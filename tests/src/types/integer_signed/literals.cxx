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

#include <doctest/doctest.h>

#include "ztd/detail/types.hxx"

TEST_SUITE("signed integer<T>" * doctest::description(""))
{
    TEST_CASE("literals")
    {
        SUBCASE("i8")
        {
            auto x = 100_i8;
            CHECK(std::is_same_v<ztd::v2::i8, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("i16")
        {
            auto x = 100_i16;
            CHECK(std::is_same_v<ztd::v2::i16, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("i32")
        {
            auto x = 100_i32;
            CHECK(std::is_same_v<ztd::v2::i32, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("i64")
        {
            auto x = 100_i64;
            CHECK(std::is_same_v<ztd::v2::i64, decltype(x)>);
            CHECK_EQ(x, 100);
        }

        SUBCASE("isize")
        {
            auto x = 100_isize;
            CHECK(std::is_same_v<ztd::v2::isize, decltype(x)>);
            CHECK_EQ(x, 100);
        }
    }

    TEST_CASE("constexpr")
    {
        SUBCASE("u8")
        {
            [[maybe_unused]] constexpr ztd::u8 p1 = 1_u8;
            [[maybe_unused]] constexpr ztd::u8 p2 = 2_u8;
        }

        SUBCASE("i16")
        {
            [[maybe_unused]] constexpr ztd::u16 p1 = 1_u16;
            [[maybe_unused]] constexpr ztd::u16 p2 = 2_u16;
        }

        SUBCASE("i32")
        {
            [[maybe_unused]] constexpr ztd::u32 p1 = 1_u32;
            [[maybe_unused]] constexpr ztd::u32 p2 = 2_u32;
        }

        SUBCASE("i64")
        {
            [[maybe_unused]] constexpr ztd::u64 p1 = 1_u64;
            [[maybe_unused]] constexpr ztd::u64 p2 = 2_u64;
        }

        SUBCASE("isize")
        {
            [[maybe_unused]] constexpr ztd::usize p1 = 1_usize;
            [[maybe_unused]] constexpr ztd::usize p2 = 2_usize;
        }
    }
}
