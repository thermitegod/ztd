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

TEST_SUITE("ztd::byte_iec arithmetic")
{
    using namespace ztd::byte_iec_literals;

    // operator+
    TEST_CASE("operator plus")
    {
        const auto a = 1_KiB;
        const auto b = 2_KiB;

        CHECK(a + a == 2_KiB);
        CHECK(a + b == 3_KiB);
        CHECK(b + a == 3_KiB);
        CHECK(b + b == 4_KiB);
    }

    // operator+=
    TEST_CASE("operator plus equals")
    {
        auto a = 1_KiB;
        auto b = 2_KiB;

        a += a;
        CHECK(a == 2_KiB);

        a += b;
        CHECK(a == 4_KiB);

        b += a;
        CHECK(b == 6_KiB);

        b += b;
        CHECK(b == 12_KiB);
    }

    // operator-
    TEST_CASE("operator subtract")
    {
        const auto big = 100_KiB;
        const auto small = 10_KiB;

        CHECK(small - small == 0_KiB);
        CHECK(big - small == 90_KiB);
        CHECK(big - big == 0_KiB);
    }

    // operator-=
    TEST_CASE("operator subtract equals")
    {
        auto big = 100_KiB;
        const auto small = 10_KiB;

        big -= small;
        CHECK(big == 90_KiB);
    }

    // operator*
    TEST_CASE("operator multiply")
    {
        const auto val = 512_KiB;
        const auto x = 2ull;

        CHECK(val * x == 1_MiB);

        const auto zero = 0ull;
        CHECK(val * zero == 0_B);

        const auto one = 1ull;
        CHECK(val * one == val);
    }

    // operator*=
    TEST_CASE("operator multiply equals")
    {
        auto val = 10_KiB;

        auto zero = 0ull;
        auto one = 1ull;

        val *= zero;
        CHECK(val == 0_B);

        val *= one;
        CHECK(val == val);
    }

    // operator/
    TEST_CASE("operator divide")
    {
        const auto big_val = 100_KiB;
        const auto small_val = 10ull;

        CHECK(big_val / small_val == 10_KiB);
    }

    // operator/=
    TEST_CASE("operator divide equals")
    {
        auto big_val = 100_KiB;
        auto small_val = 10ull;

        CHECK(big_val / small_val == 10_KiB);
    }

    // operator%
    TEST_CASE("operator modulus remainder")
    {
        const auto val = 127_B;
        const auto mod = 2ull;
        CHECK(ztd::byte_iec{val.data() % mod} == 1_B);
    }

    // operator%
    TEST_CASE("operator modulus no remainder")
    {
        auto val = 128_B;
        const auto mod = 2ull;
        CHECK(val % mod == 0_B);
    }

    // operator%=
    TEST_CASE("operator modulus equals remainder")
    {
        auto val = 127_B;
        const auto mod = 2ull;

        val %= mod;
        CHECK(val == 1_B);
    }

    // operator%=
    TEST_CASE("operator modulus equals no remainder")
    {
        auto val = 128_B;
        const auto mod = 2ull;

        val %= mod;
        CHECK(val == 0_B);
    }
}
