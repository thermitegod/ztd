/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include "ztd/detail/byte_size.hxx"

TEST_SUITE("ztd::byte_iec comparison" * doctest::description(""))
{
    // operator==
    TEST_CASE("operator equals")
    {
        const auto big = ztd::byte_iec{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_iec{std::numeric_limits<std::uint64_t>::min()};

        CHECK_EQ((big == big), true);
        CHECK_EQ((small == small), true);
        CHECK_EQ(!(big == small), true);
    }

    // operator!=
    TEST_CASE("operator not equals ")
    {
        const auto big = ztd::byte_iec{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_iec{std::numeric_limits<std::uint64_t>::min()};

        CHECK_EQ(!(big != big), true);
        CHECK_EQ(!(small != small), true);
        CHECK_EQ((big != small), true);
    }

    // operator>
    TEST_CASE("operator greater than")
    {
        const auto big = ztd::byte_iec{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_iec{std::numeric_limits<std::uint64_t>::min()};

        CHECK_EQ(small > small, false);
        CHECK_EQ(small > big, false);

        CHECK_EQ(big > small, true);
        CHECK_EQ(big > big, false);
    }

    // operator>=
    TEST_CASE("operator greater than or equals")
    {
        const auto big = ztd::byte_iec{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_iec{std::numeric_limits<std::uint64_t>::min()};

        CHECK_EQ(small >= small, true);
        CHECK_EQ(small >= big, false);

        CHECK_EQ(big >= small, true);
        CHECK_EQ(big >= big, true);
    }

    // operator<
    TEST_CASE("operator less than")
    {
        const auto big = ztd::byte_iec{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_iec{std::numeric_limits<std::uint64_t>::min()};

        CHECK_EQ(small < small, false);
        CHECK_EQ(small < big, true);

        CHECK_EQ(big < small, false);
        CHECK_EQ(big < big, false);
    }

    // operator<=
    TEST_CASE("operator less than or equals")
    {
        const auto big = ztd::byte_iec{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_iec{std::numeric_limits<std::uint64_t>::min()};

        CHECK_EQ(small <= small, true);
        CHECK_EQ(small <= big, true);

        CHECK_EQ(big <= small, false);
        CHECK_EQ(big <= big, true);
    }
}
