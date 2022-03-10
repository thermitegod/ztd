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
#include <vector>

#include "../../src/ztd.hxx"

TEST_CASE("::split")
{
    std::string str = "foo foo foo";

    std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    std::vector<std::string> result = ztd::split(str, " ");

    REQUIRE(result == result_wanted);
}

TEST_CASE("::split delimiter first")
{
    std::string str = "delimtestdelimtest";

    std::vector<std::string> result_wanted = {"test", "test"};
    std::vector<std::string> result = ztd::split(str, "delim");

    REQUIRE(result == result_wanted);
}

TEST_CASE("::split delimiter second")
{
    std::string str = "testdelimtest";

    std::vector<std::string> result_wanted = {"test", "test"};
    std::vector<std::string> result = ztd::split(str, "delim");

    REQUIRE(result == result_wanted);
}

TEST_CASE("::join")
{
    std::vector<std::string> vec = {"foo", "foo", "foo"};

    std::string result_wanted = "foo foo foo";
    std::string result = ztd::join(vec, " ");

    REQUIRE(result == result_wanted);
}
