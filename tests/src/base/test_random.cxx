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

#include <ranges>

#include <doctest/doctest.h>

#include "ztd/detail/random.hxx"

TEST_SUITE("ztd::random" * doctest::description(""))
{
    TEST_CASE("rand")
    {
        SUBCASE("small range")
        {
            const auto min = 1;
            const auto max = 10;

            for (auto _ : std::views::iota(0, 100))
            {
                const auto value = ztd::rand<i32>(min, max);
                CHECK(value >= min);
                CHECK(value <= max);
            }
        }

        SUBCASE("larger range")
        {
            const auto min = -1000;
            const auto max = 1000;

            for (auto _ : std::views::iota(0, 100))
            {
                const auto value = ztd::rand<i64>(min, max);
                CHECK(value >= min);
                CHECK(value <= max);
            }
        }

        SUBCASE("whole range")
        {
            const auto min = std::numeric_limits<i64>::min();
            const auto max = std::numeric_limits<i64>::max();

            for (auto _ : std::views::iota(0, 100))
            {
                const auto value = ztd::rand<i64>(min, max);
                CHECK(value >= min);
                CHECK(value <= max);
            }
        }

        SUBCASE("zero range")
        {
            const auto min = 69;
            const auto max = 69;

            for (auto _ : std::views::iota(0, 10))
            {
                const auto value = ztd::rand<i32>(min, max);
                CHECK(value == min);
            }
        }
    }
}
