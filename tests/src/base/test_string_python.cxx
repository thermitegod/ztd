/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

TEST_CASE("ztd::split")
{
    SUBCASE("split")
    {
        const std::string str = "foo foo foo";

        const std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
        const std::vector<std::string> result = ztd::split(str, " ");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::vector<std::string> result_wanted = {""};
        const std::vector<std::string> result = ztd::split(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter first")
    {
        const std::string str = ",test,test";

        const std::vector<std::string> result_wanted = {"", "test", "test"};
        const std::vector<std::string> result = ztd::split(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter second")
    {
        const std::string str = "test,test";

        const std::vector<std::string> result_wanted = {"test", "test"};
        const std::vector<std::string> result = ztd::split(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple empty")
    {
        const std::string str = "test,,,test";

        const std::vector<std::string> result_wanted = {"test", "", "", "test"};
        const std::vector<std::string> result = ztd::split(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter missing")
    {
        const std::string str = "test|test";

        const std::vector<std::string> result_wanted = {"test|test"};
        const std::vector<std::string> result = ztd::split(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("no delimiter")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
        const std::vector<std::string> result = ztd::split(str);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit all")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::split(str, "<>");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 0")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a<>b<>c<>d<>e<>f"};
        const std::vector<std::string> result = ztd::split(str, "<>", 0);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 1")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b<>c<>d<>e<>f"};
        const std::vector<std::string> result = ztd::split(str, "<>", 1);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 2")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c<>d<>e<>f"};
        const std::vector<std::string> result = ztd::split(str, "<>", 2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 3")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d<>e<>f"};
        const std::vector<std::string> result = ztd::split(str, "<>", 3);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 4")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e<>f"};
        const std::vector<std::string> result = ztd::split(str, "<>", 4);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 5")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::split(str, "<>", 5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit all")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::split(str, "<=>");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 0")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d<=>e<=>f"};
        const std::vector<std::string> result = ztd::split(str, "<=>", 0);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 1")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b<=>c<=>d<=>e<=>f"};
        const std::vector<std::string> result = ztd::split(str, "<=>", 1);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 2")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c<=>d<=>e<=>f"};
        const std::vector<std::string> result = ztd::split(str, "<=>", 2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 3")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d<=>e<=>f"};
        const std::vector<std::string> result = ztd::split(str, "<=>", 3);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 4")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e<=>f"};
        const std::vector<std::string> result = ztd::split(str, "<=>", 4);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 5")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::split(str, "<=>", 5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit all")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::split(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 0")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
        const std::vector<std::string> result = ztd::split(str, ",", 0);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 1")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b,c,d,e,f"};
        const std::vector<std::string> result = ztd::split(str, ",", 1);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 2")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c,d,e,f"};
        const std::vector<std::string> result = ztd::split(str, ",", 2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 3")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d,e,f"};
        const std::vector<std::string> result = ztd::split(str, ",", 3);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 4")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e,f"};
        const std::vector<std::string> result = ztd::split(str, ",", 4);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 5")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::split(str, ",", 5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit larger than real maxsplit")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::split(str, ",", 500);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("filepath")
    {
        const std::string str = "/home/user/download";

        const std::vector<std::string> result_wanted = {"", "home", "user", "download"};
        const std::vector<std::string> result = ztd::split(str, "/");

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::rsplit")
{
    SUBCASE("split")
    {
        const std::string str = "foo foo foo";

        const std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
        const std::vector<std::string> result = ztd::rsplit(str, " ");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::vector<std::string> result_wanted = {""};
        const std::vector<std::string> result = ztd::rsplit(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter first")
    {
        const std::string str = ",test,test";

        const std::vector<std::string> result_wanted = {"", "test", "test"};
        const std::vector<std::string> result = ztd::rsplit(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter second")
    {
        const std::string str = "test,test";

        const std::vector<std::string> result_wanted = {"test", "test"};
        const std::vector<std::string> result = ztd::rsplit(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple empty")
    {
        const std::string str = "test,,,test";

        const std::vector<std::string> result_wanted = {"test", "", "", "test"};
        const std::vector<std::string> result = ztd::rsplit(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter missing")
    {
        const std::string str = "test|test";

        const std::vector<std::string> result_wanted = {"test|test"};
        const std::vector<std::string> result = ztd::rsplit(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("no delimiter")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
        const std::vector<std::string> result = ztd::rsplit(str);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit all")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<>");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 0")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a<>b<>c<>d<>e<>f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<>", 0);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 1")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a<>b<>c<>d<>e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<>", 1);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 2")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a<>b<>c<>d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<>", 2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 3")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a<>b<>c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<>", 3);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 4")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a<>b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<>", 4);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 2, maxsplit 5")
    {
        const std::string str = "a<>b<>c<>d<>e<>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<>", 5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit all")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<=>");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 0")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d<=>e<=>f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<=>", 0);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 1")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d<=>e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<=>", 1);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 2")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<=>", 2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 3")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a<=>b<=>c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<=>", 3);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 4")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a<=>b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<=>", 4);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("delimiter multiple chars 3, maxsplit 5")
    {
        const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, "<=>", 5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit all")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 0")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",", 0);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 1")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b,c,d,e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",", 1);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 2")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b,c,d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",", 2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 3")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b,c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",", 3);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 4")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a,b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",", 4);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit 5")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",", 5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("maxsplit larger than real maxsplit")
    {
        const std::string str = "a,b,c,d,e,f";

        const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
        const std::vector<std::string> result = ztd::rsplit(str, ",", 500);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("filepath")
    {
        const std::string str = "/home/user/download";

        const std::vector<std::string> result_wanted = {"", "home", "user", "download"};
        const std::vector<std::string> result = ztd::rsplit(str, "/");

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::join")
{
    SUBCASE("vector<string>")
    {
        SUBCASE("empty string")
        {
            const std::vector<std::string> vec = {};

            const std::string result_wanted;
            const std::string result = ztd::join(vec, "Z");

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("string")
        {
            const std::vector<std::string> vec = {"foo", "foo", "foo"};

            const std::string result_wanted = "foo foo foo";
            const std::string result = ztd::join(vec, " ");

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("multi sep")
        {
            const std::vector<std::string> vec = {"foo", "foo", "foo"};

            const std::string result_wanted = "foo | foo | foo";
            const std::string result = ztd::join(vec, " | ");

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("empty")
        {
            const std::vector<std::string> vec = {};

            const std::string result_wanted;
            const std::string result = ztd::join(vec, " ");

            CHECK_EQ(result, result_wanted);
        }
    }

    SUBCASE("vector<string_view>")
    {
        SUBCASE("empty string")
        {
            const std::vector<std::string_view> vec = {};

            const std::string result_wanted;
            const std::string result = ztd::join(vec, "Z");

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("string")
        {
            using namespace std::string_view_literals;

            const std::vector<std::string_view> vec = {"foo"sv, "foo"sv, "foo"sv};

            const std::string result_wanted = "foo foo foo";
            const std::string result = ztd::join(vec, " ");

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("multi sep")
        {
            using namespace std::string_view_literals;

            const std::vector<std::string_view> vec = {"foo"sv, "foo"sv, "foo"sv};

            const std::string result_wanted = "foo | foo | foo";
            const std::string result = ztd::join(vec, " | ");

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("empty")
        {
            const std::vector<std::string_view> vec = {};

            const std::string result_wanted;
            const std::string result = ztd::join(vec, " ");

            CHECK_EQ(result, result_wanted);
        }
    }
}

TEST_CASE("ztd::lower")
{
    SUBCASE("latin")
    {
        const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        const std::string lower_wanted = "abcdefghijklmnopqrstuvwxyz1234567890";

        const std::string lower = ztd::lower(upper);

        CHECK_EQ(lower, lower_wanted);
    }

    SUBCASE("special")
    {
        const std::string upper = "!@$%^&*()_+";
        const std::string lower_wanted = "!@$%^&*()_+";

        const std::string lower = ztd::lower(upper);

        CHECK_EQ(lower, lower_wanted);
    }

    SUBCASE("mixed special")
    {
        const std::string upper = "@A@a@A@";
        const std::string lower_wanted = "@a@a@a@";

        const std::string lower = ztd::lower(upper);

        CHECK_EQ(lower, lower_wanted);
    }

    SUBCASE("japanese")
    {
        const std::string upper = "化粧室はどこですか";
        const std::string lower_wanted = "化粧室はどこですか";

        const std::string lower = ztd::lower(upper);

        CHECK_EQ(lower, lower_wanted);
    }

    SUBCASE("korean")
    {
        const std::string upper = "화장실이 어디야";
        const std::string lower_wanted = "화장실이 어디야";

        const std::string lower = ztd::lower(upper);

        CHECK_EQ(lower, lower_wanted);
    }

    SUBCASE("empty")
    {
        const std::string upper;
        const std::string lower_wanted;

        const std::string lower = ztd::lower(upper);

        CHECK_EQ(lower, lower_wanted);
    }
}

TEST_CASE("ztd::upper")
{
    SUBCASE("latin")
    {
        const std::string lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
        const std::string upper_wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";

        const std::string upper = ztd::upper(lower);

        CHECK_EQ(upper, upper_wanted);
    }

    SUBCASE("special")
    {
        const std::string lower = "!@$%^&*()_+";
        const std::string upper_wanted = "!@$%^&*()_+";

        const std::string upper = ztd::upper(lower);

        CHECK_EQ(upper, upper_wanted);
    }

    SUBCASE("mixed special")
    {
        const std::string lower = "@a@A@a@";
        const std::string upper_wanted = "@A@A@A@";

        const std::string upper = ztd::upper(lower);

        CHECK_EQ(upper, upper_wanted);
    }

    SUBCASE("japanese")
    {
        const std::string lower = "化粧室はどこですか";
        const std::string upper_wanted = "化粧室はどこですか";

        const std::string upper = ztd::upper(lower);

        CHECK_EQ(upper, upper_wanted);
    }

    SUBCASE("korean")
    {
        const std::string lower = "화장실이 어디야";
        const std::string upper_wanted = "화장실이 어디야";

        const std::string upper = ztd::upper(lower);

        CHECK_EQ(upper, upper_wanted);
    }

    SUBCASE("empty")
    {
        const std::string lower;
        const std::string upper_wanted;

        const std::string upper = ztd::upper(lower);

        CHECK_EQ(upper, upper_wanted);
    }
}

TEST_CASE("ztd::replace")
{
    SUBCASE("replace")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "foo";
        const std::string str_replace = "baz";

        const std::string result_wanted = "bazbar bazbar bazbar";
        const std::string result = ztd::replace(str, str_find, str_replace);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str empty")
    {
        const std::string str;
        const std::string str_find = "foo";
        const std::string str_replace = "baz";

        const std::string result_wanted;
        const std::string result = ztd::replace(str, str_find, str_replace);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("find empty")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find;
        const std::string str_replace = "baz";

        const std::string result_wanted = "foobar foobar foobar";
        const std::string result = ztd::replace(str, str_find, str_replace);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("replace empty")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "foo";
        const std::string str_replace;

        const std::string result_wanted = "bar bar bar";
        const std::string result = ztd::replace(str, str_find, str_replace);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("missing")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "fooo";
        const std::string str_replace = "baz";

        const std::string result_wanted = "foobar foobar foobar";
        const std::string result = ztd::replace(str, str_find, str_replace);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("count neg")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "foo";
        const std::string str_replace = "baz";

        const std::string result_wanted = "bazbar bazbar bazbar";
        const std::string result = ztd::replace(str, str_find, str_replace, -5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("count 0")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "foo";
        const std::string str_replace = "baz";

        const std::string result_wanted = "foobar foobar foobar";
        const std::string result = ztd::replace(str, str_find, str_replace, 0);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("count 1")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "foo";
        const std::string str_replace = "baz";

        const std::string result_wanted = "bazbar foobar foobar";
        const std::string result = ztd::replace(str, str_find, str_replace, 1);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("count 2")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "foo";
        const std::string str_replace = "baz";

        const std::string result_wanted = "bazbar bazbar foobar";
        const std::string result = ztd::replace(str, str_find, str_replace, 2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("count 3")
    {
        const std::string str = "foobar foobar foobar";
        const std::string str_find = "foo";
        const std::string str_replace = "baz";

        const std::string result_wanted = "bazbar bazbar bazbar";
        const std::string result = ztd::replace(str, str_find, str_replace, 3);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::capitalize")
{
    SUBCASE("space")
    {
        const std::string str = " will not capitalize the first letter.";

        const std::string result_wanted = " will not capitalize the first letter.";
        const std::string result = ztd::capitalize(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("lower")
    {
        const std::string str = "capitalize only the first letter.";

        const std::string result_wanted = "Capitalize only the first letter.";
        const std::string result = ztd::capitalize(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("upper")
    {
        const std::string str = "AAAA BBBB CCCC";

        const std::string result_wanted = "Aaaa bbbb cccc";
        const std::string result = ztd::capitalize(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("mixed")
    {
        const std::string str = "aAaA BbBb CcCc";

        const std::string result_wanted = "Aaaa bbbb cccc";
        const std::string result = ztd::capitalize(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted;
        const std::string result = ztd::capitalize(str);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::center")
{
    SUBCASE("even string even width")
    {
        const std::string str = "even";

        const std::string result_wanted = "   even   ";
        const std::string result = ztd::center(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("even string odd width")
    {
        const std::string str = "even";

        const std::string result_wanted = "  even   ";
        const std::string result = ztd::center(str, 9);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("odd string odd width")
    {
        const std::string str = "odd";

        const std::string result_wanted = " odd ";
        const std::string result = ztd::center(str, 5);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("odd string even width")
    {
        const std::string str = "odd";

        const std::string result_wanted = "   odd    ";
        const std::string result = ztd::center(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted = "     ";
        const std::string result = ztd::center(str, 5);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::count")
{
    SUBCASE("count")
    {
        const std::string str = "zaaazaaaz";

        const u64 result_wanted = 6;
        const u64 result = ztd::count(str, "a");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("multichar")
    {
        const std::string str = "zaaazaaaz";

        const u64 result_wanted = 2;
        const u64 result = ztd::count(str, "aaa");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("zero")
    {
        const std::string str = "zaaazaaaz";

        const u64 result_wanted = 0;
        const u64 result = ztd::count(str, "w");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const u64 result_wanted = 0;
        const u64 result = ztd::count(str, "w");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("char overload")
    {
        SUBCASE("char")
        {
            const std::string str = "zaaazaaaz";

            const u64 result_wanted = 6;
            const u64 result = ztd::count(str, 'a');

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("zero")
        {
            const std::string str = "zaaazaaaz";

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, 'w');

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("empty")
        {
            const std::string str;

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, 'w');

            CHECK_EQ(result, result_wanted);
        }
    }

    SUBCASE("(start, end) overload")
    {
        SUBCASE("empty")
        {
            const std::string str;

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, "w", 0, std::string_view::npos);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("start/end")
        {
            const std::string str = "zaaazaaaz";

            const u64 result_wanted = 3;
            const u64 result = ztd::count(str, "a", 4, 15);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("start/end 2")
        {
            const std::string str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

            const u64 result_wanted = 3;
            const u64 result = ztd::count(str, "a", 0, 4);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("multichar")
        {
            const std::string str = "zaaazaaaz";

            const u64 result_wanted = 1;
            const u64 result = ztd::count(str, "aaa", 4, 15);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("zero")
        {
            const std::string str = "zaaazaaaz";

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, "w", 0, 15);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("same")
        {
            const std::string str = "aaaa";

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, "a", 1, 1);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("large start")
        {
            const std::string str = "aaaa";

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, "a", 3, 2);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("large end")
        {
            const std::string str = "aaaa";

            const u64 result_wanted = 4;
            const u64 result = ztd::count(str, "a", 0, 100);

            CHECK_EQ(result, result_wanted);
        }
    }

    SUBCASE("(start, end) char overload")
    {
        SUBCASE("empty")
        {
            const std::string str;

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, 'w', 0, std::string_view::npos);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("start/end")
        {
            const std::string str = "zaaazaaaz";

            const u64 result_wanted = 3;
            const u64 result = ztd::count(str, 'a', 4, 15);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("start/end 2")
        {
            const std::string str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

            const u64 result_wanted = 3;
            const u64 result = ztd::count(str, 'a', 0, 4);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("zero")
        {
            const std::string str = "zaaazaaaz";

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, 'w', 0, 15);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("same")
        {
            const std::string str = "aaaa";

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, 'a', 1, 1);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("large start")
        {
            const std::string str = "aaaa";

            const u64 result_wanted = 0;
            const u64 result = ztd::count(str, 'a', 3, 2);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("large end")
        {
            const std::string str = "aaaa";

            const u64 result_wanted = 4;
            const u64 result = ztd::count(str, 'a', 0, 100);

            CHECK_EQ(result, result_wanted);
        }
    }
}

TEST_CASE("ztd::expandtabs")
{
    SUBCASE("4")
    {
        const std::string str = "01\t012\t0123\t01234";
        const std::string result_wanted = "01  012 0123    01234";

        const std::string result = ztd::expandtabs(str, 4);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("8")
    {
        const std::string str = "01\t012\t0123\t01234";
        const std::string result_wanted = "01      012     0123    01234";

        const std::string result = ztd::expandtabs(str, 8);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("LF")
    {
        const std::string str = "01\t012\t0123\t01234\n012345\t0123";
        const std::string result_wanted = "01      012     0123    01234\n012345  0123";

        const std::string result = ztd::expandtabs(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("CR")
    {
        const std::string str = "01\t012\t0123\t01234\r012345\t0123";
        const std::string result_wanted = "01      012     0123    01234\r012345  0123";

        const std::string result = ztd::expandtabs(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("CRLF")
    {
        const std::string str = "01\t012\t0123\t01234\r\n012345\t0123";
        const std::string result_wanted = "01      012     0123    01234\r\n012345  0123";

        const std::string result = ztd::expandtabs(str);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::isalnum")
{
    SUBCASE("all alpha")
    {
        const std::string str = "alphastring";

        CHECK_EQ(ztd::isalnum(str), true);
    }

    SUBCASE("all digit")
    {
        const std::string str = "69420";

        CHECK_EQ(ztd::isalnum(str), true);
    }

    SUBCASE("mixed")
    {
        const std::string str = "alnumstring69420";

        CHECK_EQ(ztd::isalnum(str), true);
    }

    SUBCASE("special ")
    {
        const std::string str = "!@#$%^&*()_+{}";

        CHECK_EQ(ztd::isalnum(str), false);
    }

    SUBCASE("space")
    {
        const std::string str = "not alnum string";

        CHECK_EQ(ztd::isalnum(str), false);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::isalnum(str), false);
    }
}

TEST_CASE("ztd::isalpha")
{
    SUBCASE("true")
    {
        const std::string str = "alphastring";

        CHECK_EQ(ztd::isalpha(str), true);
    }

    SUBCASE("false")
    {
        const std::string str = "not alpha string?";

        CHECK_EQ(ztd::isalpha(str), false);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::isalpha(str), false);
    }
}

#if 0
TEST_CASE("ztd::isascii")
{
    SUBCASE("isascii")
    {
        for (isize i = 0; i <= 127; ++i)
        {
            unsigned char ch = char(i);
            CHECK_EQ(ztd::isascii(std::to_string(ch)), true);
        }
    }

    SUBCASE("empty")
    {
        CHECK_EQ(ztd::isascii(""), true);
    }

    SUBCASE("false")
    {
        CHECK_EQ(ztd::isascii("ß"), false);
    }
}
#endif

TEST_CASE("ztd::isdecimal")
{
    SUBCASE("true")
    {
        const std::string str = "1234567890";

        CHECK_EQ(ztd::isdecimal(str), true);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::isdecimal(str), false);
    }

    SUBCASE("false")
    {
        const std::string str = "1234567890a";

        CHECK_EQ(ztd::isdecimal(str), false);
    }
}

TEST_CASE("ztd::isdigit")
{
    SUBCASE("true")
    {
        const std::string str = "1234567890";

        CHECK_EQ(ztd::isdigit(str), true);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::isdigit(str), false);
    }

    SUBCASE("false")
    {
        const std::string str = "1234567890a";

        CHECK_EQ(ztd::isdigit(str), false);
    }
}

TEST_CASE("ztd::isnumeric")
{
    SUBCASE("true")
    {
        const std::string str = "1234567890";

        CHECK_EQ(ztd::isnumeric(str), true);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::isnumeric(str), false);
    }

    SUBCASE("false")
    {
        const std::string str = "1234567890a";

        CHECK_EQ(ztd::isnumeric(str), false);
    }
}

TEST_CASE("ztd::islower")
{
    SUBCASE("true")
    {
        const std::string str = "string";

        CHECK_EQ(ztd::islower(str), true);
    }

    SUBCASE("true special")
    {
        const std::string str = "string string!@#$%^&*_+(){}[]";

        CHECK_EQ(ztd::islower(str), true);
    }

    SUBCASE("false")
    {
        const std::string str = "STRING";

        CHECK_EQ(ztd::islower(str), false);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::islower(str), false);
    }
}

TEST_CASE("ztd::isupper")
{
    SUBCASE("true")
    {
        const std::string str = "STRING";

        CHECK_EQ(ztd::isupper(str), true);
    }

    SUBCASE("true special")
    {
        const std::string str = "STRING STRING!@#$%^&*_+(){}[]";

        CHECK_EQ(ztd::isupper(str), true);
    }

    SUBCASE("false")
    {
        const std::string str = "string";

        CHECK_EQ(ztd::isupper(str), false);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::isupper(str), false);
    }
}

TEST_CASE("ztd::isspace")
{
    SUBCASE("true")
    {
        const std::string str = "    ";

        CHECK_EQ(ztd::isspace(str), true);
    }

    SUBCASE("false")
    {
        const std::string str = " a ";

        CHECK_EQ(ztd::isspace(str), false);
    }

    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::isspace(str), false);
    }
}

TEST_CASE("ztd::istitle")
{
    SUBCASE("empty")
    {
        const std::string str;

        CHECK_EQ(ztd::istitle(str), false);
    }

    SUBCASE("true")
    {
        const std::string str = "A String A";

        CHECK_EQ(ztd::istitle(str), true);
    }

    SUBCASE("false")
    {
        const std::string str = "A string A";

        CHECK_EQ(ztd::istitle(str), false);
    }

    SUBCASE("python example")
    {
        const std::string str = "They'Re Bill'S Friends From The Uk";

        CHECK_EQ(ztd::istitle(str), true);
    }
}

TEST_CASE("ztd::title")
{
    SUBCASE("title")
    {
        const std::string str = "String";

        const std::string result_wanted = "String";
        const std::string result = ztd::title(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted;
        const std::string result = ztd::title(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("all lower")
    {
        const std::string str = "string a string";

        const std::string result_wanted = "String A String";
        const std::string result = ztd::title(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("all upper")
    {
        const std::string str = "STRING A STRING";

        const std::string result_wanted = "String A String";
        const std::string result = ztd::title(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("mixed")
    {
        const std::string str = "StRiNg a sTrInG";

        const std::string result_wanted = "String A String";
        const std::string result = ztd::title(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("special")
    {
        const std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

        const std::string result_wanted = "String ~!@#$%^&*()-_+{}|<>?,./";
        const std::string result = ztd::title(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("python example")
    {
        const std::string str = "they're bill's friends from the UK";

        const std::string result_wanted = "They'Re Bill'S Friends From The Uk";
        const std::string result = ztd::title(str);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::swapcase")
{
    SUBCASE("swapcase")
    {
        const std::string str = "String";

        const std::string result_wanted = "sTRING";
        const std::string result = ztd::swapcase(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted;
        const std::string result = ztd::swapcase(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("all lower")
    {
        const std::string str = "string string";

        const std::string result_wanted = "STRING STRING";
        const std::string result = ztd::swapcase(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("all upper")
    {
        const std::string str = "STRING STRING";

        const std::string result_wanted = "string string";
        const std::string result = ztd::swapcase(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("mixed")
    {
        const std::string str = "StRiNg sTrInG";

        const std::string result_wanted = "sTrInG StRiNg";
        const std::string result = ztd::swapcase(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("special")
    {
        const std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

        const std::string result_wanted = "sTRING ~!@#$%^&*()-_+{}|<>?,./";
        const std::string result = ztd::swapcase(str);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::ljust")
{
    SUBCASE("ljust")
    {
        const std::string str = "string";

        const std::string result_wanted = "string    ";
        const std::string result = ztd::ljust(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted = "          ";
        const std::string result = ztd::ljust(str, 10);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::rjust")
{
    SUBCASE("rjust")
    {
        const std::string str = "string";

        const std::string result_wanted = "    string";
        const std::string result = ztd::rjust(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted = "          ";
        const std::string result = ztd::rjust(str, 10);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::lstrip")
{
    SUBCASE("lstrip")
    {
        const std::string str = "  a  ";

        const std::string result_wanted = "a  ";
        const std::string result = ztd::lstrip(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("chars")
    {
        const std::string str = "z a z";

        const std::string result_wanted = " a z";
        const std::string result = ztd::lstrip(str, "z");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted;
        const std::string result = ztd::lstrip(str);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::rstrip")
{
    SUBCASE("rstrip")
    {
        const std::string str = "  a  ";

        const std::string result_wanted = "  a";
        const std::string result = ztd::rstrip(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("chars")
    {
        const std::string str = "z a z";

        const std::string result_wanted = "z a ";
        const std::string result = ztd::rstrip(str, "z");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted;
        const std::string result = ztd::rstrip(str);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::strip")
{
    SUBCASE("strip")
    {
        const std::string str = "  a  ";

        const std::string result_wanted = "a";
        const std::string result = ztd::strip(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("chars")
    {
        const std::string str = "z a z";

        const std::string result_wanted = " a ";
        const std::string result = ztd::strip(str, "z");

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("chars all")
    {
        const std::string str = "\n\r\t ";

        const std::string result_wanted;
        const std::string result = ztd::strip(str);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted;
        const std::string result = ztd::strip(str);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::removeprefix")
{
    SUBCASE("removeprefix")
    {
        const std::string str1 = "foobar test string";
        const std::string str2 = "foobar ";

        const std::string result_wanted = "test string";
        const std::string result = ztd::removeprefix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("missing")
    {
        const std::string str1 = "foobar test string";
        const std::string str2 = "zbar";

        const std::string result_wanted = "foobar test string";
        const std::string result = ztd::removeprefix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str empty")
    {
        const std::string str1;
        const std::string str2 = "foobar";

        const std::string result_wanted;
        const std::string result = ztd::removeprefix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("prefix empty")
    {
        const std::string str1 = "foobar";
        const std::string str2;

        const std::string result_wanted = "foobar";
        const std::string result = ztd::removeprefix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("char overload")
    {
        SUBCASE("char")
        {
            const std::string str1 = "@foobar@";

            const std::string result_wanted = "foobar@";
            const std::string result = ztd::removeprefix(str1, '@');

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("missing")
        {
            const std::string str1 = "@foobar@";

            const std::string result_wanted = "@foobar@";
            const std::string result = ztd::removeprefix(str1, 'Z');

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("str empty")
        {
            const std::string str1;

            const std::string result_wanted;
            const std::string result = ztd::removeprefix(str1, '@');

            CHECK_EQ(result, result_wanted);
        }
    }
}

TEST_CASE("ztd::removesuffix")
{
    SUBCASE("removesuffix")
    {
        const std::string str1 = "foobar test string";
        const std::string str2 = " string";

        const std::string result_wanted = "foobar test";
        const std::string result = ztd::removesuffix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("missing")
    {
        const std::string str1 = "foobar test string";
        const std::string str2 = "zbar";

        const std::string result_wanted = "foobar test string";
        const std::string result = ztd::removesuffix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str empty")
    {
        const std::string str1;
        const std::string str2 = "foobar";

        const std::string result_wanted;
        const std::string result = ztd::removesuffix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("prefix empty")
    {
        const std::string str1 = "foobar";
        const std::string str2;

        const std::string result_wanted = "foobar";
        const std::string result = ztd::removesuffix(str1, str2);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("char overload")
    {
        SUBCASE("char")
        {
            const std::string str1 = "@foobar@";

            const std::string result_wanted = "@foobar";
            const std::string result = ztd::removesuffix(str1, '@');

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("missing")
        {
            const std::string str1 = "@foobar@";

            const std::string result_wanted = "@foobar@";
            const std::string result = ztd::removesuffix(str1, 'Z');

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("str empty")
        {
            const std::string str1;

            const std::string result_wanted;
            const std::string result = ztd::removesuffix(str1, '@');

            CHECK_EQ(result, result_wanted);
        }
    }
}

TEST_CASE("ztd::partition")
{
    SUBCASE("partition")
    {
        const std::string str = "foobar$foobar$foobar";

        const std::string result_wanted_1 = "foobar";
        const std::string result_wanted_2 = "$";
        const std::string result_wanted_3 = "foobar$foobar";

        const auto result = ztd::partition(str, "$");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("str empty")
    {
        const std::string str;

        const std::string result_wanted_1;
        const std::string result_wanted_2;
        const std::string result_wanted_3;

        const auto result = ztd::partition(str, "$");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("sep empty")
    {
        const std::string str = "foobar$foobar$foobar";

        const std::string result_wanted_1 = "foobar$foobar$foobar";
        const std::string result_wanted_2;
        const std::string result_wanted_3;

        const auto result = ztd::partition(str, "");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("missing")
    {
        const std::string str = "foobar$foobar$foobar";

        const std::string result_wanted_1 = "foobar$foobar$foobar";
        const std::string result_wanted_2;
        const std::string result_wanted_3;

        const auto result = ztd::partition(str, "^");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("recombine")
    {
        const std::string str = "split/split/split";

        const std::string& recombine_wanted = str;

        const std::string result_wanted_1 = "split";
        const std::string result_wanted_2 = "/";
        const std::string result_wanted_3 = "split/split";

        const auto result = ztd::partition(str, "/");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);

        const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

        CHECK_EQ(recombine_wanted, recombine);
    }

    SUBCASE("multi")
    {
        const std::string str = "test.tar.tar.test";

        const std::string result_wanted_1 = "test";
        const std::string result_wanted_2 = ".tar.";
        const std::string result_wanted_3 = "tar.test";

        const auto result = ztd::partition(str, ".tar.");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("char overload")
    {
        SUBCASE("char")
        {
            const std::string str = "foobar$foobar$foobar";

            const std::string result_wanted_1 = "foobar";
            const std::string result_wanted_2 = "$";
            const std::string result_wanted_3 = "foobar$foobar";

            const auto result = ztd::partition(str, '$');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);
        }

        SUBCASE("str empty")
        {
            const std::string str;

            const std::string result_wanted_1;
            const std::string result_wanted_2;
            const std::string result_wanted_3;

            const auto result = ztd::partition(str, '$');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);
        }

        SUBCASE("missong")
        {
            const std::string str = "foobar$foobar$foobar";

            const std::string result_wanted_1 = "foobar$foobar$foobar";
            const std::string result_wanted_2;
            const std::string result_wanted_3;

            const auto result = ztd::partition(str, '^');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);
        }

        SUBCASE("recombine")
        {
            const std::string str = "split/split/split";

            const std::string& recombine_wanted = str;

            const std::string result_wanted_1 = "split";
            const std::string result_wanted_2 = "/";
            const std::string result_wanted_3 = "split/split";

            const auto result = ztd::partition(str, '/');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);

            const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

            CHECK_EQ(recombine_wanted, recombine);
        }
    }
}

TEST_CASE("ztd::rpartition")
{
    SUBCASE("rpartition")
    {
        const std::string str = "foobar$foobar$foobar";

        const std::string result_wanted_1 = "foobar$foobar";
        const std::string result_wanted_2 = "$";
        const std::string result_wanted_3 = "foobar";

        const auto result = ztd::rpartition(str, "$");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("str empty")
    {
        const std::string str;

        const std::string result_wanted_1;
        const std::string result_wanted_2;
        const std::string result_wanted_3;

        const auto result = ztd::rpartition(str, "$");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("sep empty")
    {
        const std::string str = "foobar$foobar$foobar";

        const std::string result_wanted_1;
        const std::string result_wanted_2;
        const std::string result_wanted_3 = "foobar$foobar$foobar";

        const auto result = ztd::rpartition(str, "");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("missing")
    {
        const std::string str = "foobar$foobar$foobar";

        const std::string result_wanted_1;
        const std::string result_wanted_2;
        const std::string result_wanted_3 = "foobar$foobar$foobar";

        const auto result = ztd::rpartition(str, "^");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("recombine")
    {
        const std::string str = "split/split/split";

        const std::string& recombine_wanted = str;

        const std::string result_wanted_1 = "split/split";
        const std::string result_wanted_2 = "/";
        const std::string result_wanted_3 = "split";

        const auto result = ztd::rpartition(str, "/");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);

        const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

        CHECK_EQ(recombine_wanted, recombine);
    }

    SUBCASE("multi")
    {
        const std::string str = "test.tar.tar.test";

        const std::string result_wanted_1 = "test.tar";
        const std::string result_wanted_2 = ".tar.";
        const std::string result_wanted_3 = "test";

        const auto result = ztd::rpartition(str, ".tar.");

        const auto& result_1 = result[0];
        const auto& result_2 = result[1];
        const auto& result_3 = result[2];

        CHECK_EQ(result_1, result_wanted_1);
        CHECK_EQ(result_2, result_wanted_2);
        CHECK_EQ(result_3, result_wanted_3);
    }

    SUBCASE("char overload")
    {
        SUBCASE("char")
        {
            const std::string str = "foobar$foobar$foobar";

            const std::string result_wanted_1 = "foobar$foobar";
            const std::string result_wanted_2 = "$";
            const std::string result_wanted_3 = "foobar";

            const auto result = ztd::rpartition(str, '$');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);
        }

        SUBCASE("str empty")
        {
            const std::string str;

            const std::string result_wanted_1;
            const std::string result_wanted_2;
            const std::string result_wanted_3;

            const auto result = ztd::rpartition(str, '$');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);
        }

        SUBCASE("missing")
        {
            const std::string str = "foobar$foobar$foobar";

            const std::string result_wanted_1;
            const std::string result_wanted_2;
            const std::string result_wanted_3 = "foobar$foobar$foobar";

            const auto result = ztd::rpartition(str, '^');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);
        }

        SUBCASE("recombine")
        {
            const std::string str = "split/split/split";

            const std::string& recombine_wanted = str;

            const std::string result_wanted_1 = "split/split";
            const std::string result_wanted_2 = "/";
            const std::string result_wanted_3 = "split";

            const auto result = ztd::rpartition(str, '/');

            const auto& result_1 = result[0];
            const auto& result_2 = result[1];
            const auto& result_3 = result[2];

            CHECK_EQ(result_1, result_wanted_1);
            CHECK_EQ(result_2, result_wanted_2);
            CHECK_EQ(result_3, result_wanted_3);

            const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

            CHECK_EQ(recombine_wanted, recombine);
        }
    }
}

TEST_CASE("ztd::splitlines")
{
    SUBCASE("newline keepends")
    {
        const std::string str = "foo\nfoo";

        const std::vector<std::string> result_wanted = {"foo", "foo"};
        const std::vector<std::string> result = ztd::splitlines(str, false);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("python example 1")
    {
        const std::string str = "ab c\n\nde fg\rkl\r\n";

        const std::vector<std::string> result_wanted = {"ab c", "", "de fg", "kl"};
        const std::vector<std::string> result = ztd::splitlines(str, false);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("python example 2")
    {
        const std::string str = "ab c\n\nde fg\rkl\r\n";

        const std::vector<std::string> result_wanted = {"ab c\n", "\n", "de fg\r", "kl\r\n"};
        const std::vector<std::string> result = ztd::splitlines(str, true);

        CHECK_EQ(result, result_wanted);
    }
}

TEST_CASE("ztd::zfill")
{
    SUBCASE("str")
    {
        const std::string str = "string";

        const std::string result_wanted = "0000string";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str pos")
    {
        const std::string str = "+string";

        const std::string result_wanted = "+000string";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str neg")
    {
        const std::string str = "-string";

        const std::string result_wanted = "-000string";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str int")
    {
        const std::string str = "420";

        const std::string result_wanted = "0000000420";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str int pos")
    {
        const std::string str = "+420";

        const std::string result_wanted = "+000000420";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("str int neg")
    {
        const std::string str = "-420";

        const std::string result_wanted = "-000000420";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("empty")
    {
        const std::string str;

        const std::string result_wanted = "0000000000";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("sign pos only")
    {
        const std::string str = "+";

        const std::string result_wanted = "+000000000";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("sign neg only")
    {
        const std::string str = "-";

        const std::string result_wanted = "-000000000";
        const std::string result = ztd::zfill(str, 10);

        CHECK_EQ(result, result_wanted);
    }

    SUBCASE("sign no fill")
    {
        const std::string str = "string";

        const std::string result_wanted = "string";
        const std::string result = ztd::zfill(str, str.size());

        CHECK_EQ(result, result_wanted);
    }
}
