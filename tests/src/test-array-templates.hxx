/**
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

#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <array>

#include "../../src/ztd.hxx"

TEST_CASE("::contains array<T> overload")
{
    std::vector<std::string> arr1{"foo", "bar", "baz"};

    std::string bar = "bar";
    std::string buz = "buz";

    REQUIRE(ztd::contains(arr1, bar) == true);
    REQUIRE(ztd::contains(arr1, buz) == false);

    std::vector<int> arr2{1, 2, 3, 4, 5};

    int five = 5;
    int nine = 9;

    REQUIRE(ztd::contains(arr2, five) == true);
    REQUIRE(ztd::contains(arr2, nine) == false);
}
