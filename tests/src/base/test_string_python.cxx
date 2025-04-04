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
#include <string_view>
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::split")
{
    std::string str;
    std::string sep;
    i32 maxsplit = -1; // split all
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
            wanted = {"a", "b,c,d,e,f"};
        }

        SUBCASE("maxsplit 2")
        {
            maxsplit = 2;
            wanted = {"a", "b", "c,d,e,f"};
        }

        SUBCASE("maxsplit 3")
        {
            maxsplit = 3;
            wanted = {"a", "b", "c", "d,e,f"};
        }

        SUBCASE("maxsplit 4")
        {
            maxsplit = 4;
            wanted = {"a", "b", "c", "d", "e,f"};
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
            wanted = {"a", "b<>c<>d<>e<>f"};
        }

        SUBCASE("maxsplit 2")
        {
            maxsplit = 2;
            wanted = {"a", "b", "c<>d<>e<>f"};
        }

        SUBCASE("maxsplit 3")
        {
            maxsplit = 3;
            wanted = {"a", "b", "c", "d<>e<>f"};
        }

        SUBCASE("maxsplit 4")
        {
            maxsplit = 4;
            wanted = {"a", "b", "c", "d", "e<>f"};
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
            wanted = {"a", "b<=>c<=>d<=>e<=>f"};
        }

        SUBCASE("maxsplit 2")
        {
            maxsplit = 2;
            wanted = {"a", "b", "c<=>d<=>e<=>f"};
        }

        SUBCASE("maxsplit 3")
        {
            maxsplit = 3;
            wanted = {"a", "b", "c", "d<=>e<=>f"};
        }

        SUBCASE("maxsplit 4")
        {
            maxsplit = 4;
            wanted = {"a", "b", "c", "d", "e<=>f"};
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

    CHECK_EQ(ztd::split(str, sep, maxsplit), wanted);
}

