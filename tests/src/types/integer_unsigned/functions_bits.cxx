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
    using namespace ztd::literals::type_literals;

    TEST_CASE_TEMPLATE("count_ones ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        // using type = typename Integer::integer_type;

        SUBCASE("basic") {}

        SUBCASE("max")
        {
            CHECK_EQ(Integer::MAX().count_ones(), Integer::BITS());
        }

        SUBCASE("min")
        {
            CHECK_EQ(Integer::MIN().count_ones(), 0);
        }
    }

    TEST_CASE_TEMPLATE("count_zeros ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        // using type = typename Integer::integer_type;

        SUBCASE("basic") {}

        SUBCASE("max")
        {
            CHECK_EQ(Integer::MAX().count_zeros(), 0);
        }

        SUBCASE("min")
        {
            CHECK_EQ(Integer::MIN().count_zeros(), Integer::BITS());
        }
    }

    TEST_CASE_TEMPLATE("leading_ones ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        // using type = typename Integer::integer_type;

        SUBCASE("basic") {}

        SUBCASE("max")
        {
            CHECK_EQ(Integer::MAX().leading_ones(), Integer::BITS());
        }

        SUBCASE("min")
        {
            CHECK_EQ(Integer::MIN().leading_ones(), 0);
        }
    }

    TEST_CASE_TEMPLATE("leading_zeros ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        // using type = typename Integer::integer_type;

        SUBCASE("basic") {}

        SUBCASE("max")
        {
            CHECK_EQ(Integer::MAX().leading_zeros(), 0);
        }

        SUBCASE("min")
        {
            CHECK_EQ(Integer::MIN().leading_zeros(), Integer::BITS());
        }
    }

    TEST_CASE_TEMPLATE("trailing_ones ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        // using type = typename Integer::integer_type;

        SUBCASE("basic") {}

        SUBCASE("max")
        {
            CHECK_EQ(Integer::MAX().trailing_ones(), Integer::BITS());
        }

        SUBCASE("min")
        {
            CHECK_EQ(Integer::MIN().trailing_ones(), 0);
        }
    }

    TEST_CASE_TEMPLATE("trailing_zeros ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        // using type = typename Integer::integer_type;

        SUBCASE("basic") {}

        SUBCASE("max")
        {
            CHECK_EQ(Integer::MAX().trailing_zeros(), 0);
        }

        SUBCASE("min")
        {
            CHECK_EQ(Integer::MIN().trailing_zeros(), Integer::BITS());
        }
    }

    TEST_CASE_TEMPLATE("rotate_right ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("compile only")
        {
            auto x = Integer(type(0b10101));

            [[maybe_unused]] auto z = x.rotate_right(0_i32);
        }
    }

    TEST_CASE_TEMPLATE("rotate_left ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("compile only")
        {
            auto x = Integer(type(0b10101));

            [[maybe_unused]] auto z = x.rotate_left(0_i32);
        }
    }

    TEST_CASE_TEMPLATE("swap_bytes ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("compile only")
        {
            auto x = Integer(type(0b10101));

            [[maybe_unused]] auto z = x.swap_bytes();
        }
    }
}
