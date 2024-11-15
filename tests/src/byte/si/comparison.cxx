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

#include <gtest/gtest.h>

#include "ztd/detail/byte_size.hxx"

/**
 * operator==
 */
TEST(byte_si_operator_equals, basic)
{
    const ztd::byte_si big = std::numeric_limits<std::uint64_t>::max();
    const ztd::byte_si small = std::numeric_limits<std::uint64_t>::min();

    EXPECT_EQ((big == big), true);
    EXPECT_EQ((small == small), true);
    EXPECT_EQ(!(big == small), true);
}

/**
 * operator!=
 */

TEST(byte_si_spaceship, not_equals)
{
    const ztd::byte_si big = std::numeric_limits<std::uint64_t>::max();
    const ztd::byte_si small = std::numeric_limits<std::uint64_t>::min();

    EXPECT_EQ(!(big != big), true);
    EXPECT_EQ(!(small != small), true);
    EXPECT_EQ((big != small), true);
}

/**
 * operator>
 */
TEST(byte_si_spaceship, basic)
{
    const ztd::byte_si big = std::numeric_limits<std::uint64_t>::max();
    const ztd::byte_si small = std::numeric_limits<std::uint64_t>::min();

    EXPECT_EQ(small > small, false);
    EXPECT_EQ(small > big, false);

    EXPECT_EQ(big > small, true);
    EXPECT_EQ(big > big, false);
}

/**
 * operator>=
 */

TEST(byte_si_spaceship, greater_than_or_equals)
{
    const ztd::byte_si big = std::numeric_limits<std::uint64_t>::max();
    const ztd::byte_si small = std::numeric_limits<std::uint64_t>::min();

    EXPECT_EQ(small >= small, true);
    EXPECT_EQ(small >= big, false);

    EXPECT_EQ(big >= small, true);
    EXPECT_EQ(big >= big, true);
}

/**
 * operator<
 */

TEST(byte_si_spaceship, less_than)
{
    const ztd::byte_si big = std::numeric_limits<std::uint64_t>::max();
    const ztd::byte_si small = std::numeric_limits<std::uint64_t>::min();

    EXPECT_EQ(small < small, false);
    EXPECT_EQ(small < big, true);

    EXPECT_EQ(big < small, false);
    EXPECT_EQ(big < big, false);
}

/**
 * operator<=
 */

TEST(byte_si_spaceship, less_than_or_equals)
{
    const ztd::byte_si big = std::numeric_limits<std::uint64_t>::max();
    const ztd::byte_si small = std::numeric_limits<std::uint64_t>::min();

    EXPECT_EQ(small <= small, true);
    EXPECT_EQ(small <= big, true);

    EXPECT_EQ(big <= small, false);
    EXPECT_EQ(big <= big, true);
}
