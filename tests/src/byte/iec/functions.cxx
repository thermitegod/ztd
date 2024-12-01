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

#include "byte/iec/utils.hxx"

#include "ztd/detail/byte_size.hxx"

TEST_SUITE("ztd::byte_iec functions" * doctest::description(""))
{
    using namespace ztd::byte_iec_literals;

    TEST_CASE("size zero")
    {
        const ztd::byte_iec size = 0ull;
        const auto formatted = size.format();
        CHECK_EQ(formatted, "0 B");
    }

    TEST_CASE("rand sizes")
    {
        std::string formatted;

        const ztd::byte_iec size01 = 4488998912ull;
        formatted = size01.format();
        CHECK_EQ(formatted, "4.2 GiB");

        const ztd::byte_iec size02 = 12544835584ull;
        formatted = size02.format();
        CHECK_EQ(formatted, "11.7 GiB");

        const ztd::byte_iec size03 = 111031328768ull;
        formatted = size03.format();
        CHECK_EQ(formatted, "103.4 GiB");

        const ztd::byte_iec size04 = 249008676864ull;
        formatted = size04.format();
        CHECK_EQ(formatted, "231.9 GiB");

        const ztd::byte_iec size05 = 5973753856ull;
        formatted = size05.format();
        CHECK_EQ(formatted, "5.6 GiB");

        const ztd::byte_iec size06 = 942819ull;
        formatted = size06.format();
        CHECK_EQ(formatted, "920.7 KiB");

        const ztd::byte_iec size07 = 19260ull;
        formatted = size07.format();
        CHECK_EQ(formatted, "18.8 KiB");

        const ztd::byte_iec size08 = 360ull;
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

        SUBCASE("KiB")
        {
            const auto size = 1_KiB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 KiB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 KiB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 KiB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 KiB");
        }

        SUBCASE("MiB")
        {
            const auto size = 1_MiB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 MiB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 MiB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 MiB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 MiB");
        }

        SUBCASE("GiB")
        {
            const auto size = 1_GiB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 GiB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 GiB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 GiB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 GiB");
        }

        SUBCASE("TiB")
        {
            const auto size = 1_TiB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 TiB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 TiB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 TiB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 TiB");
        }

        SUBCASE("PiB")
        {
            const auto size = 1_PiB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 PiB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 PiB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 PiB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 PiB");
        }

        SUBCASE("EiB")
        {
            const auto size = 1_EiB;

            formatted = size.format(0);
            CHECK_EQ(formatted, "1 EiB");

            formatted = size.format(1);
            CHECK_EQ(formatted, "1.0 EiB");

            formatted = size.format(2);
            CHECK_EQ(formatted, "1.00 EiB");

            formatted = size.format(3);
            CHECK_EQ(formatted, "1.000 EiB");
        }
    }

    TEST_CASE(".is_*()")
    {
        SUBCASE("is_byte")
        {
            const auto size = 1_B;

            CHECK_EQ(size.is_byte(), true);
            CHECK_EQ(size.is_kibibyte(), false);
            CHECK_EQ(size.is_mebibyte(), false);
            CHECK_EQ(size.is_gibibyte(), false);
            CHECK_EQ(size.is_tebibyte(), false);
            CHECK_EQ(size.is_pebibyte(), false);
            CHECK_EQ(size.is_exbibyte(), false);
            CHECK_EQ(size.is_zebibyte(), false);
            CHECK_EQ(size.is_yobibyte(), false);
            CHECK_EQ(size.is_robibyte(), false);
            CHECK_EQ(size.is_qubibyte(), false);
        }

        SUBCASE("is_kibibyte")
        {
            const auto size = 1_KiB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kibibyte(), true);
            CHECK_EQ(size.is_mebibyte(), false);
            CHECK_EQ(size.is_gibibyte(), false);
            CHECK_EQ(size.is_tebibyte(), false);
            CHECK_EQ(size.is_pebibyte(), false);
            CHECK_EQ(size.is_exbibyte(), false);
            CHECK_EQ(size.is_zebibyte(), false);
            CHECK_EQ(size.is_yobibyte(), false);
            CHECK_EQ(size.is_robibyte(), false);
            CHECK_EQ(size.is_qubibyte(), false);
        }

        SUBCASE("is_mebibyte")
        {
            const auto size = 1_MiB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kibibyte(), false);
            CHECK_EQ(size.is_mebibyte(), true);
            CHECK_EQ(size.is_gibibyte(), false);
            CHECK_EQ(size.is_tebibyte(), false);
            CHECK_EQ(size.is_pebibyte(), false);
            CHECK_EQ(size.is_exbibyte(), false);
            CHECK_EQ(size.is_zebibyte(), false);
            CHECK_EQ(size.is_yobibyte(), false);
            CHECK_EQ(size.is_robibyte(), false);
            CHECK_EQ(size.is_qubibyte(), false);
        }

        SUBCASE("is_gibibyte")
        {
            const auto size = 1_GiB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kibibyte(), false);
            CHECK_EQ(size.is_mebibyte(), false);
            CHECK_EQ(size.is_gibibyte(), true);
            CHECK_EQ(size.is_tebibyte(), false);
            CHECK_EQ(size.is_pebibyte(), false);
            CHECK_EQ(size.is_exbibyte(), false);
            CHECK_EQ(size.is_zebibyte(), false);
            CHECK_EQ(size.is_yobibyte(), false);
            CHECK_EQ(size.is_robibyte(), false);
            CHECK_EQ(size.is_qubibyte(), false);
        }

        SUBCASE("is_tebibyte")
        {
            const auto size = 1_TiB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kibibyte(), false);
            CHECK_EQ(size.is_mebibyte(), false);
            CHECK_EQ(size.is_gibibyte(), false);
            CHECK_EQ(size.is_tebibyte(), true);
            CHECK_EQ(size.is_pebibyte(), false);
            CHECK_EQ(size.is_exbibyte(), false);
            CHECK_EQ(size.is_zebibyte(), false);
            CHECK_EQ(size.is_yobibyte(), false);
            CHECK_EQ(size.is_robibyte(), false);
            CHECK_EQ(size.is_qubibyte(), false);
        }

        SUBCASE("is_pebibyte")
        {
            const auto size = 1_PiB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kibibyte(), false);
            CHECK_EQ(size.is_mebibyte(), false);
            CHECK_EQ(size.is_gibibyte(), false);
            CHECK_EQ(size.is_tebibyte(), false);
            CHECK_EQ(size.is_pebibyte(), true);
            CHECK_EQ(size.is_exbibyte(), false);
            CHECK_EQ(size.is_zebibyte(), false);
            CHECK_EQ(size.is_yobibyte(), false);
            CHECK_EQ(size.is_robibyte(), false);
            CHECK_EQ(size.is_qubibyte(), false);
        }

        SUBCASE("is_exbibyte")
        {
            const auto size = 1_EiB;

            CHECK_EQ(size.is_byte(), false);
            CHECK_EQ(size.is_kibibyte(), false);
            CHECK_EQ(size.is_mebibyte(), false);
            CHECK_EQ(size.is_gibibyte(), false);
            CHECK_EQ(size.is_tebibyte(), false);
            CHECK_EQ(size.is_pebibyte(), false);
            CHECK_EQ(size.is_exbibyte(), true);
            CHECK_EQ(size.is_zebibyte(), false);
            CHECK_EQ(size.is_yobibyte(), false);
            CHECK_EQ(size.is_robibyte(), false);
            CHECK_EQ(size.is_qubibyte(), false);
        }
    }

    TEST_CASE("min/max")
    {
        const ztd::byte_iec x = 1_KiB;
        const ztd::byte_iec y = 512_B;

        CHECK_EQ(x.max(y), x);
        CHECK_EQ(x.min(y), y);
    }
}
