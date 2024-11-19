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

#include "byte/iec/utils.hxx"

#include "ztd/detail/byte_size.hxx"

/**
 * byte_iec
 */

TEST(byte_iec, size_zero)
{
    const ztd::byte_iec size = 0ull;
    const auto formatted = size.format();
    EXPECT_EQ(formatted, "0 B");
}

TEST(byte_iec, rand_sizes)
{
    std::string formatted;

    const ztd::byte_iec size01 = 4488998912ull;
    formatted = size01.format();
    EXPECT_EQ(formatted, "4.2 GiB");

    const ztd::byte_iec size02 = 12544835584ull;
    formatted = size02.format();
    EXPECT_EQ(formatted, "11.7 GiB");

    const ztd::byte_iec size03 = 111031328768ull;
    formatted = size03.format();
    EXPECT_EQ(formatted, "103.4 GiB");

    const ztd::byte_iec size04 = 249008676864ull;
    formatted = size04.format();
    EXPECT_EQ(formatted, "231.9 GiB");

    const ztd::byte_iec size05 = 5973753856ull;
    formatted = size05.format();
    EXPECT_EQ(formatted, "5.6 GiB");

    const ztd::byte_iec size06 = 942819ull;
    formatted = size06.format();
    EXPECT_EQ(formatted, "920.7 KiB");

    const ztd::byte_iec size07 = 19260ull;
    formatted = size07.format();
    EXPECT_EQ(formatted, "18.8 KiB");

    const ztd::byte_iec size08 = 360ull;
    formatted = size08.format();
    EXPECT_EQ(formatted, "360 B");
}

TEST(byte_iec, format__B)
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

TEST(byte_iec, format__KiB)
{
    std::string formatted;

    const auto size = SIZE_KIBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 KiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 KiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 KiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 KiB");
}

TEST(byte_iec, format__MiB)
{
    std::string formatted;

    const auto size = SIZE_MEBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 MiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 MiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 MiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 MiB");
}

TEST(byte_iec, format__GiB)
{
    std::string formatted;

    const auto size = SIZE_GIBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 GiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 GiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 GiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 GiB");
}

TEST(byte_iec, format__TiB)
{
    std::string formatted;

    const auto size = SIZE_TEBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 TiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 TiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 TiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 TiB");
}

TEST(byte_iec, format__PiB)
{
    std::string formatted;

    const auto size = SIZE_PEBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 PiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 PiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 PiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 PiB");
}

TEST(byte_iec, format__EiB)
{
    std::string formatted;

    const auto size = SIZE_EXBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 EiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 EiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 EiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 EiB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(byte_iec, format__ZiB)
{
    std::string formatted;

    const auto size = SIZE_ZEBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 ZiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 ZiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 ZiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 ZiB");
}

TEST(byte_iec, format__YiB)
{
    std::string formatted;

    const auto size = SIZE_YOBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 YiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 YiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 YiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 YiB");
}

TEST(byte_iec, format__RiB)
{
    std::string formatted;

    const auto size = SIZE_ROBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 RiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 RiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 RiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 RiB");
}

TEST(byte_iec, format__QiB)
{
    std::string formatted;

    const auto size = SIZE_QUBIBYTE;

    formatted = size.format(0);
    EXPECT_EQ(formatted, "1 QiB");

    formatted = size.format(1);
    EXPECT_EQ(formatted, "1.0 QiB");

    formatted = size.format(2);
    EXPECT_EQ(formatted, "1.00 QiB");

    formatted = size.format(3);
    EXPECT_EQ(formatted, "1.000 QiB");
}
#endif

/**
 * is_*()
 */

TEST(byte_iec, is_byte)
{
    const auto size = SIZE_BYTE;

    EXPECT_TRUE(size.is_byte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_kibibyte)
{
    const auto size = SIZE_KIBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_TRUE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_mebibyte)
{
    const auto size = SIZE_MEBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_TRUE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_gibibyte)
{
    const auto size = SIZE_GIBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_TRUE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_tebibyte)
{
    const auto size = SIZE_TEBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_TRUE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_pebibyte)
{
    const auto size = SIZE_PEBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_TRUE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_exbibyte)
{
    const auto size = SIZE_EXBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_TRUE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(byte_iec, is_zebibyte)
{
    const auto size = SIZE_ZEBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_TRUE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_yobibyte)
{
    const auto size = SIZE_YOBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_TRUE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_robibyte)
{
    const auto size = SIZE_ROBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_TRUE(size.is_robibyte());
    EXPECT_FALSE(size.is_qubibyte());
}

TEST(byte_iec, is_qubibyte)
{
    const auto size = SIZE_QUBIBYTE;

    EXPECT_FALSE(size.is_byte());
    EXPECT_FALSE(size.is_kibibyte());
    EXPECT_FALSE(size.is_mebibyte());
    EXPECT_FALSE(size.is_gibibyte());
    EXPECT_FALSE(size.is_tebibyte());
    EXPECT_FALSE(size.is_pebibyte());
    EXPECT_FALSE(size.is_exbibyte());
    EXPECT_FALSE(size.is_zebibyte());
    EXPECT_FALSE(size.is_yobibyte());
    EXPECT_FALSE(size.is_robibyte());
    EXPECT_TRUE(size.is_qubibyte());
}
#endif

/**
 * min/max
 */

TEST(byte_iec, min_max)
{
    const ztd::byte_iec x = 1_KiB;
    const ztd::byte_iec y = 512_B;

    EXPECT_EQ(x.max(y), x);
    EXPECT_EQ(x.min(y), y);
}
