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

#include <limits>

#include <doctest/doctest.h>

#include "ztd/detail/types.hxx"

TEST_SUITE("signed integer<T>" * doctest::description(""))
{
    TEST_CASE_TEMPLATE("MAX ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        CHECK_EQ(Integer::MAX(), std::numeric_limits<type>::max());
    }

    TEST_CASE_TEMPLATE("MIN ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        CHECK_EQ(Integer::MIN(), std::numeric_limits<type>::min());
    }

    TEST_CASE("BITS ")
    {
        SUBCASE("i8")
        {
            CHECK_EQ(i8::BITS(), 8_u32);
        }

        SUBCASE("i16")
        {
            CHECK_EQ(i16::BITS(), 16_u32);
        }

        SUBCASE("i32")
        {
            CHECK_EQ(i32::BITS(), 32_u32);
        }

        SUBCASE("i64")
        {
            CHECK_EQ(i64::BITS(), 64_u32);
        }

        SUBCASE("isize")
        {
            CHECK_EQ(isize::BITS(), 64_u32);
        }
    }

    TEST_CASE("size ")
    {
        SUBCASE("i8")
        {
            CHECK_EQ(sizeof(ztd::v2::i8), sizeof(ztd::v2::i8::integer_type));
        }

        SUBCASE("i16")
        {
            CHECK_EQ(sizeof(ztd::v2::i16), sizeof(ztd::v2::i16::integer_type));
        }

        SUBCASE("i32")
        {
            CHECK_EQ(sizeof(ztd::v2::i32), sizeof(ztd::v2::i32::integer_type));
        }

        SUBCASE("i64")
        {
            CHECK_EQ(sizeof(ztd::v2::i64), sizeof(ztd::v2::i64::integer_type));
        }

        SUBCASE("isize")
        {
            CHECK_EQ(sizeof(ztd::v2::isize), sizeof(ztd::v2::isize::integer_type));
        }
    }
}
