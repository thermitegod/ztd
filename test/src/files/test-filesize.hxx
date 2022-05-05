/**
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

#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include "../../../src/ztd-files.hxx"

/**
 * Zettabyte and Yottabyte support is disabled because there are no
 * integer types large enough to hold their size in bytes.
 * They can be enabled when the C++ standard has uint128_t.
 */
#define NO_VERY_LARGE_INT_TYPE

/**
 * Byte        1
 */
#define SIZE_BYTE 1

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
 */
#define SIZE_KIBIBYTE 1024
#define SIZE_MEBIBYTE 1048576
#define SIZE_GIBIBYTE 1073741824
#define SIZE_TEBIBYTE 1099511627776
#define SIZE_PEBIBYTE 1125899906842624
#define SIZE_EXBIBYTE 1152921504606846976
#define SIZE_ZEBIBYTE 1180591620717411303424
#define SIZE_YOBIBYTE 1208925819614629174706176

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
#define SIZE_KILOBYTE  1000
#define SIZE_MEGABYTE  1000000
#define SIZE_GIGABYTE  1000000000
#define SIZE_TERABYTE  1000000000000
#define SIZE_PETABYTE  1000000000000000
#define SIZE_EXABYTE   1000000000000000000
#define SIZE_ZETTABYTE 1000000000000000000000
#define SIZE_YOTTABYTE 1000000000000000000000000

TEST_CASE("::FileSize without passing a size")
{
    std::string formatted;

    ztd::FileSize size;
    formatted = size.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "0 B"));
}

TEST_CASE("::FileSizeSI without passing a size")
{
    std::string formatted;

    ztd::FileSizeSI size;
    formatted = size.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "0 B"));
}

TEST_CASE("::FileSize base 2")
{
    std::string formatted;

    ztd::FileSize size01(4488998912);
    formatted = size01.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "4.2 GiB"));

    ztd::FileSize size02(12544835584);
    formatted = size02.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "11.7 GiB"));

    ztd::FileSize size03(111031328768);
    formatted = size03.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "103.4 GiB"));

    ztd::FileSize size04(249008676864);
    formatted = size04.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "231.9 GiB"));

    ztd::FileSize size05(5973753856);
    formatted = size05.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "5.6 GiB"));

    ztd::FileSize size06(942819);
    formatted = size06.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "920.7 KiB"));

    ztd::FileSize size07(19260);
    formatted = size07.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "18.8 KiB"));

    ztd::FileSize size08(360);
    formatted = size08.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "360 B"));
}

TEST_CASE("::FileSizeSI")
{
    std::string formatted;

    ztd::FileSizeSI size01(4488998912);
    formatted = size01.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "4.5 GB"));

    ztd::FileSizeSI size02(12544835584);
    formatted = size02.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "12.5 GB"));

    ztd::FileSizeSI size03(111031328768);
    formatted = size03.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "111.0 GB"));

    ztd::FileSizeSI size04(249008676864);
    formatted = size04.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "249.0 GB"));

    ztd::FileSizeSI size05(5973753856);
    formatted = size05.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "6.0 GB"));

    ztd::FileSizeSI size06(942819);
    formatted = size06.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "942.8 KB"));

    ztd::FileSizeSI size07(19260);
    formatted = size07.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "19.3 KB"));

    ztd::FileSizeSI size08(360);
    formatted = size08.get_formated_size();
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "360 B"));
}

/**
 * Byte        1
 * Kilobyte    1,024
 * Megabyte    1,048,576
 * Gigabyte    1,073,741,824
 * Terrabyte   1,099,511,627,776
 * Petabyte    1,125,899,906,842,624
 * Exabyte     1,152,921,504,606,846,976
 * Zettabyte   1,180,591,620,717,411,303,424
 * Yottabyte   1,208,925,819,614,629,174,706,176
 */
TEST_CASE("::FileSize get_formated_size B")
{
    std::string formatted;

    ztd::FileSize size(SIZE_BYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 B"));
}

TEST_CASE("::FileSize get_formated_size KiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_KIBIBYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 KiB"));
}

TEST_CASE("::FileSize get_formated_size MiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_MEBIBYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 MiB"));
}

TEST_CASE("::FileSize get_formated_size GiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_GIBIBYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 GiB"));
}

TEST_CASE("::FileSize get_formated_size TiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_TEBIBYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 TiB"));
}

TEST_CASE("::FileSize get_formated_size PiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_PEBIBYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 PiB"));
}

