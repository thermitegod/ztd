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

#include "ztd/detail/byte_size.hxx"

TEST_SUITE("ztd::byte_iec literals" * doctest::description(""))
{
    using namespace ztd::byte_iec_literals;

    TEST_CASE("B")
    {
        const auto a = 1_B;
        CHECK_EQ(a.data(), 1);
        CHECK_EQ(a.is_byte(), true);

        const auto b = 100_B;
        CHECK_EQ(b.data(), 100);
        CHECK_EQ(b.is_byte(), true);

        const auto c = 500_B;
        CHECK_EQ(c.data(), 500);
        CHECK_EQ(c.is_byte(), true);

        const auto d = 1024_B;
        CHECK_EQ(d.data(), 1024);
        CHECK_EQ(d.is_byte(), false);
    }

    TEST_CASE("KiB")
    {
        const auto a = 1_KiB;
        CHECK_EQ(a.data(), 1024);
        CHECK_EQ(a.is_kibibyte(), true);

        const auto b = 100_KiB;
        CHECK_EQ(b.data(), 102400);
        CHECK_EQ(b.is_kibibyte(), true);

        const auto c = 500_KiB;
        CHECK_EQ(c.data(), 512000);
        CHECK_EQ(c.is_kibibyte(), true);

        const auto d = 1024_KiB;
        CHECK_EQ(d.data(), 1048576);
        CHECK_EQ(d.is_kibibyte(), false);
    }

    TEST_CASE("MiB")
    {
        const auto a = 1_MiB;
        CHECK_EQ(a.data(), 1048576);
        CHECK_EQ(a.is_mebibyte(), true);

        const auto b = 100_MiB;
        CHECK_EQ(b.data(), 104857600);
        CHECK_EQ(b.is_mebibyte(), true);

        const auto c = 500_MiB;
        CHECK_EQ(c.data(), 524288000);
        CHECK_EQ(c.is_mebibyte(), true);

        const auto d = 1024_MiB;
        CHECK_EQ(d.data(), 1073741824);
        CHECK_EQ(d.is_mebibyte(), false);
    }

    TEST_CASE("GiB")
    {
        const auto a = 1_GiB;
        CHECK_EQ(a.data(), 1073741824);
        CHECK_EQ(a.is_gibibyte(), true);

        const auto b = 100_GiB;
        CHECK_EQ(b.data(), 107374182400);
        CHECK_EQ(b.is_gibibyte(), true);

        const auto c = 500_GiB;
        CHECK_EQ(c.data(), 536870912000);
        CHECK_EQ(c.is_gibibyte(), true);

        const auto d = 1024_GiB;
        CHECK_EQ(d.data(), 1099511627776);
        CHECK_EQ(d.is_gibibyte(), false);
    }

    TEST_CASE("TiB")
    {
        const auto a = 1_TiB;
        CHECK_EQ(a.data(), 1099511627776);
        CHECK_EQ(a.is_tebibyte(), true);

        const auto b = 100_TiB;
        CHECK_EQ(b.data(), 109951162777600);
        CHECK_EQ(b.is_tebibyte(), true);

        const auto c = 500_TiB;
        CHECK_EQ(c.data(), 549755813888000);
        CHECK_EQ(c.is_tebibyte(), true);

        const auto d = 1024_TiB;
        CHECK_EQ(d.data(), 1125899906842624);
        CHECK_EQ(d.is_tebibyte(), false);
    }

    TEST_CASE("PiB")
    {
        const auto a = 1_PiB;
        CHECK_EQ(a.data(), 1125899906842624);
        CHECK_EQ(a.is_pebibyte(), true);

        const auto b = 100_PiB;
        CHECK_EQ(b.data(), 112589990684262400);
        CHECK_EQ(b.is_pebibyte(), true);

        const auto c = 500_PiB;
        CHECK_EQ(c.data(), 562949953421312000);
        CHECK_EQ(c.is_pebibyte(), true);

        const auto d = 1024_PiB;
        CHECK_EQ(d.data(), 1152921504606846976);
        CHECK_EQ(d.is_pebibyte(), false);
    }

    TEST_CASE("EiB")
    {
        const auto a = 1_EiB;
        CHECK_EQ(a.data(), 1152921504606846976);
        CHECK_EQ(a.is_exbibyte(), true);

#ifdef NO_VERY_LARGE_INT_TYPE
        const auto b = 100_EiB;
        CHECK_EQ(b.data(), 115292150460684697600);
        CHECK_EQ(b.is_exbibyte(), true);

        const auto c = 500_EiB;
        CHECK_EQ(c.data(), 576460752303423488000);
        CHECK_EQ(c.is_exbibyte(), true);

        const auto d = 1024_EiB;
        CHECK_EQ(d.data(), 1180591620717411303424);
        CHECK_EQ(d.is_exbibyte(), false);
#endif
    }
}
