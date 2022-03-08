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

#include "../../src/ztd.hxx"

TEST_CASE("::clear")
{
    std::string str1 = "a";

    ztd::clear(str1);

    REQUIRE(ztd::same(str1, ""));
}

TEST_CASE("::empty")
{
    std::string str1 = "";
    std::string str2 = "a";

    REQUIRE(ztd::empty(str1) == true);
    REQUIRE(ztd::empty(str2) == false);
}

TEST_CASE("::nempty")
{
    std::string str1 = "";
    std::string str2 = "a";

    REQUIRE(ztd::nempty(str1) == false);
    REQUIRE(ztd::nempty(str2) == true);
}

TEST_CASE("::b")
{
    std::string str1 = "";
    std::string str2 = "a";

    REQUIRE(ztd::b(str1) == false);
    REQUIRE(ztd::b(str2) == true);
}
