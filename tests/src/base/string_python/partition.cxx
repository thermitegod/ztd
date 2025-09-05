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

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::partition")
{
    SUBCASE("default")
    {
        std::string str;
        std::string sep;
        std::string wanted_1;
        std::string wanted_2;
        std::string wanted_3;

        SUBCASE("partition")
        {
            str = "foobar$foobar$foobar";
            sep = "$";
            wanted_1 = "foobar";
            wanted_2 = "$";
            wanted_3 = "foobar$foobar";
        }

        SUBCASE("str empty")
        {
            str = "";
            sep = "$";
            wanted_1 = "";
            wanted_2 = "";
            wanted_3 = "";
        }

        SUBCASE("sep empty")
        {
            str = "foobar$foobar$foobar";
            sep = "";
            wanted_1 = "foobar$foobar$foobar";
            wanted_2 = "";
            wanted_3 = "";
        }

        SUBCASE("missing")
        {
            str = "foobar$foobar$foobar";
            sep = "^";
            wanted_1 = "foobar$foobar$foobar";
            wanted_2 = "";
            wanted_3 = "";
        }

        SUBCASE("multi")
        {
            str = "test.tar.tar.test";
            sep = ".tar.";
            wanted_1 = "test";
            wanted_2 = ".tar.";
            wanted_3 = "tar.test";
        }

        const auto [r1, r2, r3] = ztd::partition(str, sep);
        CHECK_EQ(r1, wanted_1);
        CHECK_EQ(r2, wanted_2);
        CHECK_EQ(r3, wanted_3);

        const auto recombine = std::format("{}{}{}", r1, r2, r3);
        CHECK_EQ(recombine, str);
    }

    SUBCASE("char overload")
    {
        std::string str;
        char sep = 0;
        std::string wanted_1;
        std::string wanted_2;
        std::string wanted_3;

        SUBCASE("char")
        {
            str = "foobar$foobar$foobar";
            sep = '$';
            wanted_1 = "foobar";
            wanted_2 = "$";
            wanted_3 = "foobar$foobar";
        }

        SUBCASE("str empty")
        {
            str = "";
            sep = '$';
            wanted_1 = "";
            wanted_2 = "";
            wanted_3 = "";
        }

        SUBCASE("missong")
        {
            str = "foobar$foobar$foobar";
            sep = '^';
            wanted_1 = "foobar$foobar$foobar";
            wanted_2 = "";
            wanted_3 = "";
        }

        const auto [r1, r2, r3] = ztd::partition(str, sep);
        CHECK_EQ(r1, wanted_1);
        CHECK_EQ(r2, wanted_2);
        CHECK_EQ(r3, wanted_3);

        const auto recombine = std::format("{}{}{}", r1, r2, r3);
        CHECK_EQ(recombine, str);
    }
}