TEST_CASE("ztd::rsplit")
{
    std::string str;
    std::string sep;
    i32 maxsplit = -1; // split all
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

TEST_CASE("ztd::lower")
{
    std::string upper;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("latin")
    {
        upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        wanted = "abcdefghijklmnopqrstuvwxyz1234567890";
    }

    SUBCASE("special")
    {
        upper = "!@$%^&*()_+";
        wanted = "!@$%^&*()_+";
    }

    SUBCASE("mixed special")
    {
        upper = "@A@a@A@";
        wanted = "@a@a@a@";
    }

    SUBCASE("japanese")
    {
        upper = "化粧室はどこですか";
        wanted = "化粧室はどこですか";
    }

    SUBCASE("korean")
    {
        upper = "화장실이 어디야";
        wanted = "화장실이 어디야";
    }

    CHECK_EQ(ztd::lower(upper), wanted);
}

TEST_CASE("ztd::upper")
{
    std::string lower;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("latin")
    {
        lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
        wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";
    }

    SUBCASE("special")
    {
        lower = "!@$%^&*()_+";
        wanted = "!@$%^&*()_+";
    }

    SUBCASE("mixed special")
    {
        lower = "@a@A@a@";
        wanted = "@A@A@A@";
    }

    SUBCASE("japanese")
    {
        lower = "化粧室はどこですか";
        wanted = "化粧室はどこですか";
    }

    SUBCASE("korean")
    {
        lower = "화장실이 어디야";
        wanted = "화장실이 어디야";
    }

    CHECK_EQ(ztd::upper(lower), wanted);
}

TEST_CASE("ztd::replace")
{
    std::string str;
    std::string str_find;
    std::string str_replace;
    std::string wanted;
    i32 count = -1; // replace all

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

TEST_CASE("ztd::capitalize")
{
    std::string str;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("space")
    {
        str = " will not capitalize the first letter.";
        wanted = " will not capitalize the first letter.";
    }

    SUBCASE("lower")
    {
        str = "capitalize only the first letter.";
        wanted = "Capitalize only the first letter.";
    }

    SUBCASE("upper")
    {
        str = "AAAA BBBB CCCC";
        wanted = "Aaaa bbbb cccc";
    }

    SUBCASE("mixed")
    {
        str = "aAaA BbBb CcCc";
        wanted = "Aaaa bbbb cccc";
    }

    CHECK_EQ(ztd::capitalize(str), wanted);
}

TEST_CASE("ztd::center")
{
    std::string str;
    std::string wanted;
    u32 width = 0;

    SUBCASE("even string even width")
    {
        str = "even";
        wanted = "   even   ";
        width = 10;
    }

    SUBCASE("even string odd width")
    {
        str = "even";
        wanted = "  even   ";
        width = 9;
    }

    SUBCASE("odd string odd width")
    {
        str = "odd";
        wanted = " odd ";
        width = 5;
    }

    SUBCASE("odd string even width")
    {
        str = "odd";
        wanted = "   odd    ";
        width = 10;
    }

    SUBCASE("str empty")
    {
        str = "";
        wanted = "     ";
        width = 5;
    }

    CHECK_EQ(ztd::center(str, width), wanted);
}

TEST_CASE("ztd::count")
{
    SUBCASE("default")
    {
        std::string str;
        std::string find;
        u64 wanted = 0;

        SUBCASE("count")
        {
            str = "zaaazaaaz";
            find = "a";
            wanted = 6;
        }

        SUBCASE("multichar")
        {
            str = "zaaazaaaz";
            find = "aaa";
            wanted = 2;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = "w";
            wanted = 0;
        }

        SUBCASE("empty")
        {
            str = "";
            find = "a";
            wanted = 0;
        }

        CHECK_EQ(ztd::count(str, find), wanted);
    }

    SUBCASE("char overload")
    {
        std::string str;
        char find = 0;
        u64 wanted = 0;

        SUBCASE("char")
        {
            str = "zaaazaaaz";
            find = 'a';
            wanted = 6;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = 'w';
            wanted = 0;
        }

        SUBCASE("empty")
        {
            str = "";
            find = 'w';
            wanted = 0;
        }

        CHECK_EQ(ztd::count(str, find), wanted);
    }

    SUBCASE("(start, end) overload")
    {
        std::string str;
        std::string find;
        usize start = 0;
        usize end = 0;
        u64 wanted = 0;

        SUBCASE("empty")
        {
            str = "";
            find = "w";
            start = 0;
            end = std::string_view::npos;
            wanted = 0;
        }

        SUBCASE("start/end")
        {
            str = "zaaazaaaz";
            find = "a";
            start = 4;
            end = 15;
            wanted = 3;
        }

        SUBCASE("start/end 2")
        {
            str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            find = "a";
            start = 0;
            end = 4;
            wanted = 3;
        }

        SUBCASE("multichar")
        {
            str = "zaaazaaaz";
            find = "aaa";
            start = 4;
            end = 15;
            wanted = 1;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = "w";
            start = 0;
            end = 15;
            wanted = 0;
        }

        SUBCASE("same")
        {
            str = "aaaa";
            find = "a";
            start = 1;
            end = 1;
            wanted = 0;
        }

        SUBCASE("large start")
        {
            str = "aaaa";
            find = "a";
            start = 3;
            end = 2;
            wanted = 0;
        }

        SUBCASE("large end")
        {
            str = "aaaa";
            find = "a";
            start = 0;
            end = 100;
            wanted = 4;
        }

        CHECK_EQ(ztd::count(str, find, start, end), wanted);
    }

    SUBCASE("(start, end) char overload")
    {
        std::string str;
        char find = 0;
        usize start = 0;
        usize end = 0;
        u64 wanted = 0;

        SUBCASE("empty")
        {
            str = "";
            find = 'w';
            start = 0;
            end = std::string_view::npos;
            wanted = 0;
        }

        SUBCASE("start/end")
        {
            str = "zaaazaaaz";
            find = 'a';
            start = 4;
            end = 15;
            wanted = 3;
        }

        SUBCASE("start/end 2")
        {
            str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            find = 'a';
            start = 0;
            end = 4;
            wanted = 3;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = 'w';
            start = 0;
            end = 15;
            wanted = 0;
        }

        SUBCASE("same")
        {
            str = "aaaa";
            find = 'a';
            start = 1;
            end = 1;
            wanted = 0;
        }

        SUBCASE("large start")
        {
            str = "aaaa";
            find = 'a';
            start = 3;
            end = 2;
            wanted = 0;
        }

        SUBCASE("large end")
        {
            str = "aaaa";
            find = 'a';
            start = 0;
            end = 100;
            wanted = 4;
        }

        CHECK_EQ(ztd::count(str, find, start, end), wanted);
    }
}

TEST_CASE("ztd::expandtabs")
{
    std::string str;
    std::string wanted;
    u32 tabsize = 8;

    SUBCASE("4")
    {
        str = "01\t012\t0123\t01234";
        wanted = "01  012 0123    01234";
        tabsize = 4;
    }

    SUBCASE("8")
    {
        str = "01\t012\t0123\t01234";
        wanted = "01      012     0123    01234";
        tabsize = 8;
    }

    SUBCASE("LF")
    {
        str = "01\t012\t0123\t01234\n012345\t0123";
        wanted = "01      012     0123    01234\n012345  0123";
    }

    SUBCASE("CR")
    {
        str = "01\t012\t0123\t01234\r012345\t0123";
        wanted = "01      012     0123    01234\r012345  0123";
    }

    SUBCASE("CRLF")
    {
        str = "01\t012\t0123\t01234\r\n012345\t0123";
        wanted = "01      012     0123    01234\r\n012345  0123";
    }

    CHECK_EQ(ztd::expandtabs(str, tabsize), wanted);
}

TEST_CASE("ztd::isalnum")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("all alpha")
    {
        str = "alphastring";
        wanted = true;
    }

    SUBCASE("all digit")
    {
        str = "69420";
        wanted = true;
    }

    SUBCASE("mixed")
    {
        str = "alnumstring69420";
        wanted = true;
    }

    SUBCASE("specia ")
    {
        str = "!@#$%^&*()_+{}";
        wanted = false;
    }

    SUBCASE("space")
    {
        str = "not alnum string";
        wanted = false;
    }

    CHECK_EQ(ztd::isalnum(str), wanted);
}

TEST_CASE("ztd::isalpha")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "alphastring";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = "not alpha string?";
        wanted = false;
    }

    CHECK_EQ(ztd::isalpha(str), wanted);
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
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "1234567890";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = "1234567890a";
        wanted = false;
    }

    CHECK_EQ(ztd::isdecimal(str), wanted);
}

