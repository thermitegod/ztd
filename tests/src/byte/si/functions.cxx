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

#include <doctest/doctest.h>

#include "byte/si/utils.hxx"
#include "ztd/detail/byte_size.hxx"

TEST_SUITE("ztd::byte_si functions" * doctest::description(""))
{
    using namespace ztd::byte_si_literals;

    TEST_CASE("size zero")
    {
        const ztd::byte_si size = 0ull;
        const auto formatted = size.format();
        CHECK_EQ(formatted, "0 B");
    }

    TEST_CASE("rand sizes")
    {
        std::string formatted;

        const ztd::byte_si size01 = 4488998912ull;
        formatted = size01.format();
        CHECK_EQ(formatted, "4.5 GB");

        const ztd::byte_si size02 = 12544835584ull;
        formatted = size02.format();
        CHECK_EQ(formatted, "12.5 GB");

        const ztd::byte_si size03 = 111031328768ull;
        formatted = size03.format();
        CHECK_EQ(formatted, "111.0 GB");

        const ztd::byte_si size04 = 249008676864ull;
        formatted = size04.format();
        CHECK_EQ(formatted, "249.0 GB");

        const ztd::byte_si size05 = 5973753856ull;
        formatted = size05.format();
        CHECK_EQ(formatted, "6.0 GB");

        const ztd::byte_si size06 = 942819ull;
        formatted = size06.format();
        CHECK_EQ(formatted, "942.8 kB");

        const ztd::byte_si size07 = 19260ull;
        formatted = size07.format();
        CHECK_EQ(formatted, "19.3 kB");

        const ztd::byte_si size08 = 360ull;
        formatted = size08.format();
        CHECK_EQ(formatted, "360 B");
    }

    TEST_CASE(".format()")
    {
        std::string formatted;

        SUBCASE("B")
        {
            const auto size = 1_B;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 B");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1 B");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1 B");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1 B");
        }

        SUBCASE("kB")
        {
            const auto size = 1_kB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 kB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 kB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 kB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 kB");
        }

        SUBCASE("MB")
        {
            const auto size = 1_MB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 MB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 MB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 MB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 MB");
        }

        SUBCASE("GB")
        {
            const auto size = 1_GB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 GB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 GB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 GB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 GB");
        }

        SUBCASE("TB")
        {
            const auto size = 1_TB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 TB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 TB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 TB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 TB");
        }

        SUBCASE("PB")
        {
            const auto size = 1_PB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 PB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 PB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 PB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 PB");
        }

        SUBCASE("EB")
        {
            const auto size = 1_EB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 EB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 EB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 EB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 EB");
        }
    }

    TEST_CASE(".is_*()")
    {
        SUBCASE("is_byte")
        {
            const auto size = 1_B;

            CHECK_EQ(size.is_byte(), true);
            CHECK_EQ(size.is_kilobyte(), false);
            CHECK_EQ(size.is_megabyte(), false);
            CHECK_EQ(size.is_gigabyte(), false);
            CHECK_EQ(size.is_terrabyte(), false);
            CHECK_EQ(size.is_petabyte(), false);
            CHECK_EQ(size.is_exabyte(), false);
            CHECK_EQ(size.is_zettabyte(), false);
            CHECK_EQ(size.is_yottabyte(), false);
            CHECK_EQ(size.is_ronnabyte(), false);
            CHECK_EQ(size.is_quettabyte(), false);
        }

        SUBCASE("is_kibibyte")
        {
            const auto size = 1_kB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kilobyte(), true);
            CHECK_EQ(size.is_megabyte(), false);
            CHECK_EQ(size.is_gigabyte(), false);
            CHECK_EQ(size.is_terrabyte(), false);
            CHECK_EQ(size.is_petabyte(), false);
            CHECK_EQ(size.is_exabyte(), false);
            CHECK_EQ(size.is_zettabyte(), false);
            CHECK_EQ(size.is_yottabyte(), false);
            CHECK_EQ(size.is_ronnabyte(), false);
            CHECK_EQ(size.is_quettabyte(), false);
        }

        SUBCASE("is_mebibyte")
        {
            const auto size = 1_MB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kilobyte(), false);
            CHECK_EQ(size.is_megabyte(), true);
            CHECK_EQ(size.is_gigabyte(), false);
            CHECK_EQ(size.is_terrabyte(), false);
            CHECK_EQ(size.is_petabyte(), false);
            CHECK_EQ(size.is_exabyte(), false);
            CHECK_EQ(size.is_zettabyte(), false);
            CHECK_EQ(size.is_yottabyte(), false);
            CHECK_EQ(size.is_ronnabyte(), false);
            CHECK_EQ(size.is_quettabyte(), false);
        }

        SUBCASE("is_gibibyte")
        {
            const auto size = 1_GB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kilobyte(), false);
            CHECK_EQ(size.is_megabyte(), false);
            CHECK_EQ(size.is_gigabyte(), true);
            CHECK_EQ(size.is_terrabyte(), false);
            CHECK_EQ(size.is_petabyte(), false);
            CHECK_EQ(size.is_exabyte(), false);
            CHECK_EQ(size.is_zettabyte(), false);
            CHECK_EQ(size.is_yottabyte(), false);
            CHECK_EQ(size.is_ronnabyte(), false);
            CHECK_EQ(size.is_quettabyte(), false);
        }

        SUBCASE("is_tebibyte")
        {
            const auto size = 1_TB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kilobyte(), false);
            CHECK_EQ(size.is_megabyte(), false);
            CHECK_EQ(size.is_gigabyte(), false);
            CHECK_EQ(size.is_terrabyte(), true);
            CHECK_EQ(size.is_petabyte(), false);
            CHECK_EQ(size.is_exabyte(), false);
            CHECK_EQ(size.is_zettabyte(), false);
            CHECK_EQ(size.is_yottabyte(), false);
            CHECK_EQ(size.is_ronnabyte(), false);
            CHECK_EQ(size.is_quettabyte(), false);
        }

        SUBCASE("is_pebibyte")
        {
            const auto size = 1_PB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kilobyte(), false);
            CHECK_EQ(size.is_megabyte(), false);
            CHECK_EQ(size.is_gigabyte(), false);
            CHECK_EQ(size.is_terrabyte(), false);
            CHECK_EQ(size.is_petabyte(), true);
            CHECK_EQ(size.is_exabyte(), false);
            CHECK_EQ(size.is_zettabyte(), false);
            CHECK_EQ(size.is_yottabyte(), false);
            CHECK_EQ(size.is_ronnabyte(), false);
            CHECK_EQ(size.is_quettabyte(), false);
        }

        SUBCASE("is_exbibyte")
        {
            const auto size = 1_EB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kilobyte(), false);
            CHECK_EQ(size.is_megabyte(), false);
            CHECK_EQ(size.is_gigabyte(), false);
            CHECK_EQ(size.is_terrabyte(), false);
            CHECK_EQ(size.is_petabyte(), false);
            CHECK_EQ(size.is_exabyte(), true);
            CHECK_EQ(size.is_zettabyte(), false);
            CHECK_EQ(size.is_yottabyte(), false);
            CHECK_EQ(size.is_ronnabyte(), false);
            CHECK_EQ(size.is_quettabyte(), false);
        }
    }

    TEST_CASE("min/max")
    {
        const ztd::byte_si x = 1_kB;
        const ztd::byte_si y = 512_B;

        CHECK_EQ(x.max(y), x);
        CHECK_EQ(x.min(y), y);
    }
}
