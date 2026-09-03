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

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    TEST_CASE("literals")
    {
        SUBCASE("u8")
        {
            auto p1 = 1_u8;
            const auto p2 = 1_u8;
            constexpr auto p3 = 1_u8;

            CHECK(std::same_as<ztd::u8, decltype(p1)>);
            CHECK(std::same_as<const ztd::u8, decltype(p2)>);
            CHECK(std::same_as<const ztd::u8, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);
        }

        SUBCASE("u16")
        {
            auto p1 = 1_u16;
            const auto p2 = 1_u16;
            constexpr auto p3 = 1_u16;

            CHECK(std::same_as<ztd::u16, decltype(p1)>);
            CHECK(std::same_as<const ztd::u16, decltype(p2)>);
            CHECK(std::same_as<const ztd::u16, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);
        }

        SUBCASE("u32")
        {
            auto p1 = 1_u32;
            const auto p2 = 1_u32;
            constexpr auto p3 = 1_u32;

            CHECK(std::same_as<ztd::u32, decltype(p1)>);
            CHECK(std::same_as<const ztd::u32, decltype(p2)>);
            CHECK(std::same_as<const ztd::u32, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);
        }

        SUBCASE("u64")
        {
            auto p1 = 1_u64;
            const auto p2 = 1_u64;
            constexpr auto p3 = 1_u64;

            CHECK(std::same_as<ztd::u64, decltype(p1)>);
            CHECK(std::same_as<const ztd::u64, decltype(p2)>);
            CHECK(std::same_as<const ztd::u64, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);
        }

        SUBCASE("usize")
        {
            auto p1 = 1_usize;
            const auto p2 = 1_usize;
            constexpr auto p3 = 1_usize;

            CHECK(std::same_as<ztd::usize, decltype(p1)>);
            CHECK(std::same_as<const ztd::usize, decltype(p2)>);
            CHECK(std::same_as<const ztd::usize, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);
        }
    }
}