TEST_CASE("ztd::isdigit")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "1234567890";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = "1234567890a";
        wanted = false;
    }

    CHECK_EQ(ztd::isdigit(str), wanted);
}

TEST_CASE("ztd::isnumeric")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "1234567890";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = "1234567890a";
        wanted = false;
    }

    CHECK_EQ(ztd::isnumeric(str), wanted);
}

TEST_CASE("ztd::islower")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "string";
        wanted = true;
    }

    SUBCASE("true special")
    {
        str = "string string!@#$%^&*_+(){}[]";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = "STRING";
        wanted = false;
    }

    CHECK_EQ(ztd::islower(str), wanted);
}

TEST_CASE("ztd::isupper")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "STRING";
        wanted = true;
    }

    SUBCASE("true special")
    {
        str = "STRING STRING!@#$%^&*_+(){}[]";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = "string";
        wanted = false;
    }

    CHECK_EQ(ztd::isupper(str), wanted);
}

TEST_CASE("ztd::isspace")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "    ";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = " a ";
        wanted = false;
    }

    CHECK_EQ(ztd::isspace(str), wanted);
}

TEST_CASE("ztd::istitle")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("true")
    {
        str = "A String A";
        wanted = true;
    }

    SUBCASE("false")
    {
        str = "A string A";
        wanted = false;
    }

    SUBCASE("python example")
    {
        str = "They'Re Bill'S Friends From The Uk";
        wanted = true;
    }

    CHECK_EQ(ztd::istitle(str), wanted);
}

TEST_CASE("ztd::title")
{
    std::string str;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("title")
    {
        str = "String";
        wanted = "String";
    }

    SUBCASE("all lower")
    {
        str = "string a string";
        wanted = "String A String";
    }

    SUBCASE("all upper")
    {
        str = "STRING A STRING";
        wanted = "String A String";
    }

    SUBCASE("mixed")
    {
        str = "StRiNg a sTrInG";
        wanted = "String A String";
    }

    SUBCASE("special")
    {
        str = "String ~!@#$%^&*()-_+{}|<>?,./";
        wanted = "String ~!@#$%^&*()-_+{}|<>?,./";
    }

    SUBCASE("python example")
    {
        str = "they're bill's friends from the UK";
        wanted = "They'Re Bill'S Friends From The Uk";
    }

    CHECK_EQ(ztd::title(str), wanted);
}

