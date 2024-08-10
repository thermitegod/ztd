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

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    TEST_CASE_TEMPLATE("constants ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("MAX")
        {
            CHECK_EQ(Integer::MAX().data(), std::numeric_limits<type>::max());
        }

        SUBCASE("MIN")
        {
            CHECK_EQ(Integer::MIN().data(), std::numeric_limits<type>::min());
        }
    }

    TEST_CASE("size ")
    {
        SUBCASE("u8")
        {
            CHECK_EQ(sizeof(ztd::v2::u8), sizeof(ztd::v2::u8::integer_type));
        }

        SUBCASE("u16")
        {
            CHECK_EQ(sizeof(ztd::v2::u16), sizeof(ztd::v2::u16::integer_type));
        }

        SUBCASE("u32")
        {
            CHECK_EQ(sizeof(ztd::v2::u32), sizeof(ztd::v2::u32::integer_type));
        }

        SUBCASE("u64")
        {
            CHECK_EQ(sizeof(ztd::v2::u64), sizeof(ztd::v2::u64::integer_type));
        }

        SUBCASE("usize")
        {
            CHECK_EQ(sizeof(ztd::v2::usize), sizeof(ztd::v2::usize::integer_type));
        }
    }
}
