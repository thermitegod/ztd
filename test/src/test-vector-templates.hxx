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

TEST_CASE("::move")
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::vector<std::string> result_wanted{"bar", "foo", "baz"};
    ztd::move(vec1, 1, 0);

    REQUIRE(vec1 == result_wanted);
}

TEST_CASE("::index")
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::string bar = "bar";
    std::size_t index = ztd::index(vec1, bar);

    REQUIRE(index == 1);
}

TEST_CASE("::contains vector")
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::string bar = "bar";
    std::string buz = "buz";

    REQUIRE(ztd::contains(vec1, bar) == true);
    REQUIRE(ztd::contains(vec1, buz) == false);
}

TEST_CASE("::remove")
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::vector<std::string> result_wanted{"foo", "baz"};
    std::string bar = "bar";
    ztd::remove(vec1, bar);

    REQUIRE(vec1 == result_wanted);
}

TEST_CASE("::merge")
{
    std::vector<std::string> vec1{"foo", "bar"};
    std::vector<std::string> vec2{"foo", "baz", "buz"};

    std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz"};
    std::vector<std::string> result = ztd::merge(vec1, vec2);

    REQUIRE(result == result_wanted);
}