TEST_CASE("ztd::swapcase")
{
    std::string str;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("swapcase")
    {
        str = "String";
        wanted = "sTRING";
    }

    SUBCASE("all lower")
    {
        str = "string string";
        wanted = "STRING STRING";
    }

    SUBCASE("all upper")
    {
        str = "STRING STRING";
        wanted = "string string";
    }

    SUBCASE("mixed")
    {
        str = "StRiNg sTrInG";
        wanted = "sTrInG StRiNg";
    }

    SUBCASE("special")
    {
        str = "String ~!@#$%^&*()-_+{}|<>?,./";
        wanted = "sTRING ~!@#$%^&*()-_+{}|<>?,./";
    }

    CHECK_EQ(ztd::swapcase(str), wanted);
}

TEST_CASE("ztd::ljust")
{
    std::string str;
    std::string wanted;
    usize width = 10;
    char fillchar = ' ';

    SUBCASE("empty")
    {
        str = "";
        wanted = "          ";
    }

    SUBCASE("empty fillchar")
    {
        str = "";
        fillchar = 'x';
        wanted = "xxxxxxxxxx";
    }

    SUBCASE("ljust")
    {
        str = "string";
        wanted = "string    ";
    }

    CHECK_EQ(ztd::ljust(str, width, fillchar), wanted);
}

TEST_CASE("ztd::rjust")
{
    std::string str;
    std::string wanted;
    usize width = 10;
    char fillchar = ' ';

    SUBCASE("empty")
    {
        str = "";
        wanted = "          ";
    }

    SUBCASE("empty fillchar")
    {
        str = "";
        fillchar = 'x';
        wanted = "xxxxxxxxxx";
    }

    SUBCASE("rjust")
    {
        str = "string";
        wanted = "    string";
    }

    CHECK_EQ(ztd::rjust(str, width, fillchar), wanted);
}

TEST_CASE("ztd::lstrip")
{
    std::string str;
    std::string chars = " \r\n\t";
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("lstrip")
    {
        str = "  a  ";
        wanted = "a  ";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = " a z";
    }

    CHECK_EQ(ztd::lstrip(str, chars), wanted);
}

TEST_CASE("ztd::rstrip")
{
    std::string str;
    std::string chars = " \r\n\t";
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("rstrip")
    {
        str = "  a  ";
        wanted = "  a";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = "z a ";
    }

    CHECK_EQ(ztd::rstrip(str, chars), wanted);
}

TEST_CASE("ztd::strip")
{
    std::string str;
    std::string chars = " \r\n\t";
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("strip")
    {
        str = "  a  ";
        wanted = "a";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = " a ";
    }

    CHECK_EQ(ztd::strip(str, chars), wanted);
}

TEST_CASE("ztd::removeprefix")
{
    SUBCASE("default")
    {
        std::string str;
        std::string prefix;
        std::string wanted;

        SUBCASE("removeprefix")
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

        CHECK_EQ(ztd::removeprefix(str, prefix), wanted);
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

        CHECK_EQ(ztd::removeprefix(str, prefix), wanted);
    }
}

TEST_CASE("ztd::removesuffix")
{
    SUBCASE("default")
    {
        std::string str;
        std::string suffix;
        std::string wanted;

        SUBCASE("removesuffix")
        {
            str = "foobar test string";
            suffix = " string";
            wanted = "foobar test";
        }

        SUBCASE("missing")
        {
            str = "foobar test string";
            suffix = "zbar";
            wanted = "foobar test string";
        }

        SUBCASE("str empty")
        {
            str = "";
            suffix = "foobar";
            wanted = "";
        }

        SUBCASE("prefix empty")
        {
            str = "foobar";
            suffix = "";
            wanted = "foobar";
        }

        CHECK_EQ(ztd::removesuffix(str, suffix), wanted);
    }

    SUBCASE("char overload")
    {
        std::string str;
        char suffix = 0;
        std::string wanted;

        SUBCASE("char")
        {
            str = "@foobar@";
            suffix = '@';
            wanted = "@foobar";
        }

        SUBCASE("missing")
        {
            str = "@foobar@";
            suffix = 'Z';
            wanted = "@foobar@";
        }

        SUBCASE("str empty")
        {
            str = "";
            suffix = '@';
            wanted = "";
        }

        CHECK_EQ(ztd::removesuffix(str, suffix), wanted);
    }
}

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

