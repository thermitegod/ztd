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
    TEST_CASE_TEMPLATE("as ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        auto x = Integer(type(100));

        SUBCASE("i8")
        {
            auto y = x.template as<ztd::v2::i8>();
            REQUIRE(std::is_same_v<ztd::v2::i8::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i8);
        }

        SUBCASE("i16")
        {
            auto y = x.template as<ztd::v2::i16>();
            REQUIRE(std::is_same_v<ztd::v2::i16::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i16);
        }

        SUBCASE("i32")
        {
            auto y = x.template as<ztd::v2::i32>();
            REQUIRE(std::is_same_v<ztd::v2::i32::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i32);
        }

        SUBCASE("i64")
        {
            auto y = x.template as<ztd::v2::i64>();
            REQUIRE(std::is_same_v<ztd::v2::i64::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i64);
        }

        SUBCASE("isize")
        {
            auto y = x.template as<ztd::v2::isize>();
            REQUIRE(std::is_same_v<ztd::v2::isize::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_isize);
        }
    }

    TEST_CASE_TEMPLATE("as_saturate ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        auto x = Integer(type(100));

        SUBCASE("i8")
        {
            auto y = x.template as_saturate<ztd::v2::i8>();
            REQUIRE(std::is_same_v<ztd::v2::i8::integer_type, decltype(y.data())>);
            REQUIRE(std::is_same_v<decltype(y), decltype(100_i8)>);
            CHECK_EQ(y, 100_i8);
        }

        SUBCASE("i16")
        {
            auto y = x.template as_saturate<ztd::v2::i16>();
            REQUIRE(std::is_same_v<ztd::v2::i16::integer_type, decltype(y.data())>);
            REQUIRE(std::is_same_v<decltype(y), decltype(100_i16)>);
            CHECK_EQ(y, 100_i16);
        }

        SUBCASE("i32")
        {
            auto y = x.template as_saturate<ztd::v2::i32>();
            REQUIRE(std::is_same_v<ztd::v2::i32::integer_type, decltype(y.data())>);
            REQUIRE(std::is_same_v<decltype(y), decltype(100_i32)>);
            CHECK_EQ(y, 100_i32);
        }

        SUBCASE("i64")
        {
            auto y = x.template as_saturate<ztd::v2::i64>();
            REQUIRE(std::is_same_v<ztd::v2::i64::integer_type, decltype(y.data())>);
            REQUIRE(std::is_same_v<decltype(y), decltype(100_i64)>);
            CHECK_EQ(y, 100_i64);
        }

        SUBCASE("isize")
        {
            auto y = x.template as_saturate<ztd::v2::isize>();
            REQUIRE(std::is_same_v<ztd::v2::isize::integer_type, decltype(y.data())>);
            REQUIRE(std::is_same_v<decltype(y), decltype(100_isize)>);
            CHECK_EQ(y, 100_isize);
        }
    }

    TEST_CASE("cast_signed")
    {
        SUBCASE("u8")
        {
            ztd::v2::u8 x = 100_u8;

            auto y = x.cast_signed();

            REQUIRE(std::is_same_v<ztd::v2::i8::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i8);
        }

        SUBCASE("u16")
        {
            ztd::v2::u16 x = 100_u16;

            auto y = x.cast_signed();

            REQUIRE(std::is_same_v<ztd::v2::i16::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i16);
        }

        SUBCASE("u32")
        {
            ztd::v2::u32 x = 100_u32;

            auto y = x.cast_signed();

            REQUIRE(std::is_same_v<ztd::v2::i32::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i32);
        }

        SUBCASE("u64")
        {
            ztd::v2::u64 x = 100_u64;

            auto y = x.cast_signed();

            REQUIRE(std::is_same_v<ztd::v2::i64::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_i64);
        }

        SUBCASE("usize")
        {
            ztd::v2::usize x = 100_usize;

            auto y = x.cast_signed();

            REQUIRE(std::is_same_v<ztd::v2::isize::integer_type, decltype(y.data())>);
            CHECK_EQ(y, 100_isize);
        }
    }
}
