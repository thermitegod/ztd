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

TEST(byte_si, literals_B)
{
    using namespace ztd::byte_si_literals;

    const auto a = 1_B;
    EXPECT_EQ(a.data(), 1);
    EXPECT_TRUE(a.is_byte());

    const auto b = 100_B;
    EXPECT_EQ(b.data(), 100);
    EXPECT_TRUE(b.is_byte());

    const auto c = 500_B;
    EXPECT_EQ(c.data(), 500);
    EXPECT_TRUE(c.is_byte());

    const auto d = 1000_B;
    EXPECT_EQ(d.data(), 1000);
    EXPECT_FALSE(d.is_byte());
}

TEST(byte_si, literals_kB)
{
    using namespace ztd::byte_si_literals;

    const auto a = 1_kB;
    EXPECT_EQ(a.data(), 1000);
    EXPECT_TRUE(a.is_kilobyte());

    const auto b = 100_kB;
    EXPECT_EQ(b.data(), 100000);
    EXPECT_TRUE(b.is_kilobyte());

    const auto c = 500_kB;
    EXPECT_EQ(c.data(), 500000);
    EXPECT_TRUE(c.is_kilobyte());

    const auto d = 1000_kB;
    EXPECT_EQ(d.data(), 1000000);
    EXPECT_FALSE(d.is_kilobyte());
}

TEST(byte_si, literals_MB)
{
    using namespace ztd::byte_si_literals;

    const auto a = 1_MB;
    EXPECT_EQ(a.data(), 1000000);
    EXPECT_TRUE(a.is_megabyte());

    const auto b = 100_MB;
    EXPECT_EQ(b.data(), 100000000);
    EXPECT_TRUE(b.is_megabyte());

    const auto c = 500_MB;
    EXPECT_EQ(c.data(), 500000000);
    EXPECT_TRUE(c.is_megabyte());

    const auto d = 1000_MB;
    EXPECT_EQ(d.data(), 1000000000);
    EXPECT_FALSE(d.is_megabyte());
}

TEST(byte_si, literals_GB)
{
    using namespace ztd::byte_si_literals;

    const auto a = 1_GB;
    EXPECT_EQ(a.data(), 1000000000);
    EXPECT_TRUE(a.is_gigabyte());

    const auto b = 100_GB;
    EXPECT_EQ(b.data(), 100000000000);
    EXPECT_TRUE(b.is_gigabyte());

    const auto c = 500_GB;
    EXPECT_EQ(c.data(), 500000000000);
    EXPECT_TRUE(c.is_gigabyte());

    const auto d = 1000_GB;
    EXPECT_EQ(d.data(), 1000000000000);
    EXPECT_FALSE(d.is_gigabyte());
}

TEST(byte_si, literals_TB)
{
    using namespace ztd::byte_si_literals;

    const auto a = 1_TB;
    EXPECT_EQ(a.data(), 1000000000000);
    EXPECT_TRUE(a.is_terrabyte());

    const auto b = 100_TB;
    EXPECT_EQ(b.data(), 100000000000000);
    EXPECT_TRUE(b.is_terrabyte());

    const auto c = 500_TB;
    EXPECT_EQ(c.data(), 500000000000000);
    EXPECT_TRUE(c.is_terrabyte());

    const auto d = 1000_TB;
    EXPECT_EQ(d.data(), 1000000000000000);
    EXPECT_FALSE(d.is_terrabyte());
}

TEST(byte_si, literals_PB)
{
    using namespace ztd::byte_si_literals;

    const auto a = 1_PB;
    EXPECT_EQ(a.data(), 1000000000000000);
    EXPECT_TRUE(a.is_petabyte());

    const auto b = 100_PB;
    EXPECT_EQ(b.data(), 100000000000000000);
    EXPECT_TRUE(b.is_petabyte());

    const auto c = 500_PB;
    EXPECT_EQ(c.data(), 500000000000000000);
    EXPECT_TRUE(c.is_petabyte());

    const auto d = 1000_PB;
    EXPECT_EQ(d.data(), 1000000000000000000);
    EXPECT_FALSE(d.is_petabyte());
}

TEST(byte_si, literals_EB)
{
    using namespace ztd::byte_si_literals;

    const auto a = 1_EB;
    EXPECT_EQ(a.data(), 1000000000000000000);
    EXPECT_TRUE(a.is_exabyte());

#ifdef NO_VERY_LARGE_INT_TYPE
    const auto b = 100_EB;
    EXPECT_EQ(b.data(), 100000000000000000000);
    EXPECT_TRUE(b.is_exabyte());

    const auto c = 500_EB;
    EXPECT_EQ(c.data(), 500000000000000000000);
    EXPECT_TRUE(c.is_exabyte());

    const auto d = 1000_EB;
    EXPECT_EQ(d.data(), 1000000000000000000000);
    EXPECT_FALSE(d.is_exabyte());
#endif
}