TEST_CASE("ztd::rpartition")
{
    SUBCASE("default")
    {
        std::string str;
        std::string sep;
        std::string wanted_1;
        std::string wanted_2;
        std::string wanted_3;

        SUBCASE("rpartition")
        {
            str = "foobar$foobar$foobar";
            sep = "$";
            wanted_1 = "foobar$foobar";
            wanted_2 = "$";
            wanted_3 = "foobar";
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
            wanted_1 = "";
            wanted_2 = "";
            wanted_3 = "foobar$foobar$foobar";
        }

        SUBCASE("missing")
        {
            str = "foobar$foobar$foobar";
            sep = "^";
            wanted_1 = "";
            wanted_2 = "";
            wanted_3 = "foobar$foobar$foobar";
        }

        SUBCASE("multi")
        {
            str = "test.tar.tar.test";
            sep = ".tar.";
            wanted_1 = "test.tar";
            wanted_2 = ".tar.";
            wanted_3 = "test";
        }

        const auto [r1, r2, r3] = ztd::rpartition(str, sep);
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
            wanted_1 = "foobar$foobar";
            wanted_2 = "$";
            wanted_3 = "foobar";
        }

        SUBCASE("str empty")
        {
            str = "";
            sep = '$';
            wanted_1 = "";
            wanted_2 = "";
            wanted_3 = "";
        }

        SUBCASE("missing")
        {
            str = "foobar$foobar$foobar";
            sep = '^';
            wanted_1 = "";
            wanted_2 = "";
            wanted_3 = "foobar$foobar$foobar";
        }

        const auto [r1, r2, r3] = ztd::rpartition(str, sep);
        CHECK_EQ(r1, wanted_1);
        CHECK_EQ(r2, wanted_2);
        CHECK_EQ(r3, wanted_3);

        const auto recombine = std::format("{}{}{}", r1, r2, r3);
        CHECK_EQ(recombine, str);
    }
}

TEST_CASE("ztd::splitlines")
{
    std::string str;
    bool keepends = false;
    std::vector<std::string> wanted;

    SUBCASE("newline keepends")
    {
        str = "foo\nfoo";
        wanted = {"foo", "foo"};
    }

    SUBCASE("python example 1")
    {
        str = "ab c\n\nde fg\rkl\r\n";
        wanted = {"ab c", "", "de fg", "kl"};
    }

    SUBCASE("python example 2")
    {
        str = "ab c\n\nde fg\rkl\r\n";
        keepends = true;
        wanted = {"ab c\n", "\n", "de fg\r", "kl\r\n"};
    }

    CHECK_EQ(ztd::splitlines(str, keepends), wanted);
}

TEST_CASE("ztd::zfill")
{
    std::string str;
    usize width = 10;
    std::string wanted;

    SUBCASE("str")
    {
        str = "string";
        wanted = "0000string";
    }

    SUBCASE("str pos")
    {
        str = "+string";
        wanted = "+000string";
    }

    SUBCASE("str neg")
    {
        str = "-string";
        wanted = "-000string";
    }

    SUBCASE("str int")
    {
        str = "420";
        wanted = "0000000420";
    }

    SUBCASE("str int pos")
    {
        str = "+420";
        wanted = "+000000420";
    }

    SUBCASE("str int neg")
    {
        str = "-420";
        wanted = "-000000420";
    }

    SUBCASE("empty")
    {
        str = "";
        wanted = "0000000000";
    }

    SUBCASE("sign pos only")
    {
        str = "+";
        wanted = "+000000000";
    }

    SUBCASE("sign neg only")
    {
        str = "-";
        wanted = "-000000000";
    }

    SUBCASE("sign no fill")
    {
        str = "string";
        width = str.size();
        wanted = "string";
    }

    CHECK_EQ(ztd::zfill(str, width), wanted);
}
