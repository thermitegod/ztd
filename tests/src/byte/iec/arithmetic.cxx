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

TEST_SUITE("ztd::byte_iec arithmetic" * doctest::description(""))
{
    using namespace ztd::byte_iec_literals;

    // operator+
    TEST_CASE("operator plus")
    {
        const auto a = 1_KiB;
        const auto b = 2_KiB;

        CHECK_EQ(a + a, 2_KiB);
        CHECK_EQ(a + b, 3_KiB);
        CHECK_EQ(b + a, 3_KiB);
        CHECK_EQ(b + b, 4_KiB);
    }

    // operator+=
    TEST_CASE("operator plus equals")
    {
        auto a = 1_KiB;
        auto b = 2_KiB;

        CHECK_EQ(a += a, 2_KiB);
        CHECK_EQ(a += b, 4_KiB);
        CHECK_EQ(b += a, 6_KiB);
        CHECK_EQ(b += b, 12_KiB);
    }

    // operator-
    TEST_CASE("operator subtract")
    {
        const auto big = 100_KiB;
        const auto small = 10_KiB;

        CHECK_EQ(small - small, 0_KiB);
        CHECK_EQ(big - small, 90_KiB);
        CHECK_EQ(big - big, 0_KiB);
    }

    // operator-=
    TEST_CASE("operator subtract equals")
    {
        auto big = 100_KiB;
        const auto small = 10_KiB;

        CHECK_EQ(big -= small, 90_KiB);
    }

    // operator*
    TEST_CASE("operator multiply")
    {
        const auto val = 512_KiB;
        const auto x = 2ull;

        CHECK_EQ(val * x, 1_MiB);

        const auto zero = 0ull;
        CHECK_EQ(val * zero, zero);

        const auto one = 1ull;
        CHECK_EQ(val * one, val);
    }

    // operator*=
    TEST_CASE("operator multiply equals")
    {
        auto val = 10_KiB;

        auto zero = 0ull;
        CHECK_EQ(val *= zero, zero);

        auto one = 1ull;
        CHECK_EQ(val *= one, val);
    }

    // operator/
    TEST_CASE("operator divide")
    {
        const auto big_val = 100_KiB;
        const auto small_val = 10ull;

        CHECK_EQ(big_val / small_val, 10_KiB);
    }

    // operator/=
    TEST_CASE("operator divide equals")
    {
        auto big_val = 100_KiB;
        auto small_val = 10ull;

        CHECK_EQ(big_val / small_val, 10_KiB);
    }

    // operator%
    TEST_CASE("operator modulus remainder")
    {
        const auto val = 127_B;
        const auto mod = 2ull;
        CHECK_EQ(val.data() % mod, 1_B);
    }

    // operator%
    TEST_CASE("operator modulus no remainder")
    {
        auto val = 128_B;
        const auto mod = 2ull;
        CHECK_EQ(val % mod, 0_B);
    }

    // operator%=
    TEST_CASE("operator modulus equals remainder")
    {
        auto val = 127_B;
        const auto mod = 2ull;
        CHECK_EQ(val %= mod, 1_B);
    }

    // operator%=
    TEST_CASE("operator modulus equals no remainder")
    {
        auto val = 128_B;
        const auto mod = 2ull;
        CHECK_EQ(val %= mod, 0_B);
    }
}
