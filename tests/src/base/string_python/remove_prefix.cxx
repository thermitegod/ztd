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

TEST_CASE("ztd::remove_prefix")
{
    SUBCASE("default")
    {
        std::string str;
        std::string prefix;
        std::string wanted;

        SUBCASE("remove_prefix")
        {
            str = "foobar test string";
            prefix = "foobar ";
            wanted = "test string";
        }

        SUBCASE("missing")
        {
            str = "foobar test string";
            prefix = "zbar";
            wanted = "foobar test string";
        }

        SUBCASE("str empty")
        {
            str = "";
            prefix = "foobar";
            wanted = "";
        }

        SUBCASE("prefix empty")
        {
            str = "foobar";
            prefix = "";
            wanted = "foobar";
        }

        CHECK_EQ(ztd::remove_prefix(str, prefix), wanted);
    }

    SUBCASE("char overload")
    {
        std::string str;
        char prefix = 0;
        std::string wanted;

        SUBCASE("char")
        {
            str = "@foobar@";
            prefix = '@';
            wanted = "foobar@";
        }

        SUBCASE("missing")
        {
            str = "@foobar@";
            prefix = 'Z';
            wanted = "@foobar@";
        }

        SUBCASE("str empty")
        {
            str = "";
            prefix = '@';
            wanted = "";
        }

        CHECK_EQ(ztd::remove_prefix(str, prefix), wanted);
    }
}
