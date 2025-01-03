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

#include "ztd/detail/random.hxx"

TEST_SUITE("ztd::random" * doctest::description(""))
{
    TEST_CASE("irand")
    {
        SUBCASE("min_max")
        {
            const auto result = ztd::irand(0, 10);
            CHECK_EQ((result >= 0 && result <= 10), true);
        }
    }

    TEST_CASE("urand")
    {
        SUBCASE("min_max")
        {
            const auto result = ztd::urand(0, 10);
            CHECK_EQ((result >= 0 && result <= 10), true);
        }
    }
}
