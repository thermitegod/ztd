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

TEST_SUITE("ztd::byte_si literals" * doctest::description(""))
{
    using namespace ztd::byte_si_literals;

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

        const auto d = 1000_B;
        CHECK_EQ(d.data(), 1000);
        CHECK_EQ(d.is_byte(), false);
    }

    TEST_CASE("kB")
    {
        const auto a = 1_kB;
        CHECK_EQ(a.data(), 1000);
        CHECK_EQ(a.is_kilobyte(), true);

        const auto b = 100_kB;
        CHECK_EQ(b.data(), 100000);
        CHECK_EQ(b.is_kilobyte(), true);

        const auto c = 500_kB;
        CHECK_EQ(c.data(), 500000);
        CHECK_EQ(c.is_kilobyte(), true);

        const auto d = 1000_kB;
        CHECK_EQ(d.data(), 1000000);
        CHECK_EQ(d.is_kilobyte(), false);
    }

    TEST_CASE("MB")
    {
        const auto a = 1_MB;
        CHECK_EQ(a.data(), 1000000);
        CHECK_EQ(a.is_megabyte(), true);

        const auto b = 100_MB;
        CHECK_EQ(b.data(), 100000000);
        CHECK_EQ(b.is_megabyte(), true);

        const auto c = 500_MB;
        CHECK_EQ(c.data(), 500000000);
        CHECK_EQ(c.is_megabyte(), true);

        const auto d = 1000_MB;
        CHECK_EQ(d.data(), 1000000000);
        CHECK_EQ(d.is_megabyte(), false);
    }

    TEST_CASE("GB")
    {
        const auto a = 1_GB;
        CHECK_EQ(a.data(), 1000000000);
        CHECK_EQ(a.is_gigabyte(), true);

        const auto b = 100_GB;
        CHECK_EQ(b.data(), 100000000000);
        CHECK_EQ(b.is_gigabyte(), true);

        const auto c = 500_GB;
        CHECK_EQ(c.data(), 500000000000);
        CHECK_EQ(c.is_gigabyte(), true);

        const auto d = 1000_GB;
        CHECK_EQ(d.data(), 1000000000000);
        CHECK_EQ(d.is_gigabyte(), false);
    }

    TEST_CASE("TB")
    {
        const auto a = 1_TB;
        CHECK_EQ(a.data(), 1000000000000);
        CHECK_EQ(a.is_terrabyte(), true);

        const auto b = 100_TB;
        CHECK_EQ(b.data(), 100000000000000);
        CHECK_EQ(b.is_terrabyte(), true);

        const auto c = 500_TB;
        CHECK_EQ(c.data(), 500000000000000);
        CHECK_EQ(c.is_terrabyte(), true);

        const auto d = 1000_TB;
        CHECK_EQ(d.data(), 1000000000000000);
        CHECK_EQ(d.is_terrabyte(), false);
    }

    TEST_CASE("PB")
    {
        const auto a = 1_PB;
        CHECK_EQ(a.data(), 1000000000000000);
        CHECK_EQ(a.is_petabyte(), true);

        const auto b = 100_PB;
        CHECK_EQ(b.data(), 100000000000000000);
        CHECK_EQ(b.is_petabyte(), true);

        const auto c = 500_PB;
        CHECK_EQ(c.data(), 500000000000000000);
        CHECK_EQ(c.is_petabyte(), true);

        const auto d = 1000_PB;
        CHECK_EQ(d.data(), 1000000000000000000);
        CHECK_EQ(d.is_petabyte(), false);
    }

    TEST_CASE("EB")
    {
        const auto a = 1_EB;
        CHECK_EQ(a.data(), 1000000000000000000);
        CHECK_EQ(a.is_exabyte(), true);

#ifdef NO_VERY_LARGE_INT_TYPE
        const auto b = 100_EB;
        CHECK_EQ(b.data(), 100000000000000000000);
        CHECK_EQ(b.is_exabyte());

        const auto c = 500_EB;
        CHECK_EQ(c.data(), 500000000000000000000);
        CHECK_EQ(c.is_exabyte());

        const auto d = 1000_EB;
        CHECK_EQ(d.data(), 1000000000000000000000);
        CHECK_EQ(d.is_exabyte(), false);
#endif
    }
}
