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
TEST_CASE("::FileSize all sizes")
{
    std::string formatted;
    ztd::FileSizePrecision precision = ztd::FileSizePrecision::PRECISION_0;

    ztd::FileSize size01(1);
    formatted = size01.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 B"));

    ztd::FileSize size02(1024);
    formatted = size02.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 KiB"));

    ztd::FileSize size03(1048576);
    formatted = size03.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 MiB"));

    ztd::FileSize size04(1073741824);
    formatted = size04.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 GiB"));

    ztd::FileSize size05(1099511627776);
    formatted = size05.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 TiB"));

    ztd::FileSize size06(1125899906842624);
    formatted = size06.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 PiB"));

    ztd::FileSize size07(1152921504606846976);
    formatted = size07.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 EiB"));

    /**
     * Zettabyte and Yottabyte are disabled because
     * their integer literal is too large to be
     * represented in any current integer type
     */

    // ztd::FileSize size08(1180591620717411303424);
    // formatted = size08.get_formated_size(precision);
    // INFO(formatted);
    // REQUIRE(ztd::same(formatted, "1 ZiB"));

    // ztd::FileSize size09(1208925819614629174706176);
    // formatted = size09.get_formated_size(precision);
    // INFO(formatted);
    // REQUIRE(ztd::same(formatted, "1 YiB"));
}

TEST_CASE("::FileSizeSI all sizes")
{
    std::string formatted;
    ztd::FileSizePrecision precision = ztd::FileSizePrecision::PRECISION_0;

    ztd::FileSizeSI size01(1);
    formatted = size01.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 B"));

    ztd::FileSizeSI size02(1000);
    formatted = size02.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 KB"));

    ztd::FileSizeSI size03(1000000);
    formatted = size03.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 MB"));

    ztd::FileSizeSI size04(1000000000);
    formatted = size04.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 GB"));

    ztd::FileSizeSI size05(1000000000000);
    formatted = size05.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 TB"));

    ztd::FileSizeSI size06(1000000000000000);
    formatted = size06.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 PB"));

    ztd::FileSizeSI size07(1000000000000000000);
    formatted = size07.get_formated_size(precision);
    INFO(formatted);
    REQUIRE(ztd::same(formatted, "1 EB"));

    /**
     * Zettabyte and Yottabyte are disabled because
     * their integer literal is too large to be
     * represented in any current integer type
     */

    // ztd::FileSizeSI size08(1000000000000000000000);
    // formatted = size08.get_formated_size(precision);
    // INFO(formatted);
    // REQUIRE(ztd::same(formatted, "1 ZiB"));

    // ztd::FileSizeSI size09(1000000000000000000000000);
    // formatted = size09.get_formated_size(precision);
    // INFO(formatted);
    // REQUIRE(ztd::same(formatted, "1 YiB"));
}
