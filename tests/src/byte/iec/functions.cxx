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

#include <format>

#include <doctest/doctest.h>

#include "byte/iec/utils.hxx"
#include "ztd/detail/byte_size.hxx"

TEST_SUITE("ztd::byte_iec functions")
{
    using namespace ztd::byte_iec_literals;

    TEST_CASE("std::formatter")
    {
        SUBCASE("basic")
        {
            CHECK(ztd::byte_iec(0ull).format() == "0 B");
            CHECK(std::format("{}", 0_B) == "0 B");
        }
    }

    TEST_CASE("size zero")
    {
        CHECK(ztd::byte_iec(0ull).format() == "0 B");
        CHECK((0_B).format() == "0 B");
    }

    TEST_CASE("rand sizes")
    {
        std::string formatted;

        const auto size01 = ztd::byte_iec{4488998912ull};
        formatted = size01.format();
        CHECK(formatted == "4.2 GiB");

        const auto size02 = ztd::byte_iec{12544835584ull};
        formatted = size02.format();
        CHECK(formatted == "11.7 GiB");

        const auto size03 = ztd::byte_iec{111031328768ull};
        formatted = size03.format();
        CHECK(formatted == "103.4 GiB");

        const auto size04 = ztd::byte_iec{249008676864ull};
        formatted = size04.format();
        CHECK(formatted == "231.9 GiB");

        const auto size05 = ztd::byte_iec{5973753856ull};
        formatted = size05.format();
        CHECK(formatted == "5.6 GiB");

        const auto size06 = ztd::byte_iec{942819ull};
        formatted = size06.format();
        CHECK(formatted == "920.7 KiB");

        const auto size07 = ztd::byte_iec{19260ull};
        formatted = size07.format();
        CHECK(formatted == "18.8 KiB");

        const auto size08 = ztd::byte_iec{360ull};
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

        SUBCASE("KiB")
        {
            const auto size = 1_KiB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 KiB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 KiB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 KiB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 KiB");
        }

        SUBCASE("MiB")
        {
            const auto size = 1_MiB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 MiB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 MiB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 MiB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 MiB");
        }

        SUBCASE("GiB")
        {
            const auto size = 1_GiB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 GiB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 GiB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 GiB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 GiB");
        }

        SUBCASE("TiB")
        {
            const auto size = 1_TiB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 TiB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 TiB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 TiB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 TiB");
        }

        SUBCASE("PiB")
        {
            const auto size = 1_PiB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 PiB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 PiB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 PiB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 PiB");
        }

        SUBCASE("EiB")
        {
            const auto size = 1_EiB;

            formatted = size.format(0_u32);
            CHECK(formatted == "1 EiB");

            formatted = size.format(1_u32);
            CHECK(formatted == "1.0 EiB");

            formatted = size.format(2_u32);
            CHECK(formatted == "1.00 EiB");

            formatted = size.format(3_u32);
            CHECK(formatted == "1.000 EiB");
        }
    }

    TEST_CASE(".is_*()")
    {
        SUBCASE("is_byte")
        {
            const auto size = 1_B;

            CHECK(size.is_byte());
            CHECK_FALSE(size.is_kibibyte());
            CHECK_FALSE(size.is_mebibyte());
            CHECK_FALSE(size.is_gibibyte());
            CHECK_FALSE(size.is_tebibyte());
            CHECK_FALSE(size.is_pebibyte());
            CHECK_FALSE(size.is_exbibyte());
            CHECK_FALSE(size.is_zebibyte());
            CHECK_FALSE(size.is_yobibyte());
            CHECK_FALSE(size.is_robibyte());
            CHECK_FALSE(size.is_qubibyte());
        }

        SUBCASE("is_kibibyte")
        {
            const auto size = 1_KiB;

            CHECK_FALSE(size.is_byte());
            CHECK(size.is_kibibyte());
            CHECK_FALSE(size.is_mebibyte());
            CHECK_FALSE(size.is_gibibyte());
            CHECK_FALSE(size.is_tebibyte());
            CHECK_FALSE(size.is_pebibyte());
            CHECK_FALSE(size.is_exbibyte());
            CHECK_FALSE(size.is_zebibyte());
            CHECK_FALSE(size.is_yobibyte());
            CHECK_FALSE(size.is_robibyte());
            CHECK_FALSE(size.is_qubibyte());
        }

        SUBCASE("is_mebibyte")
        {
            const auto size = 1_MiB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kibibyte());
            CHECK(size.is_mebibyte());
            CHECK_FALSE(size.is_gibibyte());
            CHECK_FALSE(size.is_tebibyte());
            CHECK_FALSE(size.is_pebibyte());
            CHECK_FALSE(size.is_exbibyte());
            CHECK_FALSE(size.is_zebibyte());
            CHECK_FALSE(size.is_yobibyte());
            CHECK_FALSE(size.is_robibyte());
            CHECK_FALSE(size.is_qubibyte());
        }

        SUBCASE("is_gibibyte")
        {
            const auto size = 1_GiB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kibibyte());
            CHECK_FALSE(size.is_mebibyte());
            CHECK(size.is_gibibyte());
            CHECK_FALSE(size.is_tebibyte());
            CHECK_FALSE(size.is_pebibyte());
            CHECK_FALSE(size.is_exbibyte());
            CHECK_FALSE(size.is_zebibyte());
            CHECK_FALSE(size.is_yobibyte());
            CHECK_FALSE(size.is_robibyte());
            CHECK_FALSE(size.is_qubibyte());
        }

        SUBCASE("is_tebibyte")
        {
            const auto size = 1_TiB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kibibyte());
            CHECK_FALSE(size.is_mebibyte());
            CHECK_FALSE(size.is_gibibyte());
            CHECK(size.is_tebibyte());
            CHECK_FALSE(size.is_pebibyte());
            CHECK_FALSE(size.is_exbibyte());
            CHECK_FALSE(size.is_zebibyte());
            CHECK_FALSE(size.is_yobibyte());
            CHECK_FALSE(size.is_robibyte());
            CHECK_FALSE(size.is_qubibyte());
        }

        SUBCASE("is_pebibyte")
        {
            const auto size = 1_PiB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kibibyte());
            CHECK_FALSE(size.is_mebibyte());
            CHECK_FALSE(size.is_gibibyte());
            CHECK_FALSE(size.is_tebibyte());
            CHECK(size.is_pebibyte());
            CHECK_FALSE(size.is_exbibyte());
            CHECK_FALSE(size.is_zebibyte());
            CHECK_FALSE(size.is_yobibyte());
            CHECK_FALSE(size.is_robibyte());
            CHECK_FALSE(size.is_qubibyte());
        }

        SUBCASE("is_exbibyte")
        {
            const auto size = 1_EiB;

            CHECK_FALSE(size.is_byte());
            CHECK_FALSE(size.is_kibibyte());
            CHECK_FALSE(size.is_mebibyte());
            CHECK_FALSE(size.is_gibibyte());
            CHECK_FALSE(size.is_tebibyte());
            CHECK_FALSE(size.is_pebibyte());
            CHECK(size.is_exbibyte());
            CHECK_FALSE(size.is_zebibyte());
            CHECK_FALSE(size.is_yobibyte());
            CHECK_FALSE(size.is_robibyte());
            CHECK_FALSE(size.is_qubibyte());
        }
    }

    TEST_CASE("min/max")
    {
        const ztd::byte_iec x = 1_KiB;
        const ztd::byte_iec y = 512_B;

        CHECK(x.max(y) == x);
        CHECK(x.min(y) == y);
    }

    TEST_CASE("as_si")
    {
        const ztd::byte_iec x = 1_MiB;

        CHECK(x.as_si() == ztd::byte_si{x.data()});
        CHECK(x.as_si().format() == ztd::byte_si{x.data()}.format());
    }
}
