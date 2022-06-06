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

#include "../../../src/ztd.hxx"
#include "../../../src/ztd-files.hxx"

/**
 * Zettabyte and Yottabyte support is disabled because there are no
 * integer types large enough to hold their size in bytes.
 * They can be enabled when the C++ standard has uint128_t.
 */
#define NO_VERY_LARGE_INT_TYPE

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
#define SIZE_BYTE      1
#define SIZE_KILOBYTE  1000
#define SIZE_MEGABYTE  1000000
#define SIZE_GIGABYTE  1000000000
#define SIZE_TERABYTE  1000000000000
#define SIZE_PETABYTE  1000000000000000
#define SIZE_EXABYTE   1000000000000000000
#define SIZE_ZETTABYTE 1000000000000000000000
#define SIZE_YOTTABYTE 1000000000000000000000000

TEST(FileSizeSI, constructor_without_passing_a_size)
{
    std::string formatted;

    ztd::FileSizeSI size;
    formatted = size.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "0 B"));
}

TEST(FileSizeSI, rand_sizes)
{
    std::string formatted;

    ztd::FileSizeSI size01(4488998912);
    formatted = size01.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "4.5 GB"));

    ztd::FileSizeSI size02(12544835584);
    formatted = size02.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "12.5 GB"));

    ztd::FileSizeSI size03(111031328768);
    formatted = size03.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "111.0 GB"));

    ztd::FileSizeSI size04(249008676864);
    formatted = size04.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "249.0 GB"));

    ztd::FileSizeSI size05(5973753856);
    formatted = size05.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "6.0 GB"));

    ztd::FileSizeSI size06(942819);
    formatted = size06.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "942.8 KB"));

    ztd::FileSizeSI size07(19260);
    formatted = size07.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "19.3 KB"));

    ztd::FileSizeSI size08(360);
    formatted = size08.get_formated_size();
    ASSERT_TRUE(ztd::same(formatted, "360 B"));
}

TEST(FileSizeSI, get_formated_size__int__B)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_BYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 B"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1 B"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1 B"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1 B"));
}

TEST(FileSizeSI, get_formated_size__int__KB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_KILOBYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 KB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 KB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 KB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 KB"));
}

TEST(FileSizeSI, get_formated_size__int__MB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_MEGABYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 MB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 MB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 MB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 MB"));
}

TEST(FileSizeSI, get_formated_size__int__GB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_GIGABYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 GB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 GB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 GB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 GB"));
}

TEST(FileSizeSI, get_formated_size__int__TB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_TERABYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 TB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 TB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 TB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 TB"));
}

TEST(FileSizeSI, get_formated_size__int__PB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_PETABYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 PB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 PB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 PB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 PB"));
}

TEST(FileSizeSI, get_formated_size__int__EB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_EXABYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 EB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 EB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 EB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 EB"));
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(FileSizeSI, get_formated_size__int__ZB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_ZETTABYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 ZB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 ZB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 ZB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 ZB"));
}

TEST(FileSizeSI, get_formated_size__int__YB)
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_YOTTABYTE);

    formatted = size.get_formated_size(0);
    ASSERT_TRUE(ztd::same(formatted, "1 YB"));

    formatted = size.get_formated_size(1);
    ASSERT_TRUE(ztd::same(formatted, "1.0 YB"));

    formatted = size.get_formated_size(2);
    ASSERT_TRUE(ztd::same(formatted, "1.00 YB"));

    formatted = size.get_formated_size(3);
    ASSERT_TRUE(ztd::same(formatted, "1.000 YB"));
}
#endif

TEST(FileSizeSI, get_filesize_parts_B)
{
    ztd::FileSizeSI size(SIZE_BYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "B");
}

TEST(FileSizeSI, get_filesize_parts_KB)
{
    ztd::FileSizeSI size(SIZE_KILOBYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "KB");
}

TEST(FileSizeSI, get_filesize_parts_MB)
{
    ztd::FileSizeSI size(SIZE_MEGABYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "MB");
}

TEST(FileSizeSI, get_filesize_parts_GB)
{
    ztd::FileSizeSI size(SIZE_GIGABYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "GB");
}

TEST(FileSizeSI, get_filesize_parts_TB)
{
    ztd::FileSizeSI size(SIZE_TERABYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "TB");
}

TEST(FileSizeSI, get_filesize_parts_PB)
{
    ztd::FileSizeSI size(SIZE_PETABYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "PB");
}

TEST(FileSizeSI, get_filesize_parts_EB)
{
    ztd::FileSizeSI size(SIZE_EXABYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "EB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(FileSizeSI, get_filesize_parts_ZB)
{
    ztd::FileSizeSI size(SIZE_ZETTABYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "ZB");
}

TEST(FileSizeSI, get_filesize_parts_YB)
{
    ztd::FileSizeSI size(SIZE_YOTTABYTE);
    auto parts = size.get_filesize_parts();
    ASSERT_TRUE(parts.first == 1.0);
    ASSERT_TRUE(parts.second == "YB");
}
#endif
