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

TEST(byte_si_assignment, basic)
{
    const ztd::byte_si a1 = 1000ull;
    const ztd::byte_si b1 = 1000ull;
    const ztd::byte_si c1 = 1000ull;
    const ztd::byte_si d1 = 1000ull;

    ztd::byte_si a2 = 0_u64;
    ztd::byte_si b2 = 0_u64;
    ztd::byte_si c2 = 0_u64;
    ztd::byte_si d2 = 0_u64;

    a2 = a1;
    b2 = b1;
    c2 = c1;
    d2 = d1;

    EXPECT_EQ(a1, a2);
    EXPECT_EQ(b1, b2);
    EXPECT_EQ(c1, c2);
    EXPECT_EQ(d1, d2);
}