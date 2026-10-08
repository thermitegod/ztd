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

TEST_SUITE("ztd::byte_si literals")
{
    using namespace ztd::byte_si_literals;

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

        const auto d = 1000_B;
        CHECK(d.data() == 1000);
        CHECK_FALSE(d.is_byte());
    }

    TEST_CASE("kB")
    {
        const auto a = 1_kB;
        CHECK(a.data() == 1000);
        CHECK(a.is_kilobyte());

        const auto b = 100_kB;
        CHECK(b.data() == 100000);
        CHECK(b.is_kilobyte());

        const auto c = 500_kB;
        CHECK(c.data() == 500000);
        CHECK(c.is_kilobyte());

        const auto d = 1000_kB;
        CHECK(d.data() == 1000000);
        CHECK_FALSE(d.is_kilobyte());
    }

    TEST_CASE("MB")
    {
        const auto a = 1_MB;
        CHECK(a.data() == 1000000);
        CHECK(a.is_megabyte());

        const auto b = 100_MB;
        CHECK(b.data() == 100000000);
        CHECK(b.is_megabyte());

        const auto c = 500_MB;
        CHECK(c.data() == 500000000);
        CHECK(c.is_megabyte());

        const auto d = 1000_MB;
        CHECK(d.data() == 1000000000);
        CHECK_FALSE(d.is_megabyte());
    }

    TEST_CASE("GB")
    {
        const auto a = 1_GB;
        CHECK(a.data() == 1000000000);
        CHECK(a.is_gigabyte());

        const auto b = 100_GB;
        CHECK(b.data() == 100000000000);
        CHECK(b.is_gigabyte());

        const auto c = 500_GB;
        CHECK(c.data() == 500000000000);
        CHECK(c.is_gigabyte());

        const auto d = 1000_GB;
        CHECK(d.data() == 1000000000000);
        CHECK_FALSE(d.is_gigabyte());
    }

    TEST_CASE("TB")
    {
        const auto a = 1_TB;
        CHECK(a.data() == 1000000000000);
        CHECK(a.is_terrabyte());

        const auto b = 100_TB;
        CHECK(b.data() == 100000000000000);
        CHECK(b.is_terrabyte());

        const auto c = 500_TB;
        CHECK(c.data() == 500000000000000);
        CHECK(c.is_terrabyte());

        const auto d = 1000_TB;
        CHECK(d.data() == 1000000000000000);
        CHECK_FALSE(d.is_terrabyte());
    }

    TEST_CASE("PB")
    {
        const auto a = 1_PB;
        CHECK(a.data() == 1000000000000000);
        CHECK(a.is_petabyte());

        const auto b = 100_PB;
        CHECK(b.data() == 100000000000000000);
        CHECK(b.is_petabyte());

        const auto c = 500_PB;
        CHECK(c.data() == 500000000000000000);
        CHECK(c.is_petabyte());

        const auto d = 1000_PB;
        CHECK(d.data() == 1000000000000000000);
        CHECK_FALSE(d.is_petabyte());
    }

    TEST_CASE("EB")
    {
        const auto a = 1_EB;
        CHECK(a.data() == 1000000000000000000);
        CHECK(a.is_exabyte());

#ifdef NO_VERY_LARGE_INT_TYPE
        const auto b = 100_EB;
        CHECK(b.data() == 100000000000000000000);
        CHECK(b.is_exabyte());

        const auto c = 500_EB;
        CHECK(c.data() == 500000000000000000000);
        CHECK(c.is_exabyte());

        const auto d = 1000_EB;
        CHECK(d.data() == 1000000000000000000000);
        CHECK_FALSE(d.is_exabyte());
#endif
    }
}
