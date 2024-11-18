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

TEST(byte_iec, literals_B)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_B;
    EXPECT_EQ(a.data(), 1);
    EXPECT_TRUE(a.is_byte());

    const auto b = 100_B;
    EXPECT_EQ(b.data(), 100);
    EXPECT_TRUE(b.is_byte());

    const auto c = 500_B;
    EXPECT_EQ(c.data(), 500);
    EXPECT_TRUE(c.is_byte());

    const auto d = 1024_B;
    EXPECT_EQ(d.data(), 1024);
    EXPECT_FALSE(d.is_byte());
}

TEST(byte_iec, literals_KiB)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_KiB;
    EXPECT_EQ(a.data(), 1024);
    EXPECT_TRUE(a.is_kibibyte());

    const auto b = 100_KiB;
    EXPECT_EQ(b.data(), 102400);
    EXPECT_TRUE(b.is_kibibyte());

    const auto c = 500_KiB;
    EXPECT_EQ(c.data(), 512000);
    EXPECT_TRUE(c.is_kibibyte());

    const auto d = 1024_KiB;
    EXPECT_EQ(d.data(), 1048576);
    EXPECT_FALSE(d.is_kibibyte());
}

TEST(byte_iec, literals_MiB)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_MiB;
    EXPECT_EQ(a.data(), 1048576);
    EXPECT_TRUE(a.is_mebibyte());

    const auto b = 100_MiB;
    EXPECT_EQ(b.data(), 104857600);
    EXPECT_TRUE(b.is_mebibyte());

    const auto c = 500_MiB;
    EXPECT_EQ(c.data(), 524288000);
    EXPECT_TRUE(c.is_mebibyte());

    const auto d = 1024_MiB;
    EXPECT_EQ(d.data(), 1073741824);
    EXPECT_FALSE(d.is_mebibyte());
}

TEST(byte_iec, literals_GiB)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_GiB;
    EXPECT_EQ(a.data(), 1073741824);
    EXPECT_TRUE(a.is_gibibyte());

    const auto b = 100_GiB;
    EXPECT_EQ(b.data(), 107374182400);
    EXPECT_TRUE(b.is_gibibyte());

    const auto c = 500_GiB;
    EXPECT_EQ(c.data(), 536870912000);
    EXPECT_TRUE(c.is_gibibyte());

    const auto d = 1024_GiB;
    EXPECT_EQ(d.data(), 1099511627776);
    EXPECT_FALSE(d.is_gibibyte());
}

TEST(byte_iec, literals_TiB)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_TiB;
    EXPECT_EQ(a.data(), 1099511627776);
    EXPECT_TRUE(a.is_tebibyte());

    const auto b = 100_TiB;
    EXPECT_EQ(b.data(), 109951162777600);
    EXPECT_TRUE(b.is_tebibyte());

    const auto c = 500_TiB;
    EXPECT_EQ(c.data(), 549755813888000);
    EXPECT_TRUE(c.is_tebibyte());

    const auto d = 1024_TiB;
    EXPECT_EQ(d.data(), 1125899906842624);
    EXPECT_FALSE(d.is_tebibyte());
}

TEST(byte_iec, literals_PiB)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_PiB;
    EXPECT_EQ(a.data(), 1125899906842624);
    EXPECT_TRUE(a.is_pebibyte());

    const auto b = 100_PiB;
    EXPECT_EQ(b.data(), 112589990684262400);
    EXPECT_TRUE(b.is_pebibyte());

    const auto c = 500_PiB;
    EXPECT_EQ(c.data(), 562949953421312000);
    EXPECT_TRUE(c.is_pebibyte());

    const auto d = 1024_PiB;
    EXPECT_EQ(d.data(), 1152921504606846976);
    EXPECT_FALSE(d.is_pebibyte());
}

TEST(byte_iec, literals_EiB)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_EiB;
    EXPECT_EQ(a.data(), 1152921504606846976);
    EXPECT_TRUE(a.is_exbibyte());

#ifdef NO_VERY_LARGE_INT_TYPE
    const auto b = 100_EiB;
    EXPECT_EQ(b.data(), 115292150460684697600);
    EXPECT_TRUE(b.is_exbibyte());

    const auto c = 500_EiB;
    EXPECT_EQ(c.data(), 576460752303423488000);
    EXPECT_TRUE(c.is_exbibyte());

    const auto d = 1024_EiB;
    EXPECT_EQ(d.data(), 1180591620717411303424);
    EXPECT_FALSE(d.is_exbibyte());
#endif
}
