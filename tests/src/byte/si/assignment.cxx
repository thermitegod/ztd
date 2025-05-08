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

TEST_SUITE("ztd::byte_si assignment" * doctest::description(""))
{
    TEST_CASE("assignment")
    {
        const auto a1 = ztd::byte_si{1024ull};
        const auto b1 = ztd::byte_si{1024ull};
        const auto c1 = ztd::byte_si{1024ull};
        const auto d1 = ztd::byte_si{1024ull};

        auto a2 = ztd::byte_si{0ull};
        auto b2 = ztd::byte_si{0ull};
        auto c2 = ztd::byte_si{0ull};
        auto d2 = ztd::byte_si{0ull};

        a2 = a1;
        b2 = b1;
        c2 = c1;
        d2 = d1;

        CHECK_EQ(a1, a2);
        CHECK_EQ(b1, b2);
        CHECK_EQ(c1, c2);
        CHECK_EQ(d1, d2);
    }
}
