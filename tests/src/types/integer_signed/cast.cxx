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

TEST_SUITE("signed integer<T>" * doctest::description(""))
{
    TEST_CASE_TEMPLATE("as ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        auto x = Integer(type(100));

        SUBCASE("u8")
        {
            auto y = x.template as<ztd::v2::u8>();
            REQUIRE(std::same_as<ztd::v2::u8::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u8);
        }

        SUBCASE("u16")
        {
            auto y = x.template as<ztd::v2::u16>();
            REQUIRE(std::same_as<ztd::v2::u16::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u16);
        }

        SUBCASE("u32")
        {
            auto y = x.template as<ztd::v2::u32>();
            REQUIRE(std::same_as<ztd::v2::u32::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u32);
        }

        SUBCASE("u64")
        {
            auto y = x.template as<ztd::v2::u64>();
            REQUIRE(std::same_as<ztd::v2::u64::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u64);
        }

        SUBCASE("usize")
        {
            auto y = x.template as<ztd::v2::usize>();
            REQUIRE(std::same_as<ztd::v2::usize::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_usize);
        }
    }

    TEST_CASE_TEMPLATE("as_saturate ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        auto x = Integer(type(100));

        SUBCASE("u8")
        {
            auto y = x.template as_saturate<ztd::v2::u8>();
            REQUIRE(std::same_as<ztd::v2::u8::integer_type, decltype(y.data())>);
            REQUIRE(std::same_as<decltype(y), decltype(100_u8)>);
            CHECK_EQ(y, 100_u8);
        }

        SUBCASE("u16")
        {
            auto y = x.template as_saturate<ztd::v2::u16>();
            REQUIRE(std::same_as<ztd::v2::u16::integer_type, decltype(y.data())>);
            REQUIRE(std::same_as<decltype(y), decltype(100_u16)>);
            CHECK_EQ(y, 100_u16);
        }

        SUBCASE("u32")
        {
            auto y = x.template as_saturate<ztd::v2::u32>();
            REQUIRE(std::same_as<ztd::v2::u32::integer_type, decltype(y.data())>);
            REQUIRE(std::same_as<decltype(y), decltype(100_u32)>);
            CHECK_EQ(y, 100_u32);
        }

        SUBCASE("u64")
        {
            auto y = x.template as_saturate<ztd::v2::u64>();
            REQUIRE(std::same_as<ztd::v2::u64::integer_type, decltype(y.data())>);
            REQUIRE(std::same_as<decltype(y), decltype(100_u64)>);
            CHECK_EQ(y, 100_u64);
        }

        SUBCASE("usize")
        {
            auto y = x.template as_saturate<ztd::v2::usize>();
            REQUIRE(std::same_as<ztd::v2::usize::integer_type, decltype(y.data())>);
            REQUIRE(std::same_as<decltype(y), decltype(100_usize)>);
            CHECK_EQ(y, 100_usize);
        }
    }

    TEST_CASE("cast_unsigned")
    {
        SUBCASE("i8")
        {
            ztd::v2::i8 x = 100_i8;

            auto y = x.cast_unsigned();

            REQUIRE(std::same_as<ztd::v2::u8::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u8);
        }

        SUBCASE("i16")
        {
            ztd::v2::i16 x = 100_i16;

            auto y = x.cast_unsigned();

            REQUIRE(std::same_as<ztd::v2::u16::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u16);
        }

        SUBCASE("i32")
        {
            ztd::v2::i32 x = 100_i32;

            auto y = x.cast_unsigned();

            REQUIRE(std::same_as<ztd::v2::u32::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u32);
        }

        SUBCASE("i64")
        {
            ztd::v2::i64 x = 100_i64;

            auto y = x.cast_unsigned();

            REQUIRE(std::same_as<ztd::v2::u64::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_u64);
        }

        SUBCASE("isize")
        {
            ztd::v2::isize x = 100_isize;

            auto y = x.cast_unsigned();

            REQUIRE(std::same_as<ztd::v2::usize::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_usize);
        }
    }
}
