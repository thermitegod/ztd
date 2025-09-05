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

TEST_CASE("ztd::replace")
{
    std::string str;
    std::string str_find;
    std::string str_replace;
    std::string wanted;
    ztd::i32 count = -1_i32; // replace all

    SUBCASE("replace")
    {
        str = "foobar foobar foobar";
        str_find = "foo";
        str_replace = "baz";
        wanted = "bazbar bazbar bazbar";
    }

    SUBCASE("str empty")
    {
        str = "";
        str_find = "foo";
        str_replace = "baz";
        wanted = "";
    }

    SUBCASE("find empty")
    {
        str = "foobar foobar foobar";
        str_find = "";
        str_replace = "baz";
        wanted = "foobar foobar foobar";
    }

    SUBCASE("replace empty")
    {
        str = "foobar foobar foobar";
        str_find = "foo";
        str_replace = "";
        wanted = "bar bar bar";
    }

    SUBCASE("missing")
    {
        str = "foobar foobar foobar";
        str_find = "fooo";
        str_replace = "baz";
        wanted = "foobar foobar foobar";
    }

    SUBCASE("count neg")
    {
        str = "foobar foobar foobar";
        str_find = "foo";
        str_replace = "baz";
        wanted = "bazbar bazbar bazbar";
        count = -5;
    }

    SUBCASE("count")
    {
        str = "foobar foobar foobar";
        str_find = "foo";
        str_replace = "baz";

        SUBCASE("0")
        {
            count = 0;
            wanted = "foobar foobar foobar";
        }

        SUBCASE("1")
        {
            count = 1;
            wanted = "bazbar foobar foobar";
        }

        SUBCASE("2")
        {
            count = 2;
            wanted = "bazbar bazbar foobar";
        }

        SUBCASE("3")
        {
            count = 3;
            wanted = "bazbar bazbar bazbar";
        }

        SUBCASE("very large")
        {
            count = 500;
            wanted = "bazbar bazbar bazbar";
        }
    }

    CHECK_EQ(ztd::replace(str, str_find, str_replace, count), wanted);
}
