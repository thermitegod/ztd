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

#include "../../src/ztd.hxx"

TEST_CASE("::lower")
{

    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";
    std::string lower_wanted = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";

    std::string lower = ztd::lower(upper);

    REQUIRE(lower.compare(lower_wanted) == 0);
}

TEST_CASE("::upper")
{

    std::string lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
    std::string upper_wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";

    std::string upper = ztd::upper(lower);

    REQUIRE(upper.compare(upper_wanted) == 0);
}

TEST_CASE("::contains(std::string, std::string)")
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    REQUIRE(ztd::contains(str1, str2));

    std::string str3 = "foobarbaz";
    std::string str4 = "buz";

    REQUIRE(!ztd::contains(str3, str4));
}

TEST_CASE("::contains(std::string, char*)")
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    REQUIRE(ztd::contains(str1, str2));

    std::string str3 = "foobarbaz";
    const char* str4 = "bur";

    REQUIRE(!ztd::contains(str3, str4));

    std::string str5 = "foobarbaz";
    const char* str6 = nullptr;

    REQUIRE(!ztd::contains(str5, str6));
}

TEST_CASE("::contains(char*, std::string)")
{
    const char* str1 = "foobarbaz";
    std::string str2 = "bar";

    REQUIRE(ztd::contains(str1, str2));

    const char* str3 = "foobarbaz";
    std::string str4 = "bur";

    REQUIRE(!ztd::contains(str3, str4));

    const char* str5 = nullptr;
    std::string str6 = "bar";

    REQUIRE(!ztd::contains(str5, str6));
}

TEST_CASE("::contains(char*, char*)")
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    REQUIRE(ztd::contains(str1, str2));

    const char* str3 = "foobarbaz";
    const char* str4 = "bur";

    REQUIRE(!ztd::contains(str3, str4));

    const char* str5 = "foobarbaz";
    const char* str6 = nullptr;

    REQUIRE(!ztd::contains(str5, str6));

    const char* str7 = nullptr;
    const char* str8 = "bar";

    REQUIRE(!ztd::contains(str7, str8));

    const char* str9 = nullptr;
    const char* str0 = nullptr;

    REQUIRE(!ztd::contains(str9, str0));
}

TEST_CASE("::contains(std::string, char)")
{
    std::string str1 = "abcd";
    const char str2 = 'c';

    REQUIRE(ztd::contains(str1, str2));

    std::string str3 = "abcd";
    const char str4 = 'z';

    REQUIRE(!ztd::contains(str3, str4));
}

TEST_CASE("::contains(char*, char)")
{
    const char* str1 = "abcd";
    const char str2 = 'c';

    REQUIRE(ztd::contains(str1, str2));

    const char* str3 = "abcd";
    const char str4 = 'z';

    REQUIRE(!ztd::contains(str3, str4));

    const char* str5 = nullptr;
    const char str6 = 'z';

    REQUIRE(!ztd::contains(str5, str6));
}

TEST_CASE("::contains_any")
{
    std::string str1 = "foobar";
    std::vector<std::string> v1{"foo", "bar"};

    REQUIRE(ztd::contains_any(str1, v1));

    std::string str2 = "bazbar";
    std::vector<std::string> v2{"foo", "bar"};

    REQUIRE(ztd::contains_any(str2, v2));

    std::string str3 = "foobar";
    std::vector<std::string> v3{"fuz", "baz"};

    REQUIRE(!ztd::contains_any(str3, v3));
}

TEST_CASE("::same(std::string, std::string)")
{
    std::string str1 = "same string";
    std::string str2 = "same string";
    std::string str3 = str2;

    REQUIRE(ztd::same(str1, str2));

    REQUIRE(ztd::same(str1, str3));

    std::string str4 = "same string";
    std::string str5 = "not same string";

    REQUIRE(!ztd::same(str4, str5));
}

