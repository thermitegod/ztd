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

#include <gtest/gtest.h>

#include "ztd/detail/byte_size.hxx"

/**
 * operator+
 */
TEST(byte_iec_operator_plus, self)
{
    using namespace ztd::byte_iec_literals;

    const auto a = 1_KiB;
    const auto b = 2_KiB;

    EXPECT_EQ(a + a, 2_KiB);
    EXPECT_EQ(a + b, 3_KiB);
    EXPECT_EQ(b + a, 3_KiB);
    EXPECT_EQ(b + b, 4_KiB);
}

/**
 * operator+=
 */
TEST(byte_iec_operator_plus_equals, self)
{
    using namespace ztd::byte_iec_literals;

    auto a = 1_KiB;
    auto b = 2_KiB;

    EXPECT_EQ(a += a, 2_KiB);
    EXPECT_EQ(a += b, 4_KiB);
    EXPECT_EQ(b += a, 6_KiB);
    EXPECT_EQ(b += b, 12_KiB);
}

/**
 * operator-
 */
TEST(byte_iec_operator_subtract, self)
{
    using namespace ztd::byte_iec_literals;

    const auto big = 100_KiB;
    const auto small = 10_KiB;

    EXPECT_EQ(small - small, 0_KiB);
    EXPECT_EQ(big - small, 90_KiB);
    EXPECT_EQ(big - big, 0_KiB);
}

/**
 * operator-=
 */
TEST(byte_iec_operator_subtract_equals, self)
{
    using namespace ztd::byte_iec_literals;

    auto big = 100_KiB;
    const auto small = 10_KiB;

    EXPECT_EQ(big -= small, 90_KiB);
}

/**
 * operator*
 */
TEST(byte_iec_operator_multiply, external)
{
    using namespace ztd::byte_iec_literals;

    const auto val = 512_KiB;
    const auto x = 2ull;

    EXPECT_EQ(val * x, 1_MiB);

    const auto zero = 0ull;
    EXPECT_EQ(val * zero, zero);

    const auto one = 1ull;
    EXPECT_EQ(val * one, val);
}

/**
 * operator*=
 */
TEST(byte_iec_operator_multiply_equals, external)
{
    using namespace ztd::byte_iec_literals;

    auto val = 10_KiB;

    auto zero = 0ull;
    EXPECT_EQ(val *= zero, zero);

    auto one = 1ull;
    EXPECT_EQ(val *= one, val);
}

/**
 * operator/
 */
TEST(byte_iec_operator_divide, external)
{
    using namespace ztd::byte_iec_literals;

    const auto big_val = 100_KiB;
    const auto small_val = 10ull;

    EXPECT_EQ(big_val / small_val, 10_KiB);
}

/**
 * operator/=
 */
TEST(byte_iec_operator_divide_equals, external)
{
    using namespace ztd::byte_iec_literals;

    auto big_val = 100_KiB;
    auto small_val = 10ull;

    EXPECT_EQ(big_val / small_val, 10_KiB);
}

/**
 * operator%
 */
TEST(byte_iec_operator_modulus, external_remainder)
{
    using namespace ztd::byte_iec_literals;

    const auto val = 127_B;
    const auto mod = 2ull;
    EXPECT_EQ(val.data() % mod, 1_B);
}

TEST(byte_iec_operator_modulus, external_no_remainder)
{
    using namespace ztd::byte_iec_literals;

    auto val = 128_B;
    const auto mod = 2ull;
    EXPECT_EQ(val % mod, 0_B);
}

/**
 * operator%=
 */
TEST(byte_iec_operator_modulus_equals, external_remainder)
{
    using namespace ztd::byte_iec_literals;

    auto val = 127_B;
    const auto mod = 2ull;
    EXPECT_EQ(val %= mod, 1_B);
}

TEST(byte_iec_operator_modulus_equals, external_no_remainder)
{
    using namespace ztd::byte_iec_literals;

    auto val = 128_B;
    const auto mod = 2ull;
    EXPECT_EQ(val %= mod, 0_B);
}
