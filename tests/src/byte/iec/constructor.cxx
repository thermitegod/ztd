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

TEST_SUITE("ztd::byte_iec constructor" * doctest::description(""))
{
    TEST_CASE("default init")
    {
        const ztd::byte_iec x;
        CHECK_EQ(x.data(), 0);
    }

    TEST_CASE("init")
    {
        const auto value = ztd::byte_iec{1024ull};
        const ztd::byte_iec original = value;

        CHECK_EQ(value, original);
        CHECK_EQ(ztd::byte_iec(value), original);
        CHECK_EQ(value.data(), 1024ull);
    }
}