TEST_CASE("::FileSize get_formated_size EiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_EXBIBYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 EiB"));
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST_CASE("::FileSize get_formated_size ZiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_ZEBIBYTE);
    formatted = size.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 ZiB"));
}

TEST_CASE("::FileSize get_formated_size YiB")
{
    std::string formatted;

    ztd::FileSize size(SIZE_YOBIBYTE);
    formatted = size.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 YiB"));
}
#endif

TEST_CASE("::FileSizeSI get_formated_size B")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_BYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 B"));
}

TEST_CASE("::FileSizeSI get_formated_size KB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_KILOBYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 KB"));
}

TEST_CASE("::FileSizeSI get_formated_size MB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_MEGABYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 MB"));
}

TEST_CASE("::FileSizeSI get_formated_size GB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_GIGABYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 GB"));
}

TEST_CASE("::FileSizeSI get_formated_size TB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_TERABYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 TB"));
}

TEST_CASE("::FileSizeSI get_formated_size PB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_PETABYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 PB"));
}

TEST_CASE("::FileSizeSI get_formated_size EB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_EXABYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 EB"));
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST_CASE("::FileSizeSI get_formated_size ZB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_ZETTABYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 ZB"));
}

TEST_CASE("::FileSizeSI get_formated_size YB")
{
    std::string formatted;

    ztd::FileSizeSI size(SIZE_YOTTABYTE);
    formatted = size.get_formated_size(ztd::FileSizePrecision::PRECISION_0);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 YB"));
}
#endif

TEST_CASE("::FileSize get_filesize_parts B")
{
    ztd::FileSize size(SIZE_BYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "B");
}

TEST_CASE("::FileSize get_filesize_parts KiB")
{
    ztd::FileSize size(SIZE_KIBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "KiB");
}

TEST_CASE("::FileSize get_filesize_parts MiB")
{
    ztd::FileSize size(SIZE_MEBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "MiB");
}

TEST_CASE("::FileSize get_filesize_parts GiB")
{
    ztd::FileSize size(SIZE_GIBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "GiB");
}

TEST_CASE("::FileSize get_filesize_parts TiB")
{
    ztd::FileSize size(SIZE_TEBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "TiB");
}

TEST_CASE("::FileSize get_filesize_parts PiB")
{
    ztd::FileSize size(SIZE_PEBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "PiB");
}

TEST_CASE("::FileSize get_filesize_parts EiB")
{
    ztd::FileSize size(SIZE_EXBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "EiB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST_CASE("::FileSize get_filesize_parts ZiB")
{
    ztd::FileSize size(SIZE_ZEBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "ZiB");
}

TEST_CASE("::FileSize get_filesize_parts YiB")
{
    ztd::FileSize size(SIZE_YOBIBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "YiB");
}
#endif

TEST_CASE("::FileSizeSI get_filesize_parts B")
{
    ztd::FileSizeSI size(SIZE_BYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "B");
}

TEST_CASE("::FileSizeSI get_filesize_parts KB")
{
    ztd::FileSizeSI size(SIZE_KILOBYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "KB");
}

TEST_CASE("::FileSizeSI get_filesize_parts MB")
{
    ztd::FileSizeSI size(SIZE_MEGABYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "MB");
}

TEST_CASE("::FileSizeSI get_filesize_parts GB")
{
    ztd::FileSizeSI size(SIZE_GIGABYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "GB");
}

TEST_CASE("::FileSizeSI get_filesize_parts TB")
{
    ztd::FileSizeSI size(SIZE_TERABYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "TB");
}

TEST_CASE("::FileSizeSI get_filesize_parts PB")
{
    ztd::FileSizeSI size(SIZE_PETABYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "PB");
}

TEST_CASE("::FileSizeSI get_filesize_parts EB")
{
    ztd::FileSizeSI size(SIZE_EXABYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "EB");
}

#ifndef NO_VERY_LARGE_INT_TYPE
TEST_CASE("::FileSizeSI get_filesize_parts ZB")
{
    ztd::FileSizeSI size(SIZE_ZETTABYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "ZB");
}

TEST_CASE("::FileSizeSI get_filesize_parts YB")
{
    ztd::FileSizeSI size(SIZE_YOTTABYTE);
    auto parts = size.get_filesize_parts();
    REQUIRE(parts.first == 1.0);
    REQUIRE(parts.second == "YB");
}
#endif
