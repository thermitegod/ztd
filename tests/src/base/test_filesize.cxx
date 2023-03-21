/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
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
 * Zettabyte, Yottabyte, Ronnabyte, and Quettabyte test support
 * is disabled because there are no integer types large enough to
 * hold their size in bytes. They can be enabled when the C++ standard
 * has std::uint128_t.
 */
#define NO_VERY_LARGE_INT_TYPE

/**
 * FileSize
 */

// clang-format off

/**
 * Byte        1
 * Kibibyte    1,024
 * Mebibyte    1,048,576
 * Gibibyte    1,073,741,824
 * Tebibyte    1,099,511,627,776
 * Pebibyte    1,125,899,906,842,624
 * Exbibyte    1,152,921,504,606,846,976
 * Zebibyte    1,180,591,620,717,411,303,424
 * Yobibyte    1,208,925,819,614,629,174,706,176
 * Robibyte    1,237,940,039,285,380,274,899,124,224
 * Qubibyte    1,267,650,600,228,229,401,496,703,205,376
 */
constexpr std::uint64_t SIZE_BYTE     = 1;
constexpr std::uint64_t SIZE_KIBIBYTE = 1024;
constexpr std::uint64_t SIZE_MEBIBYTE = 1048576;
constexpr std::uint64_t SIZE_GIBIBYTE = 1073741824;
constexpr std::uint64_t SIZE_TEBIBYTE = 1099511627776;
constexpr std::uint64_t SIZE_PEBIBYTE = 1125899906842624;
constexpr std::uint64_t SIZE_EXBIBYTE = 1152921504606846976;

#ifndef NO_VERY_LARGE_INT_TYPE
constexpr std::uint64_t SIZE_ZEBIBYTE = 1180591620717411303424;
constexpr std::uint64_t SIZE_YOBIBYTE = 1208925819614629174706176;
constexpr std::uint64_t SIZE_ROBIBYTE = 1237940039285380274899124224;
constexpr std::uint64_t SIZE_QUBIBYTE = 1267650600228229401496703205376;
#endif

// clang-format on

TEST(FileSize, size_zero)
{
    std::string formatted;

    const auto size = ztd::FileSize(0);
    formatted = size.get_formated_size();
    EXPECT_EQ(formatted, "0 B");
}

TEST(FileSize, rand_sizes)
{
    std::string formatted;

    const auto size01 = ztd::FileSize(4488998912);
    formatted = size01.get_formated_size();
    EXPECT_EQ(formatted, "4.2 GiB");

    const auto size02 = ztd::FileSize(12544835584);
    formatted = size02.get_formated_size();
    EXPECT_EQ(formatted, "11.7 GiB");

    const auto size03 = ztd::FileSize(111031328768);
    formatted = size03.get_formated_size();
    EXPECT_EQ(formatted, "103.4 GiB");

    const auto size04 = ztd::FileSize(249008676864);
    formatted = size04.get_formated_size();
    EXPECT_EQ(formatted, "231.9 GiB");

    const auto size05 = ztd::FileSize(5973753856);
    formatted = size05.get_formated_size();
    EXPECT_EQ(formatted, "5.6 GiB");

    const auto size06 = ztd::FileSize(942819);
    formatted = size06.get_formated_size();
    EXPECT_EQ(formatted, "920.7 KiB");

    const auto size07 = ztd::FileSize(19260);
    formatted = size07.get_formated_size();
    EXPECT_EQ(formatted, "18.8 KiB");

    const auto size08 = ztd::FileSize(360);
    formatted = size08.get_formated_size();
    EXPECT_EQ(formatted, "360 B");
}

TEST(FileSize, get_formated_size__B)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_BYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1 B");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1 B");
}

TEST(FileSize, get_formated_size__KiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_KIBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 KiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 KiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 KiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 KiB");
}

TEST(FileSize, get_formated_size__MiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_MEBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 MiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 MiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 MiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 MiB");
}

TEST(FileSize, get_formated_size__GiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_GIBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 GiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 GiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 GiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 GiB");
}

TEST(FileSize, get_formated_size__TiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_TEBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 TiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 TiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 TiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 TiB");
}

