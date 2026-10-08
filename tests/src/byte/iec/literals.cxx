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

#include "ztd/detail/byte_size.hxx"

TEST_SUITE("ztd::byte_iec literals")
{
    using namespace ztd::byte_iec_literals;

    TEST_CASE("B")
    {
        const auto a = 1_B;
        CHECK(a.data() == 1);
        CHECK(a.is_byte());

        const auto b = 100_B;
        CHECK(b.data() == 100);
        CHECK(b.is_byte());

        const auto c = 500_B;
        CHECK(c.data() == 500);
        CHECK(c.is_byte());

        const auto d = 1024_B;
        CHECK(d.data() == 1024);
        CHECK_FALSE(d.is_byte());
    }

    TEST_CASE("KiB")
    {
        const auto a = 1_KiB;
        CHECK(a.data() == 1024);
        CHECK(a.is_kibibyte());

        const auto b = 100_KiB;
        CHECK(b.data() == 102400);
        CHECK(b.is_kibibyte());

        const auto c = 500_KiB;
        CHECK(c.data() == 512000);
        CHECK(c.is_kibibyte());

        const auto d = 1024_KiB;
        CHECK(d.data() == 1048576);
        CHECK_FALSE(d.is_kibibyte());
    }

    TEST_CASE("MiB")
    {
        const auto a = 1_MiB;
        CHECK(a.data() == 1048576);
        CHECK(a.is_mebibyte());

        const auto b = 100_MiB;
        CHECK(b.data() == 104857600);
        CHECK(b.is_mebibyte());

        const auto c = 500_MiB;
        CHECK(c.data() == 524288000);
        CHECK(c.is_mebibyte());

        const auto d = 1024_MiB;
        CHECK(d.data() == 1073741824);
        CHECK_FALSE(d.is_mebibyte());
    }

    TEST_CASE("GiB")
    {
        const auto a = 1_GiB;
        CHECK(a.data() == 1073741824);
        CHECK(a.is_gibibyte());

        const auto b = 100_GiB;
        CHECK(b.data() == 107374182400);
        CHECK(b.is_gibibyte());

        const auto c = 500_GiB;
        CHECK(c.data() == 536870912000);
        CHECK(c.is_gibibyte());

        const auto d = 1024_GiB;
        CHECK(d.data() == 1099511627776);
        CHECK_FALSE(d.is_gibibyte());
    }

    TEST_CASE("TiB")
    {
        const auto a = 1_TiB;
        CHECK(a.data() == 1099511627776);
        CHECK(a.is_tebibyte());

        const auto b = 100_TiB;
        CHECK(b.data() == 109951162777600);
        CHECK(b.is_tebibyte());

        const auto c = 500_TiB;
        CHECK(c.data() == 549755813888000);
        CHECK(c.is_tebibyte());

        const auto d = 1024_TiB;
        CHECK(d.data() == 1125899906842624);
        CHECK_FALSE(d.is_tebibyte());
    }

    TEST_CASE("PiB")
    {
        const auto a = 1_PiB;
        CHECK(a.data() == 1125899906842624);
        CHECK(a.is_pebibyte());

        const auto b = 100_PiB;
        CHECK(b.data() == 112589990684262400);
        CHECK(b.is_pebibyte());

        const auto c = 500_PiB;
        CHECK(c.data() == 562949953421312000);
        CHECK(c.is_pebibyte());

        const auto d = 1024_PiB;
        CHECK(d.data() == 1152921504606846976);
        CHECK_FALSE(d.is_pebibyte());
    }

    TEST_CASE("EiB")
    {
        const auto a = 1_EiB;
        CHECK(a.data() == 1152921504606846976);
        CHECK(a.is_exbibyte());

#ifdef NO_VERY_LARGE_INT_TYPE
        const auto b = 100_EiB;
        CHECK(b.data() == 115292150460684697600);
        CHECK(b.is_exbibyte());

        const auto c = 500_EiB;
        CHECK(c.data() == 576460752303423488000);
        CHECK(c.is_exbibyte());

        const auto d = 1024_EiB;
        CHECK(d.data() == 1180591620717411303424);
        CHECK_FALSE(d.is_exbibyte());
#endif
    }
}
