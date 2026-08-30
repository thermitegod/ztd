/**
 * Copyright (C) 2026 Brandon Zorn <brandonzorn@cock.li>
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
    TEST_CASE_TEMPLATE("operator& ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(0b1010'1100));
            auto b = Integer::create(static_cast<type>(0b1111'0000));

            CHECK_EQ(a & b, static_cast<type>(0b1010'0000));

            CHECK_EQ(a & Integer::create(0), 0);
            CHECK_EQ(b & Integer::create(0), 0);

            CHECK_EQ(a & 0, 0);
            CHECK_EQ(b & 0, 0);
        }
    }

    TEST_CASE_TEMPLATE("operator&= ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(0b1010'1100));
            auto b = Integer::create(static_cast<type>(0b1111'0000));

            a &= b;

            CHECK_EQ(a, static_cast<type>(0b1010'0000));
        }
    }

    TEST_CASE_TEMPLATE("operator| ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(0b1010'0000));
            auto b = Integer::create(static_cast<type>(0b0000'0101));

            CHECK_EQ(a | b, static_cast<type>(0b1010'0101));

            CHECK_EQ(a | Integer::create(0), a);
            CHECK_EQ(b | Integer::create(0), b);

            CHECK_EQ(a | 0, a);
            CHECK_EQ(b | 0, b);
        }
    }

    TEST_CASE_TEMPLATE("operator|= ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(0b1100'0000));
            auto b = Integer::create(static_cast<type>(0b0000'1111));

            a |= b;

            CHECK_EQ(a, static_cast<type>(0b1100'1111));
        }
    }

    TEST_CASE_TEMPLATE("operator^ ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(0b1111'0000));
            auto b = Integer::create(static_cast<type>(0b1010'1010));

            CHECK_EQ(a ^ b, Integer::create(static_cast<type>(0b0101'1010)));

            CHECK_EQ(a ^ a, 0);
            CHECK_EQ(b ^ b, 0);
        }
    }

    TEST_CASE_TEMPLATE("operator^= ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(0b1010));
            auto b = Integer::create(static_cast<type>(0b1100));

            a ^= b;

            CHECK_EQ(a, 0b0110);
        }
    }

    TEST_CASE_TEMPLATE("operator~ ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(0));
            auto b = ~a;

            CHECK_EQ(b, static_cast<type>(-1));
            CHECK_EQ(~b, a);
        }
    }

    TEST_CASE_TEMPLATE("operator<< ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(1));

            CHECK_EQ(a << 3, 8);
        }

        SUBCASE("shift by zero")
        {
            auto a = Integer::create(static_cast<type>(16));

            CHECK_EQ(a << 0, a);
        }
    }

    TEST_CASE_TEMPLATE("operator<<= ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(3));

            a <<= 2;

            CHECK_EQ(a, 12);
        }
    }

    TEST_CASE_TEMPLATE("operator>> ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(16));

            CHECK_EQ(a >> 2, 4);
        }

        SUBCASE("shift by zero")
        {
            auto a = Integer::create(static_cast<type>(16));

            CHECK_EQ(a >> 0, a);
        }

        SUBCASE("to zero")
        {
            auto a = Integer::create(static_cast<type>(1));

            CHECK_EQ(a >> 1, 0);
        }
    }

    TEST_CASE_TEMPLATE("operator>>= ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer::create(static_cast<type>(40));

            a >>= 3;

            CHECK_EQ(a, 5);
        }
    }
}
