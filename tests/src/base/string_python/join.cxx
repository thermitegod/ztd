/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <string>
#include <string_view>
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::join")
{
    SUBCASE("vector<string>")
    {
        std::vector<std::string> vec;
        std::string sep;
        std::string wanted;

        SUBCASE("empty") {}

        SUBCASE("string")
        {
            vec = {"foo", "foo", "foo"};
            sep = " ";
            wanted = "foo foo foo";
        }

        SUBCASE("multi sep")
        {
            vec = {"foo", "foo", "foo"};
            sep = " | ";
            wanted = "foo | foo | foo";
        }

        CHECK_EQ(ztd::join(vec, sep), wanted);
    }

    SUBCASE("vector<string_view>")
    {
        std::vector<std::string_view> vec;
        std::string sep;
        std::string wanted;

        SUBCASE("empty") {}

        SUBCASE("string")
        {
            using namespace std::string_view_literals;

            vec = {"foo"sv, "foo"sv, "foo"sv};
            sep = " ";
            wanted = "foo foo foo";
        }

        SUBCASE("multi sep")
        {
            using namespace std::string_view_literals;

            vec = {"foo"sv, "foo"sv, "foo"sv};
            sep = " | ";
            wanted = "foo | foo | foo";
        }

        CHECK_EQ(ztd::join(vec, sep), wanted);
    }
}
