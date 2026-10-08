/**
 * Copyright (C) 2026 Brandon Zorn <brandonzorn@cock.li>
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

TEST_SUITE("ztd::byte_si functions")
{
    using namespace ztd::byte_si_literals;

    TEST_CASE("std::formatter ")
    {
        SUBCASE("basic")
        {
            CHECK(ztd::byte_iec(0ull).format() == "0 B");
            CHECK(std::format("{}", 0_B) == "0 B");
        }
    }

    TEST_CASE("size zero")
    {
        CHECK(ztd::byte_si(0ull).format() == "0 B");
        CHECK((0_B).format() == "0 B");
    }

    TEST_CASE("rand sizes")
    {
        std::string formatted;

        const auto size01 = ztd::byte_si{4488998912ull};
        formatted = size01.format();
        CHECK(formatted == "4.5 GB");

        const auto size02 = ztd::byte_si{12544835584ull};
        formatted = size02.format();
        CHECK(formatted == "12.5 GB");

        const auto size03 = ztd::byte_si{111031328768ull};
        formatted = size03.format();
        CHECK(formatted == "111.0 GB");

        const auto size04 = ztd::byte_si{249008676864ull};
        formatted = size04.format();
        CHECK(formatted == "249.0 GB");

        const auto size05 = ztd::byte_si{5973753856ull};
        formatted = size05.format();
        CHECK(formatted == "6.0 GB");

        const auto size06 = ztd::byte_si{942819ull};
        formatted = size06.format();
        CHECK(formatted == "942.8 kB");

        const auto size07 = ztd::byte_si{19260ull};
        formatted = size07.format();
        CHECK(formatted == "19.3 kB");

        const auto size08 = ztd::byte_si{360ull};
        formatted = size08.format();
        CHECK(formatted == "360 B");
    }

    TEST_CASE(".format()")
    {
        std::string formatted;

        SUBCASE("B")
        {
            const auto size = 1_B;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 B");

            formatted = size.format(1_u32);
            CHECK(formatted == "1 B");

            formatted = size.format(2_u32);
            CHECK(formatted == "1 B");

            formatted = size.format(3_u32);
            CHECK(formatted == "1 B");
        }

        SUBCASE("kB")
        {
            const auto size = 1_kB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 kB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 kB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 kB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 kB");
        }

        SUBCASE("MB")
        {
            const auto size = 1_MB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 MB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 MB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 MB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 MB");
        }

        SUBCASE("GB")
        {
            const auto size = 1_GB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 GB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 GB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 GB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 GB");
        }

        SUBCASE("TB")
        {
            const auto size = 1_TB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 TB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 TB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 TB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 TB");
        }

        SUBCASE("PB")
        {
            const auto size = 1_PB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 PB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 PB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 PB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 PB");
        }

        SUBCASE("EB")
        {
            const auto size = 1_EB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 EB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 EB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 EB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 EB");
        }
    }

    TEST_CASE(".is_*()")
    {
        SUBCASE("is_byte")
        {
            const auto size = 1_B;

            CHECK(size.is_byte());
            CHECK_FALSE(size.is_kilobyte());
            CHECK_FALSE(size.is_megabyte());
            CHECK_FALSE(size.is_gigabyte());
            CHECK_FALSE(size.is_terrabyte());
            CHECK_FALSE(size.is_petabyte());
            CHECK_FALSE(size.is_exabyte());
            CHECK_FALSE(size.is_zettabyte());
            CHECK_FALSE(size.is_yottabyte());
            CHECK_FALSE(size.is_ronnabyte());
            CHECK_FALSE(size.is_quettabyte());
        }

        SUBCASE("is_kilobyte")
        {
            const auto size = 1_kB;

            CHECK_FALSE(size.is_byte());
            CHECK(size.is_kilobyte());
            CHECK_FALSE(size.is_megabyte());
            CHECK_FALSE(size.is_gigabyte());
            CHECK_FALSE(size.is_terrabyte());
            CHECK_FALSE(size.is_petabyte());
            CHECK_FALSE(size.is_exabyte());
            CHECK_FALSE(size.is_zettabyte());
            CHECK_FALSE(size.is_yottabyte());
            CHECK_FALSE(size.is_ronnabyte());
            CHECK_FALSE(size.is_quettabyte());
        }

        SUBCASE("is_megabyte")
        {
            const auto size = 1_MB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kilobyte());
            CHECK(size.is_megabyte());
            CHECK_FALSE(size.is_gigabyte());
            CHECK_FALSE(size.is_terrabyte());
            CHECK_FALSE(size.is_petabyte());
            CHECK_FALSE(size.is_exabyte());
            CHECK_FALSE(size.is_zettabyte());
            CHECK_FALSE(size.is_yottabyte());
            CHECK_FALSE(size.is_ronnabyte());
            CHECK_FALSE(size.is_quettabyte());
        }

        SUBCASE("is_gigabyte")
        {
            const auto size = 1_GB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kilobyte());
            CHECK_FALSE(size.is_megabyte());
            CHECK(size.is_gigabyte());
            CHECK_FALSE(size.is_terrabyte());
            CHECK_FALSE(size.is_petabyte());
            CHECK_FALSE(size.is_exabyte());
            CHECK_FALSE(size.is_zettabyte());
            CHECK_FALSE(size.is_yottabyte());
            CHECK_FALSE(size.is_ronnabyte());
            CHECK_FALSE(size.is_quettabyte());
        }

        SUBCASE("is_terrabyte")
        {
            const auto size = 1_TB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kilobyte());
            CHECK_FALSE(size.is_megabyte());
            CHECK_FALSE(size.is_gigabyte());
            CHECK(size.is_terrabyte());
            CHECK_FALSE(size.is_petabyte());
            CHECK_FALSE(size.is_exabyte());
            CHECK_FALSE(size.is_zettabyte());
            CHECK_FALSE(size.is_yottabyte());
            CHECK_FALSE(size.is_ronnabyte());
            CHECK_FALSE(size.is_quettabyte());
        }

        SUBCASE("is_petabyte")
        {
            const auto size = 1_PB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kilobyte());
            CHECK_FALSE(size.is_megabyte());
            CHECK_FALSE(size.is_gigabyte());
            CHECK_FALSE(size.is_terrabyte());
            CHECK(size.is_petabyte());
            CHECK_FALSE(size.is_exabyte());
            CHECK_FALSE(size.is_zettabyte());
            CHECK_FALSE(size.is_yottabyte());
            CHECK_FALSE(size.is_ronnabyte());
            CHECK_FALSE(size.is_quettabyte());
        }

        SUBCASE("is_exabyte")
        {
            const auto size = 1_EB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kilobyte());
            CHECK_FALSE(size.is_megabyte());
            CHECK_FALSE(size.is_gigabyte());
            CHECK_FALSE(size.is_terrabyte());
            CHECK_FALSE(size.is_petabyte());
            CHECK(size.is_exabyte());
            CHECK_FALSE(size.is_zettabyte());
            CHECK_FALSE(size.is_yottabyte());
            CHECK_FALSE(size.is_ronnabyte());
            CHECK_FALSE(size.is_quettabyte());
        }
    }

    TEST_CASE("min/max")
    {
        const ztd::byte_si x = 1_kB;
        const ztd::byte_si y = 512_B;

        CHECK(x.max(y) == x);
        CHECK(x.min(y) == y);
    }

    TEST_CASE("as_iec")
    {
        const auto x = 1_MB;

        CHECK(x.as_iec() == ztd::byte_iec{x.data()});
        CHECK(x.as_iec().format() == ztd::byte_iec{x.data()}.format());
    }
}
