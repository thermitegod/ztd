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

// I know they are deprecated, I am the one who did it.
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>

#include "../../../src/ztd.hxx"

TEST_CASE("::prefix")
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar";

    REQUIRE(ztd::prefix(str1, str2));

    std::string str3 = "foobar test string";
    std::string str4 = "test";

    REQUIRE(!ztd::prefix(str3, str4));
}

TEST_CASE("::suffix")
{
    std::string str1 = "foobar test string";
    std::string str2 = "string";

    REQUIRE(ztd::suffix(str1, str2));

    std::string str3 = "foobar test string";
    std::string str4 = "test";

    REQUIRE(!ztd::suffix(str3, str4));
}

TEST_CASE("::ltrim")
{
    std::string str = "  a  ";

    std::string result_wanted = "a  ";
    std::string result = ztd::ltrim(str);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::rtrim")
{
    std::string str = "  a  ";

    std::string result_wanted = "  a";
    std::string result = ztd::rtrim(str);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::trim")
{
    std::string str = "  a  ";

    std::string result_wanted = "a";
    std::string result = ztd::trim(str);

    REQUIRE(ztd::same(result, result_wanted));
}
