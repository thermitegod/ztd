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
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::rsplit")
{
    std::string str;
    std::string sep;
    ztd::i32 maxsplit = -1_i32; // split all
    std::vector<std::string> wanted;

    SUBCASE("split")
    {
        str = "foo foo foo";
        sep = " ";
        wanted = {"foo", "foo", "foo"};
    }

    SUBCASE("empty")
    {
        str = "";
        sep = ",";
        wanted = {""};
    }

    SUBCASE("delimiter first")
    {
        str = ",test,test";
        sep = ",";
        wanted = {"", "test", "test"};
    }

    SUBCASE("delimiter second")
    {
        str = "test,test";
        sep = ",";
        wanted = {"test", "test"};
    }

    SUBCASE("delimiter multiple empty")
    {
        str = "test,,,test";
        sep = ",";
        wanted = {"test", "", "", "test"};
    }

    SUBCASE("delimiter missing")
    {
        str = "test|test";
        sep = ",";
        wanted = {"test|test"};
    }

    SUBCASE("no delimiter")
    {
        str = "a,b,c,d,e,f";
        sep = "";
        wanted = {"a,b,c,d,e,f"};
    }

    SUBCASE("delimiter size 1")
    {
        str = "a,b,c,d,e,f";
        sep = ",";

        SUBCASE("maxsplit default")
        {
            wanted = {"a", "b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 0")
        {
            maxsplit = 0;
            wanted = {"a,b,c,d,e,f"};
        }

        SUBCASE("maxsplit 1")
        {
            maxsplit = 1;
            wanted = {"a,b,c,d,e", "f"};
        }

        SUBCASE("maxsplit 2")
        {
            maxsplit = 2;
            wanted = {"a,b,c,d", "e", "f"};
        }

        SUBCASE("maxsplit 3")
        {
            maxsplit = 3;
            wanted = {"a,b,c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 4")
        {
            maxsplit = 4;
            wanted = {"a,b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 5")
        {
            maxsplit = 5;
            wanted = {"a", "b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit very large")
        {
            maxsplit = 500;
            wanted = {"a", "b", "c", "d", "e", "f"};
        }
    }

    SUBCASE("delimiter size 2")
    {
        str = "a<>b<>c<>d<>e<>f";
        sep = "<>";

        SUBCASE("maxsplit default")
        {
            wanted = {"a", "b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 0")
        {
            maxsplit = 0;
            wanted = {"a<>b<>c<>d<>e<>f"};
        }

        SUBCASE("maxsplit 1")
        {
            maxsplit = 1;
            wanted = {"a<>b<>c<>d<>e", "f"};
        }

        SUBCASE("maxsplit 2")
        {
            maxsplit = 2;
            wanted = {"a<>b<>c<>d", "e", "f"};
        }

        SUBCASE("maxsplit 3")
        {
            maxsplit = 3;
            wanted = {"a<>b<>c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 4")
        {
            maxsplit = 4;
            wanted = {"a<>b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 5")
        {
            maxsplit = 5;
            wanted = {"a", "b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit very large")
        {
            maxsplit = 500;
            wanted = {"a", "b", "c", "d", "e", "f"};
        }
    }

    SUBCASE("delimiter size 3")
    {
        str = "a<=>b<=>c<=>d<=>e<=>f";
        sep = "<=>";

        SUBCASE("maxsplit default")
        {
            wanted = {"a", "b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 0")
        {
            maxsplit = 0;
            wanted = {"a<=>b<=>c<=>d<=>e<=>f"};
        }

        SUBCASE("maxsplit 1")
        {
            maxsplit = 1;
            wanted = {"a<=>b<=>c<=>d<=>e", "f"};
        }

        SUBCASE("maxsplit 2")
        {
            maxsplit = 2;
            wanted = {"a<=>b<=>c<=>d", "e", "f"};
        }

        SUBCASE("maxsplit 3")
        {
            maxsplit = 3;
            wanted = {"a<=>b<=>c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 4")
        {
            maxsplit = 4;
            wanted = {"a<=>b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit 5")
        {
            maxsplit = 5;
            wanted = {"a", "b", "c", "d", "e", "f"};
        }

        SUBCASE("maxsplit very large")
        {
            maxsplit = 500;
            wanted = {"a", "b", "c", "d", "e", "f"};
        }
    }

    SUBCASE("filepath")
    {
        str = "/home/user/download";
        sep = "/";
        wanted = {"", "home", "user", "download"};
    }

    CHECK_EQ(ztd::rsplit(str, sep, maxsplit), wanted);
}