TEST(FileSize, get_formated_size__PiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_PEBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 PiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 PiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 PiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 PiB");
}

TEST(FileSize, get_formated_size__EiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_EXBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 EiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 EiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 EiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 EiB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(FileSize, get_formated_size__ZiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_ZEBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 ZiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 ZiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 ZiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 ZiB");
}

TEST(FileSize, get_formated_size__YiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_YOBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 YiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 YiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 YiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 YiB");
}

TEST(FileSize, get_formated_size__RiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_ROBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 RiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 RiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 RiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 RiB");
}

TEST(FileSize, get_formated_size__QiB)
{
    std::string formatted;

    const auto size = ztd::FileSize(SIZE_QUBIBYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 QiB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 QiB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 QiB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 QiB");
}
#endif

TEST(FileSize, get_filesize_parts_B)
{
    const auto size = ztd::FileSize(SIZE_BYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "B");
}

TEST(FileSize, get_filesize_parts_KiB)
{
    const auto size = ztd::FileSize(SIZE_KIBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "KiB");
}

TEST(FileSize, get_filesize_parts_MiB)
{
    const auto size = ztd::FileSize(SIZE_MEBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "MiB");
}

TEST(FileSize, get_filesize_parts_GiB)
{
    const auto size = ztd::FileSize(SIZE_GIBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "GiB");
}

TEST(FileSize, get_filesize_parts_TiB)
{
    const auto size = ztd::FileSize(SIZE_TEBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "TiB");
}

TEST(FileSize, get_filesize_parts_PiB)
{
    const auto size = ztd::FileSize(SIZE_PEBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "PiB");
}

TEST(FileSize, get_filesize_parts_EiB)
{
    const auto size = ztd::FileSize(SIZE_EXBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "EiB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(FileSize, get_filesize_parts_ZiB)
{
    const auto size = ztd::FileSize(SIZE_ZEBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "ZiB");
}

TEST(FileSize, get_filesize_parts_YiB)
{
    const auto size = ztd::FileSize(SIZE_YOBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "YiB");
}

TEST(FileSize, get_filesize_parts_RiB)
{
    const auto size = ztd::FileSize(SIZE_ROBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "RiB");
}

TEST(FileSize, get_filesize_parts_QiB)
{
    const auto size = ztd::FileSize(SIZE_QUBIBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "QiB");
}
#endif

/**
 * is_*()
 */

TEST(FileSize, is_byte)
{
    const auto size = ztd::FileSize(SIZE_BYTE);

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

TEST(FileSize, is_kilobyte)
{
    const auto size = ztd::FileSize(SIZE_KIBIBYTE);

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

TEST(FileSize, is_megabyte)
{
    const auto size = ztd::FileSize(SIZE_MEBIBYTE);

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

TEST(FileSize, is_gigabyte)
{
    const auto size = ztd::FileSize(SIZE_GIBIBYTE);

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

TEST(FileSize, is_terrabyte)
{
    const auto size = ztd::FileSize(SIZE_TEBIBYTE);

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

TEST(FileSize, is_petabyte)
{
    const auto size = ztd::FileSize(SIZE_PEBIBYTE);

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

TEST(FileSize, is_exabyte)
{
    const auto size = ztd::FileSize(SIZE_EXBIBYTE);

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
TEST(FileSize, is_zettabyte)
{
    const auto size = ztd::FileSize(SIZE_ZEBIBYTE);

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

TEST(FileSize, is_yottabyte)
{
    const auto size = ztd::FileSize(SIZE_YOBIBYTE);

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

TEST(FileSize, is_ronnabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_ROBIBYTE);

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

TEST(FileSize, is_quettabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_QUBIBYTE);

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
 * is_*() alias
 */

TEST(FileSize, is_kibibyte)
{
    const auto size = ztd::FileSize(SIZE_KIBIBYTE);

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

TEST(FileSize, is_mebibyte)
{
    const auto size = ztd::FileSize(SIZE_MEBIBYTE);

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

TEST(FileSize, is_gibibyte)
{
    const auto size = ztd::FileSize(SIZE_GIBIBYTE);

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

TEST(FileSize, is_tebibyte)
{
    const auto size = ztd::FileSize(SIZE_TEBIBYTE);

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

TEST(FileSize, is_pebibyte)
{
    const auto size = ztd::FileSize(SIZE_PEBIBYTE);

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

TEST(FileSize, is_exbibyte)
{
    const auto size = ztd::FileSize(SIZE_EXBIBYTE);

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
TEST(FileSize, is_zebibyte)
{
    const auto size = ztd::FileSize(SIZE_ZEBIBYTE);

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

TEST(FileSize, is_yobibyte)
{
    const auto size = ztd::FileSize(SIZE_YOBIBYTE);

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

TEST(FileSize, is_robibyte)
{
    const auto size = ztd::FileSize(SIZE_ROBIBYTE);

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

TEST(FileSize, is_qubibyte)
{
    const auto size = ztd::FileSize(SIZE_QUBIBYTE);

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
 * FileSizeSI
 */

// clang-format off

/**
 * Byte         1
 * Kilobyte     1,000
 * Megabyte     1,000,000
 * Gigabyte     1,000,000,000
 * Terrabyte    1,000,000,000,000
 * Petabyte     1,000,000,000,000,000
 * Exabyte      1,000,000,000,000,000,000
 * Zettabyte    1,000,000,000,000,000,000,000
 * Yottabyte    1,000,000,000,000,000,000,000,000
 * Ronnabyte    1,000,000,000,000,000,000,000,000,000
 * Quettabyte   1,000,000,000,000,000,000,000,000,000,000
 */

// constexpr std::uint64_t SIZE_BYTE    = 1;
constexpr std::uint64_t SIZE_KILOBYTE   = 1000;
constexpr std::uint64_t SIZE_MEGABYTE   = 1000000;
constexpr std::uint64_t SIZE_GIGABYTE   = 1000000000;
constexpr std::uint64_t SIZE_TERABYTE   = 1000000000000;
constexpr std::uint64_t SIZE_PETABYTE   = 1000000000000000;
constexpr std::uint64_t SIZE_EXABYTE    = 1000000000000000000;

#ifndef NO_VERY_LARGE_INT_TYPE
constexpr std::uint64_t SIZE_ZETTABYTE  = 1000000000000000000000;
constexpr std::uint64_t SIZE_YOTTABYTE  = 1000000000000000000000000;
constexpr std::uint64_t SIZE_RONNABYTE  = 1000000000000000000000000000;
constexpr std::uint64_t SIZE_QUETTABYTE = 1000000000000000000000000000000;
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

TEST(FileSizeSI, get_formated_size__B)
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

TEST(FileSizeSI, get_formated_size__KB)
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

TEST(FileSizeSI, get_formated_size__MB)
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

TEST(FileSizeSI, get_formated_size__GB)
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

TEST(FileSizeSI, get_formated_size__TB)
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

TEST(FileSizeSI, get_formated_size__PB)
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

TEST(FileSizeSI, get_formated_size__EB)
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
TEST(FileSizeSI, get_formated_size__ZB)
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

TEST(FileSizeSI, get_formated_size__YB)
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

TEST(FileSizeSI, get_formated_size__RB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_RONNABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 RB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 RB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 RB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 RB");
}

TEST(FileSizeSI, get_formated_size__QB)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_QUETTABYTE);

    formatted = size.get_formated_size(0);
    EXPECT_EQ(formatted, "1 QB");

    formatted = size.get_formated_size(1);
    EXPECT_EQ(formatted, "1.0 QB");

    formatted = size.get_formated_size(2);
    EXPECT_EQ(formatted, "1.00 QB");

    formatted = size.get_formated_size(3);
    EXPECT_EQ(formatted, "1.000 QB");
}
#endif

TEST(FileSizeSI, get_filesize_parts_B)
{
    const auto size = ztd::FileSizeSI(SIZE_BYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "B");
}

TEST(FileSizeSI, get_filesize_parts_KB)
{
    const auto size = ztd::FileSizeSI(SIZE_KILOBYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "KB");
}

TEST(FileSizeSI, get_filesize_parts_MB)
{
    const auto size = ztd::FileSizeSI(SIZE_MEGABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "MB");
}

TEST(FileSizeSI, get_filesize_parts_GB)
{
    const auto size = ztd::FileSizeSI(SIZE_GIGABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "GB");
}

TEST(FileSizeSI, get_filesize_parts_TB)
{
    const auto size = ztd::FileSizeSI(SIZE_TERABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "TB");
}

TEST(FileSizeSI, get_filesize_parts_PB)
{
    const auto size = ztd::FileSizeSI(SIZE_PETABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "PB");
}

TEST(FileSizeSI, get_filesize_parts_EB)
{
    const auto size = ztd::FileSizeSI(SIZE_EXABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "EB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(FileSizeSI, get_filesize_parts_ZB)
{
    const auto size = ztd::FileSizeSI(SIZE_ZETTABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "ZB");
}

TEST(FileSizeSI, get_filesize_parts_YB)
{
    const auto size = ztd::FileSizeSI(SIZE_YOTTABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "YB");
}

TEST(FileSizeSI, get_filesize_parts_RB)
{
    const auto size = ztd::FileSizeSI(SIZE_RONNABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "RB");
}

TEST(FileSizeSI, get_filesize_parts_QB)
{
    const auto size = ztd::FileSizeSI(SIZE_QUETTABYTE);
    const auto [filesize, label] = size.get_filesize_parts();
    EXPECT_EQ(filesize, 1.0);
    EXPECT_EQ(label, "QB");
}
#endif

/**
 * is_*()
 */

TEST(FileSizeSI, is_byte)
{
    const auto size = ztd::FileSizeSI(SIZE_BYTE);

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

TEST(FileSizeSI, is_kilobyte)
{
    const auto size = ztd::FileSizeSI(SIZE_KILOBYTE);

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

TEST(FileSizeSI, is_megabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_MEGABYTE);

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

TEST(FileSizeSI, is_gigabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_GIGABYTE);

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

TEST(FileSizeSI, is_terrabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_TERABYTE);

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

TEST(FileSizeSI, is_petabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_PETABYTE);

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

TEST(FileSizeSI, is_exabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_EXABYTE);

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
TEST(FileSizeSI, is_zettabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_ZETTABYTE);

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

TEST(FileSizeSI, is_yottabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_YOTTABYTE);

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

TEST(FileSizeSI, is_ronnabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_RONNABYTE);

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

TEST(FileSizeSI, is_quettabyte)
{
    const auto size = ztd::FileSizeSI(SIZE_QUETTABYTE);

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
 *
 * wrapper ztd::format_filesize()
 *
 */

/**
 * ztd::format_filesize ztd::format_base::IEC
 */

TEST(format_filesize, IEC__size_zero)
{
    const auto size = ztd::format_filesize(0, ztd::format_base::IEC);
    EXPECT_EQ(size, "0 B");
}

TEST(format_filesize, IEC__randsize)
{
    const auto size01 = ztd::format_filesize(4488998912, ztd::format_base::IEC);
    EXPECT_EQ(size01, "4.2 GiB");

    const auto size02 = ztd::format_filesize(12544835584, ztd::format_base::IEC);
    EXPECT_EQ(size02, "11.7 GiB");

    const auto size03 = ztd::format_filesize(111031328768, ztd::format_base::IEC);
    EXPECT_EQ(size03, "103.4 GiB");

    const auto size04 = ztd::format_filesize(249008676864, ztd::format_base::IEC);
    EXPECT_EQ(size04, "231.9 GiB");

    const auto size05 = ztd::format_filesize(5973753856, ztd::format_base::IEC);
    EXPECT_EQ(size05, "5.6 GiB");

    const auto size06 = ztd::format_filesize(942819, ztd::format_base::IEC);
    EXPECT_EQ(size06, "920.7 KiB");

    const auto size07 = ztd::format_filesize(19260, ztd::format_base::IEC);
    EXPECT_EQ(size07, "18.8 KiB");

    const auto size08 = ztd::format_filesize(360, ztd::format_base::IEC);
    EXPECT_EQ(size08, "360 B");
}

TEST(format_filesize, IEC__B)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 B");

    const auto formatted_1 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1 B");

    const auto formatted_2 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1 B");

    const auto formatted_3 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1 B");
}

TEST(format_filesize, IEC__KiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_KIBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 KiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_KIBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 KiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_KIBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 KiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_KIBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 KiB");
}

TEST(format_filesize, IEC__MiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_MEBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 MiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_MEBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 MiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_MEBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 MiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_MEBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 MiB");
}

TEST(format_filesize, IEC__GiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_GIBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 GiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_GIBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 GiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_GIBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 GiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_GIBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 GiB");
}

TEST(format_filesize, IEC__TiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_TEBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 TiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_TEBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 TiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_TEBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 TiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_TEBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 TiB");
}

TEST(format_filesize, IEC__PiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_PEBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 PiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_PEBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 PiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_PEBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 PiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_PEBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 PiB");
}

TEST(format_filesize, IEC__EiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_EXBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 EiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_EXBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 EiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_EXBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 EiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_EXBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 EiB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(format_filesize, IEC__ZiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_ZEBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 ZiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_ZEBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 ZiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_ZEBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 ZiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_ZEBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 ZiB");
}

TEST(format_filesize, IEC__YiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_YOBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 YiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_YOBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 YiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_YOBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 YiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_YOBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 YiB");
}

TEST(format_filesize, IEC__RiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_ROBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 RiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_ROBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 RiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_ROBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 RiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_ROBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 RiB");
}

TEST(format_filesize, IEC__QiB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_QUBIBYTE, ztd::format_base::IEC, 0);
    EXPECT_EQ(formatted_0, "1 QiB");

    const auto formatted_1 = ztd::format_filesize(SIZE_QUBIBYTE, ztd::format_base::IEC, 1);
    EXPECT_EQ(formatted_1, "1.0 QiB");

    const auto formatted_2 = ztd::format_filesize(SIZE_QUBIBYTE, ztd::format_base::IEC, 2);
    EXPECT_EQ(formatted_2, "1.00 QiB");

    const auto formatted_3 = ztd::format_filesize(SIZE_QUBIBYTE, ztd::format_base::IEC, 3);
    EXPECT_EQ(formatted_3, "1.000 QiB");
}
#endif

/**
 * ztd::format_filesize ztd::format_base::SI
 */

TEST(format_filesize, SI_size_zero)
{
    const auto size = ztd::format_filesize(0, ztd::format_base::SI);
    EXPECT_EQ(size, "0 B");
}

TEST(format_filesize, SI_rand_sizes)
{
    const auto size01 = ztd::format_filesize(4488998912, ztd::format_base::SI);
    EXPECT_EQ(size01, "4.5 GB");

    const auto size02 = ztd::format_filesize(12544835584, ztd::format_base::SI);
    EXPECT_EQ(size02, "12.5 GB");

    const auto size03 = ztd::format_filesize(111031328768, ztd::format_base::SI);
    EXPECT_EQ(size03, "111.0 GB");

    const auto size04 = ztd::format_filesize(249008676864, ztd::format_base::SI);
    EXPECT_EQ(size04, "249.0 GB");

    const auto size05 = ztd::format_filesize(5973753856, ztd::format_base::SI);
    EXPECT_EQ(size05, "6.0 GB");

    const auto size06 = ztd::format_filesize(942819, ztd::format_base::SI);
    EXPECT_EQ(size06, "942.8 KB");

    const auto size07 = ztd::format_filesize(19260, ztd::format_base::SI);
    EXPECT_EQ(size07, "19.3 KB");

    const auto size08 = ztd::format_filesize(360, ztd::format_base::SI);
    EXPECT_EQ(size08, "360 B");
}

TEST(format_filesize, SI__B)
{
    std::string formatted;

    const auto size = ztd::FileSizeSI(SIZE_BYTE);

    const auto formatted_0 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 B");

    const auto formatted_1 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_0, "1 B");

    const auto formatted_2 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_0, "1 B");

    const auto formatted_3 = ztd::format_filesize(SIZE_BYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_0, "1 B");
}

TEST(format_filesize, SI__KB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_KILOBYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 KB");

    const auto formatted_1 = ztd::format_filesize(SIZE_KILOBYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 KB");

    const auto formatted_2 = ztd::format_filesize(SIZE_KILOBYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 KB");

    const auto formatted_3 = ztd::format_filesize(SIZE_KILOBYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 KB");
}

TEST(format_filesize, SI__MB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_MEGABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 MB");

    const auto formatted_1 = ztd::format_filesize(SIZE_MEGABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 MB");

    const auto formatted_2 = ztd::format_filesize(SIZE_MEGABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 MB");

    const auto formatted_3 = ztd::format_filesize(SIZE_MEGABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 MB");
}

TEST(format_filesize, SI__GB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_GIGABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 GB");

    const auto formatted_1 = ztd::format_filesize(SIZE_GIGABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 GB");

    const auto formatted_2 = ztd::format_filesize(SIZE_GIGABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 GB");

    const auto formatted_3 = ztd::format_filesize(SIZE_GIGABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 GB");
}

TEST(format_filesize, SI__TB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_TERABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 TB");

    const auto formatted_1 = ztd::format_filesize(SIZE_TERABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 TB");

    const auto formatted_2 = ztd::format_filesize(SIZE_TERABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 TB");

    const auto formatted_3 = ztd::format_filesize(SIZE_TERABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 TB");
}

TEST(format_filesize, SI__PB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_PETABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 PB");

    const auto formatted_1 = ztd::format_filesize(SIZE_PETABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 PB");

    const auto formatted_2 = ztd::format_filesize(SIZE_PETABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 PB");

    const auto formatted_3 = ztd::format_filesize(SIZE_PETABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 PB");
}

TEST(format_filesize, SI__EB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_EXABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 EB");

    const auto formatted_1 = ztd::format_filesize(SIZE_EXABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 EB");

    const auto formatted_2 = ztd::format_filesize(SIZE_EXABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 EB");

    const auto formatted_3 = ztd::format_filesize(SIZE_EXABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 EB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST(format_filesize, SI__ZB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_ZETTABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 ZB");

    const auto formatted_1 = ztd::format_filesize(SIZE_ZETTABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 ZB");

    const auto formatted_2 = ztd::format_filesize(SIZE_ZETTABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 ZB");

    const auto formatted_3 = ztd::format_filesize(SIZE_ZETTABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 ZB");
}

TEST(format_filesize, SI__YB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_YOTTABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 YB");

    const auto formatted_1 = ztd::format_filesize(SIZE_YOTTABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 YB");

    const auto formatted_2 = ztd::format_filesize(SIZE_YOTTABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 YB");

    const auto formatted_3 = ztd::format_filesize(SIZE_YOTTABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 YB");
}

TEST(format_filesize, SI__RB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_RONNABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 RB");

    const auto formatted_1 = ztd::format_filesize(SIZE_RONNABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 RB");

    const auto formatted_2 = ztd::format_filesize(SIZE_RONNABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 RB");

    const auto formatted_3 = ztd::format_filesize(SIZE_RONNABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 RB");
}

TEST(format_filesize, SI__QB)
{
    const auto formatted_0 = ztd::format_filesize(SIZE_QUETTABYTE, ztd::format_base::SI, 0);
    EXPECT_EQ(formatted_0, "1 QB");

    const auto formatted_1 = ztd::format_filesize(SIZE_QUETTABYTE, ztd::format_base::SI, 1);
    EXPECT_EQ(formatted_1, "1.0 QB");

    const auto formatted_2 = ztd::format_filesize(SIZE_QUETTABYTE, ztd::format_base::SI, 2);
    EXPECT_EQ(formatted_2, "1.00 QB");

    const auto formatted_3 = ztd::format_filesize(SIZE_QUETTABYTE, ztd::format_base::SI, 3);
    EXPECT_EQ(formatted_3, "1.000 QB");
}
#endif
