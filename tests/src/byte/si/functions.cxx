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

#include "byte/si/utils.hxx"

#include "ztd/detail/byte_size.hxx"

/**
 * byte_si
 */

TEST(byte_si, size_zero)
{
    const ztd::byte_si size = 0ull;
    const auto formatted = size.format();
    EXPECT_EQ(formatted, "0 B");
}

TEST(byte_si, rand_sizes)
{
    std::string formatted;

    const ztd::byte_si size01 = 4488998912ull;
    formatted = size01.format();
    EXPECT_EQ(formatted, "4.5 GB");

    const ztd::byte_si size02 = 12544835584ull;
    formatted = size02.format();
    EXPECT_EQ(formatted, "12.5 GB");

    const ztd::byte_si size03 = 111031328768ull;
    formatted = size03.format();
    EXPECT_EQ(formatted, "111.0 GB");

    const ztd::byte_si size04 = 249008676864ull;
    formatted = size04.format();
    EXPECT_EQ(formatted, "249.0 GB");

    const ztd::byte_si size05 = 5973753856ull;
    formatted = size05.format();
    EXPECT_EQ(formatted, "6.0 GB");

    const ztd::byte_si size06 = 942819ull;
    formatted = size06.format();
    EXPECT_EQ(formatted, "942.8 kB");

    const ztd::byte_si size07 = 19260ull;
    formatted = size07.format();
    EXPECT_EQ(formatted, "19.3 kB");

    const ztd::byte_si size08 = 360ull;
    formatted = size08.format();
    EXPECT_EQ(formatted, "360 B");
}

TEST(byte_si, format__B)
{
    std::string formatted;

    const auto size = SIZE_BYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1 B");
}

TEST(byte_si, format__kB)
{
    std::string formatted;

    const auto size = SIZE_KILOBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 kB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 kB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 kB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 kB");
}

TEST(byte_si, format__MB)
{
    std::string formatted;

    const auto size = SIZE_MEGABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 MB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 MB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 MB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 MB");
}

TEST(byte_si, format__GB)
{
    std::string formatted;

    const auto size = SIZE_GIGABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 GB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 GB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 GB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 GB");
}

TEST(byte_si, format__TB)
{
    std::string formatted;

    const auto size = SIZE_TERABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 TB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 TB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 TB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 TB");
}

TEST(byte_si, format__PB)
{
    std::string formatted;

    const auto size = SIZE_PETABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 PB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 PB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 PB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 PB");
}

TEST(byte_si, format__EB)
{
    std::string formatted;

    const auto size = SIZE_EXABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 EB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 EB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 EB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 EB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(byte_si, format__ZB)
{
    std::string formatted;

    const auto size = SIZE_ZETTABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 ZB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 ZB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 ZB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 ZB");
}

TEST(byte_si, format__YB)
{
    std::string formatted;

    const auto size = SIZE_YOTTABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 YB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 YB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 YB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 YB");
}

TEST(byte_si, format__RB)
{
    std::string formatted;

    const auto size = SIZE_RONNABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 RB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 RB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 RB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 RB");
}

TEST(byte_si, format__QB)
{
    std::string formatted;

    const auto size = SIZE_QUETTABYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 QB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 QB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 QB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 QB");
}
#endif

/**
 * is_*()
 */

TEST(byte_si, is_byte)
{
    const auto size = SIZE_BYTE;

    EXPECT_TRUE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_kilobyte)
{
    const auto size = SIZE_KILOBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_TRUE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_megabyte)
{
    const auto size = SIZE_MEGABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_TRUE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_gigabyte)
{
    const auto size = SIZE_GIGABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_TRUE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_terrabyte)
{
    const auto size = SIZE_TERABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_TRUE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_petabyte)
{
    const auto size = SIZE_PETABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_TRUE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_exabyte)
{
    const auto size = SIZE_EXABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_TRUE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(byte_si, is_zettabyte)
{
    const auto size = SIZE_ZETTABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_TRUE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_yottabyte)
{
    const auto size = SIZE_YOTTABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_TRUE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_ronnabyte)
{
    const auto size = SIZE_RONNABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_TRUE(size.is_ronnabyte());
    EXPECT_FALSE(size.is_quettabyte());
}

TEST(byte_si, is_quettabyte)
{
    const auto size = SIZE_QUETTABYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kilobyte());
    EXPECT_FALSE(size.is_megabyte());
    EXPECT_FALSE(size.is_gigabyte());
    EXPECT_FALSE(size.is_terrabyte());
    EXPECT_FALSE(size.is_petabyte());
    EXPECT_FALSE(size.is_exabyte());
    EXPECT_FALSE(size.is_zettabyte());
    EXPECT_FALSE(size.is_yottabyte());
    EXPECT_FALSE(size.is_ronnabyte());
    EXPECT_TRUE(size.is_quettabyte());
}
#endif

/**
 * min/max
 */

TEST(byte_si, min_max)
{
    const ztd::byte_si x = 1_kB;
    const ztd::byte_si y = 500_B;

    EXPECT_EQ(x.max(y), x);
    EXPECT_EQ(x.min(y), y);
}
