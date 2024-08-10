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
    TEST_CASE_TEMPLATE("operator== ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        const auto max = Integer::MAX();
        const auto min = Integer::MIN();

        CHECK_EQ((max == max), true);
        CHECK_EQ((min == min), true);
        CHECK_EQ(!(max == min), true);
    }

    TEST_CASE_TEMPLATE("operator!= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        const auto max = Integer::MAX();
        const auto min = Integer::MIN();

        CHECK_EQ(!(max != max), true);
        CHECK_EQ(!(min != min), true);
        CHECK_EQ((max != min), true);
    }

    TEST_CASE_TEMPLATE("operator> ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        const auto max = Integer::MAX();
        const auto min = Integer::MIN();

        CHECK_EQ(min > min, false);
        CHECK_EQ(min > max, false);

        CHECK_EQ(max > min, true);
        CHECK_EQ(max > max, false);
    }

    TEST_CASE_TEMPLATE("operator>= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        const auto max = Integer::MAX();
        const auto min = Integer::MIN();

        CHECK_EQ(min >= min, true);
        CHECK_EQ(min >= max, false);

        CHECK_EQ(max >= min, true);
        CHECK_EQ(max >= max, true);
    }

    TEST_CASE_TEMPLATE("operator< ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        const auto max = Integer::MAX();
        const auto min = Integer::MIN();

        CHECK_EQ(min < min, false);
        CHECK_EQ(min < max, true);

        CHECK_EQ(max < min, false);
        CHECK_EQ(max < max, false);
    }

    TEST_CASE_TEMPLATE("operator<= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        const auto max = Integer::MAX();
        const auto min = Integer::MIN();

        CHECK_EQ(min <= min, true);
        CHECK_EQ(min <= max, true);

        CHECK_EQ(max <= min, false);
        CHECK_EQ(max <= max, true);
    }
}
