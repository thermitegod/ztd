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
    TEST_CASE_TEMPLATE("operator+ unary ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            auto value = Integer(type(0));
            CHECK_EQ(+value, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            auto value = Integer(type(100));
            CHECK_EQ(+value, Integer(type(100)));
        }

        SUBCASE("negative")
        {
            auto value = Integer(type(-100));
            CHECK_EQ(+value, Integer(type(-100)));
        }
    }

    TEST_CASE_TEMPLATE("operator- unary",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            auto value = Integer(type(0));
            CHECK_EQ(-value, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            auto value = Integer(type(100));
            CHECK_EQ(-value, Integer(type(-100)));
        }

        SUBCASE("negative")
        {
            auto value = Integer(type(-100));
            CHECK_EQ(-value, Integer(type(100)));
        }
    }
}