TEST_CASE("::same(std::string, char*)")
{
    std::string str1 = "not same";
    const char* str2 = nullptr;

    REQUIRE(!ztd::same(str1, str2));

    std::string str3 = "same string";
    const char* str4 = "same string";

    REQUIRE(ztd::same(str3, str4));
}

TEST_CASE("::same(char*, std::string)")
{
    const char* str1 = nullptr;
    std::string str2 = "not same";

    REQUIRE(!ztd::same(str1, str2));

    const char* str3 = "same string";
    std::string str4 = "same string";

    REQUIRE(ztd::same(str3, str4));
}

TEST_CASE("::same(char*, char*)")
{
    const char* str1 = "not same";
    const char* str2 = nullptr;

    REQUIRE(!ztd::same(str1, str2));

    const char* str3 = nullptr;
    const char* str4 = "not same";

    REQUIRE(!ztd::same(str3, str4));

    const char* str5 = "same string";
    const char* str6 = "same string";

    REQUIRE(ztd::same(str5, str6));

    const char* str7 = nullptr;
    const char* str8 = nullptr;

    REQUIRE(!ztd::same(str7, str8));
}

TEST_CASE("::isame(std::string, std::string)")
{
    std::string str1 = "SAME string";
    std::string str2 = "same STRING";
    std::string str3 = str2;

    REQUIRE(ztd::isame(str1, str2));

    REQUIRE(ztd::isame(str1, str3));

    std::string str4 = "SAME string";
    std::string str5 = "not same STRING";

    REQUIRE(!ztd::isame(str4, str5));
}

TEST_CASE("::isame(std::string, char*)")
{
    std::string str1 = "not same";
    const char* str2 = nullptr;

    REQUIRE(!ztd::isame(str1, str2));

    std::string str3 = "SAME string";
    const char* str4 = "same STRING";

    REQUIRE(ztd::isame(str3, str4));
}

TEST_CASE("::isame(char*, std::string)")
{
    const char* str1 = nullptr;
    std::string str2 = "not same";

    REQUIRE(!ztd::isame(str1, str2));

    const char* str3 = "SAME string";
    std::string str4 = "same STRING";

    REQUIRE(ztd::isame(str3, str4));
}

TEST_CASE("::isame(char*, char*)")
{
    const char* str1 = "not SAME";
    const char* str2 = nullptr;

    REQUIRE(!ztd::isame(str1, str2));

    const char* str3 = nullptr;
    const char* str4 = "not same";

    REQUIRE(!ztd::isame(str3, str4));

    const char* str5 = "SAME string";
    const char* str6 = "same STRING";

    REQUIRE(ztd::isame(str5, str6));

    const char* str7 = nullptr;
    const char* str8 = nullptr;

    REQUIRE(!ztd::isame(str7, str8));
}

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

TEST_CASE("::remove_prefix")
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar";

    std::string result_wanted = "test string";
    std::string result = ztd::remove_prefix(str1, str2);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::remove_suffix")
{
    std::string str1 = "foobar test string";
    std::string str2 = "string";

    std::string result_wanted = "foobar test";
    std::string result = ztd::remove_suffix(str1, str2);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::remove_before")
{
    std::string str1 = "Just a test string in a test case";
    std::string str2 = "test";

    std::string result_wanted = "case";
    std::string result = ztd::remove_before(str1, str2);

    INFO(str1);
    INFO(result);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::remove_after")
{
    std::string str1 = "Just a test string in a test case";
    std::string str2 = "test";

    std::string result_wanted = "Just a";
    std::string result = ztd::remove_after(str1, str2);

    INFO(str1);
    INFO(result);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::replace")
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar bazbar bazbar";
    std::string result = ztd::replace(str, str_find, str_replace);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::replace_first")
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar foobar foobar";
    std::string result = ztd::replace_first(str, str_find, str_replace);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::replace_last")
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar bazbar";
    std::string result = ztd::replace_last(str, str_find, str_replace);

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::replace_multiple")
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace);

    REQUIRE(ztd::same(result, result_wanted));
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
