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
            auto p1 = 1_i8;
            const auto p2 = 1_i8;
            constexpr auto p3 = 1_i8;

            CHECK(std::same_as<ztd::i8, decltype(p1)>);
            CHECK(std::same_as<const ztd::i8, decltype(p2)>);
            CHECK(std::same_as<const ztd::i8, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);

            auto n1 = -1_i8;
            const auto n2 = -1_i8;
            constexpr auto n3 = -1_i8;

            CHECK(std::same_as<ztd::i8, decltype(p1)>);
            CHECK(std::same_as<const ztd::i8, decltype(p2)>);
            CHECK(std::same_as<const ztd::i8, decltype(p3)>);

            CHECK_EQ(n1, -1);
            CHECK_EQ(n2, -1);
            CHECK_EQ(n3, -1);
        }

        SUBCASE("i16")
        {
            auto p1 = 1_i16;
            const auto p2 = 1_i16;
            constexpr auto p3 = 1_i16;

            CHECK(std::same_as<ztd::i16, decltype(p1)>);
            CHECK(std::same_as<const ztd::i16, decltype(p2)>);
            CHECK(std::same_as<const ztd::i16, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);

            auto n1 = -1_i16;
            const auto n2 = -1_i16;
            constexpr auto n3 = -1_i16;

            CHECK(std::same_as<ztd::i16, decltype(p1)>);
            CHECK(std::same_as<const ztd::i16, decltype(p2)>);
            CHECK(std::same_as<const ztd::i16, decltype(p3)>);

            CHECK_EQ(n1, -1);
            CHECK_EQ(n2, -1);
            CHECK_EQ(n3, -1);
        }

        SUBCASE("i32")
        {
            auto p1 = 1_i32;
            const auto p2 = 1_i32;
            constexpr auto p3 = 1_i32;

            CHECK(std::same_as<ztd::i32, decltype(p1)>);
            CHECK(std::same_as<const ztd::i32, decltype(p2)>);
            CHECK(std::same_as<const ztd::i32, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);

            auto n1 = -1_i32;
            const auto n2 = -1_i32;
            constexpr auto n3 = -1_i32;

            CHECK(std::same_as<ztd::i32, decltype(p1)>);
            CHECK(std::same_as<const ztd::i32, decltype(p2)>);
            CHECK(std::same_as<const ztd::i32, decltype(p3)>);

            CHECK_EQ(n1, -1);
            CHECK_EQ(n2, -1);
            CHECK_EQ(n3, -1);
        }

        SUBCASE("i64")
        {
            auto p1 = 1_i64;
            const auto p2 = 1_i64;
            constexpr auto p3 = 1_i64;

            CHECK(std::same_as<ztd::i64, decltype(p1)>);
            CHECK(std::same_as<const ztd::i64, decltype(p2)>);
            CHECK(std::same_as<const ztd::i64, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);

            auto n1 = -1_i64;
            const auto n2 = -1_i64;
            constexpr auto n3 = -1_i64;

            CHECK(std::same_as<ztd::i64, decltype(p1)>);
            CHECK(std::same_as<const ztd::i64, decltype(p2)>);
            CHECK(std::same_as<const ztd::i64, decltype(p3)>);

            CHECK_EQ(n1, -1);
            CHECK_EQ(n2, -1);
            CHECK_EQ(n3, -1);
        }

        SUBCASE("isize")
        {
            auto p1 = 1_isize;
            const auto p2 = 1_isize;
            constexpr auto p3 = 1_isize;

            CHECK(std::same_as<ztd::isize, decltype(p1)>);
            CHECK(std::same_as<const ztd::isize, decltype(p2)>);
            CHECK(std::same_as<const ztd::isize, decltype(p3)>);

            CHECK_EQ(p1, 1);
            CHECK_EQ(p2, 1);
            CHECK_EQ(p3, 1);

            auto n1 = -1_isize;
            const auto n2 = -1_isize;
            constexpr auto n3 = -1_isize;

            CHECK(std::same_as<ztd::isize, decltype(p1)>);
            CHECK(std::same_as<const ztd::isize, decltype(p2)>);
            CHECK(std::same_as<const ztd::isize, decltype(p3)>);

            CHECK_EQ(n1, -1);
            CHECK_EQ(n2, -1);
            CHECK_EQ(n3, -1);
        }
    }
}
