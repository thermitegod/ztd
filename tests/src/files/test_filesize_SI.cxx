/**
 * Copyright (C) 2022 Brandon Zorn <brandonzorn@cock.li>
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

#include <string>

#include "ztd/ztd.hxx"

/**
 * Zettabyte and Yottabyte support is disabled because there are no
 * integer types large enough to hold their size in bytes.
 * They can be enabled when the C++ standard has uint128_t.
 */
#define NO_VERY_LARGE_INT_TYPE

// clang-format off

/**
 * Byte        1
 * Kilobyte    1,000
 * Megabyte    1,000,000
 * Gigabyte    1,000,000,000
 * Terrabyte   1,000,000,000,000
 * Petabyte    1,000,000,000,000,000
 * Exabyte     1,000,000,000,000,000,000
 * Zettabyte   1,000,000,000,000,000,000,000
 * Yottabyte   1,000,000,000,000,000,000,000,000
 */
constexpr std::uint64_t SIZE_BYTE      = 1;
constexpr std::uint64_t SIZE_KILOBYTE  = 1000;
constexpr std::uint64_t SIZE_MEGABYTE  = 1000000;
constexpr std::uint64_t SIZE_GIGABYTE  = 1000000000;
constexpr std::uint64_t SIZE_TERABYTE  = 1000000000000;
constexpr std::uint64_t SIZE_PETABYTE  = 1000000000000000;
constexpr std::uint64_t SIZE_EXABYTE   = 1000000000000000000;

#ifndef NO_VERY_LARGE_INT_TYPE
constexpr std::uint64_t SIZE_ZETTABYTE = 1000000000000000000000;
constexpr std::uint64_t SIZE_YOTTABYTE = 1000000000000000000000000;
#endif

// clang-format on

TEST(FileSizeSI, size_zero)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(0);
    formatted = size.get_formated_size();
    EXPECT_EQ(formatted, "0 B");
}

TEST(FileSizeSI, rand_sizes)
{
    std::string formatted;

    const auto size01 = ztd::FileSizeSI(4488998912);
    formatted = size01.get_formated_size();
    EXPECT_EQ(formatted, "4.5 GB");

    const auto size02 = ztd::FileSizeSI(12544835584);
    formatted = size02.get_formated_size();
    EXPECT_EQ(formatted, "12.5 GB");

    const auto size03 = ztd::FileSizeSI(111031328768);
    formatted = size03.get_formated_size();
    EXPECT_EQ(formatted, "111.0 GB");

    const auto size04 = ztd::FileSizeSI(249008676864);
    formatted = size04.get_formated_size();
    EXPECT_EQ(formatted, "249.0 GB");

    const auto size05 = ztd::FileSizeSI(5973753856);
    formatted = size05.get_formated_size();
    EXPECT_EQ(formatted, "6.0 GB");

    const auto size06 = ztd::FileSizeSI(942819);
    formatted = size06.get_formated_size();
    EXPECT_EQ(formatted, "942.8 KB");

    const auto size07 = ztd::FileSizeSI(19260);
    formatted = size07.get_formated_size();
    EXPECT_EQ(formatted, "19.3 KB");

    const auto size08 = ztd::FileSizeSI(360);
    formatted = size08.get_formated_size();
    EXPECT_EQ(formatted, "360 B");
}

TEST(FileSizeSI, get_formated_size__int__B)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_BYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1 B");
}

TEST(FileSizeSI, get_formated_size__int__KB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_KILOBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 KB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 KB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 KB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 KB");
}

TEST(FileSizeSI, get_formated_size__int__MB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_MEGABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 MB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 MB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 MB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 MB");
}

TEST(FileSizeSI, get_formated_size__int__GB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_GIGABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 GB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 GB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 GB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 GB");
}

TEST(FileSizeSI, get_formated_size__int__TB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_TERABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 TB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 TB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 TB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 TB");
}

TEST(FileSizeSI, get_formated_size__int__PB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_PETABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 PB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 PB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 PB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 PB");
}

TEST(FileSizeSI, get_formated_size__int__EB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_EXABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 EB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 EB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 EB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 EB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(FileSizeSI, get_formated_size__int__ZB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_ZETTABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 ZB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 ZB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 ZB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 ZB");
}

TEST(FileSizeSI, get_formated_size__int__YB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_YOTTABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 YB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 YB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 YB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 YB");
}
#endif

TEST(FileSizeSI, get_filesize_parts_B)
{
    const auto size = ztd::FileSizeSI(SIZE_BYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "B");
}

TEST(FileSizeSI, get_filesize_parts_KB)
{
    const auto size = ztd::FileSizeSI(SIZE_KILOBYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "KB");
}

TEST(FileSizeSI, get_filesize_parts_MB)
{
    const auto size = ztd::FileSizeSI(SIZE_MEGABYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "MB");
}

TEST(FileSizeSI, get_filesize_parts_GB)
{
    const auto size = ztd::FileSizeSI(SIZE_GIGABYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "GB");
}

TEST(FileSizeSI, get_filesize_parts_TB)
{
    const auto size = ztd::FileSizeSI(SIZE_TERABYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "TB");
}

TEST(FileSizeSI, get_filesize_parts_PB)
{
    const auto size = ztd::FileSizeSI(SIZE_PETABYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "PB");
}

TEST(FileSizeSI, get_filesize_parts_EB)
{
    const auto size = ztd::FileSizeSI(SIZE_EXABYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "EB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(FileSizeSI, get_filesize_parts_ZB)
{
    const auto size = ztd::FileSizeSI(SIZE_ZETTABYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "ZB");
}

TEST(FileSizeSI, get_filesize_parts_YB)
{
    const auto size = ztd::FileSizeSI(SIZE_YOTTABYTE);
    const auto parts = size.get_filesize_parts();
    EXPECT_EQ(parts.first, 1.0);
    EXPECT_EQ(parts.second, "YB");
}
#endif
