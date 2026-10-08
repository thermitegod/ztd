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

#include "ztd/detail/byte_size.hxx"

TEST_SUITE("ztd::byte_si comparison")
{
    // operator==
    TEST_CASE("operator equals")
    {
        const auto big = ztd::byte_si{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_si{std::numeric_limits<std::uint64_t>::min()};

        CHECK(big == big);
        CHECK(small == small);
        CHECK_FALSE(big == small);
    }

    // operator!=
    TEST_CASE("operator not equals ")
    {
        const auto big = ztd::byte_si{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_si{std::numeric_limits<std::uint64_t>::min()};

        CHECK_FALSE(big != big);
        CHECK_FALSE(small != small);
        CHECK(big != small);
    }

    // operator>
    TEST_CASE("operator greater than")
    {
        const auto big = ztd::byte_si{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_si{std::numeric_limits<std::uint64_t>::min()};

        CHECK_FALSE(small > small);
        CHECK_FALSE(small > big);

        CHECK(big > small);
        CHECK_FALSE(big > big);
    }

    // operator>=
    TEST_CASE("operator greater than or equals")
    {
        const auto big = ztd::byte_si{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_si{std::numeric_limits<std::uint64_t>::min()};

        CHECK(small >= small);
        CHECK_FALSE(small >= big);

        CHECK(big >= small);
        CHECK(big >= big);
    }

    // operator<
    TEST_CASE("operator less than")
    {
        const auto big = ztd::byte_si{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_si{std::numeric_limits<std::uint64_t>::min()};

        CHECK_FALSE(small < small);
        CHECK(small < big);

        CHECK_FALSE(big < small);
        CHECK_FALSE(big < big);
    }

    // operator<=
    TEST_CASE("operator less than or equals")
    {
        const auto big = ztd::byte_si{std::numeric_limits<std::uint64_t>::max()};
        const auto small = ztd::byte_si{std::numeric_limits<std::uint64_t>::min()};

        CHECK(small <= small);
        CHECK(small <= big);

        CHECK_FALSE(big <= small);
        CHECK(big <= big);
    }
}
