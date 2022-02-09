/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>

#include "../src/ztd.hxx"

TEST_CASE("::lower")
{

    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lower_wanted = "abcdefghijklmnopqrstuvwxyz";

    std::string lower = ztd::lower(upper);

    REQUIRE(lower.compare(lower_wanted) == 0);
}

TEST_CASE("::upper")
{

    std::string lower = "abcdefghijklmnopqrstuvwxyz";
    std::string upper_wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string upper = ztd::upper(lower);

    REQUIRE(upper.compare(upper_wanted) == 0);
}

TEST_CASE("::contains")
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    REQUIRE(ztd::contains(str1, str2));
}

TEST_CASE("::contains char")
{
    std::string str1 = "abcd";
    char str2 = 'c';

    REQUIRE(ztd::contains(str1, str2));
}

TEST_CASE("::contains_any")
{
    std::string str1 = "foobar";
    std::vector<std::string> v1{"foo", "bar"};

    REQUIRE(ztd::contains_any(str1, v1));

    std::string str2 = "bazbar";
    std::vector<std::string> v2{"foo", "bar"};

    REQUIRE(ztd::contains_any(str2, v2));
}

TEST_CASE("::same")
{
    std::string str1 = "same string";
    std::string str2 = "same string";
    std::string str3 = str2;

    REQUIRE(ztd::same(str1, str2));

    REQUIRE(ztd::same(str1, str3));
}

TEST_CASE("::not_same")
{
    std::string str1 = "not same string";
    std::string str2 = "same string";

    REQUIRE(ztd::not_same(str1, str2));
}

TEST_CASE("::isame")
{
    std::string str1 = "SAME string";
    std::string str2 = "same STRING";

    REQUIRE(ztd::isame(str1, str2));
}

TEST_CASE("::not_isame")
{
    std::string str1 = "NOT same string";
    std::string str2 = "same string";

    REQUIRE(ztd::not_isame(str1, str2));
}

TEST_CASE("::prefix")
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar";

    REQUIRE(ztd::prefix(str1, str2));
}

TEST_CASE("::suffix")
{
    std::string str1 = "foobar test string";
    std::string str2 = "string";

    REQUIRE(ztd::suffix(str1, str2));
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

TEST_CASE("::split")
{
    std::string str = "foo foo foo";

    std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    std::vector<std::string> result = ztd::split(str, " ");

    REQUIRE(result == result_wanted);
}

TEST_CASE("::join")
{
    std::vector<std::string> vec = {"foo", "foo", "foo"};

    std::string result_wanted = "foo foo foo";
    std::string result = ztd::join(vec, " ");

    REQUIRE(result == result_wanted);
}

TEST_CASE("::build_path 1")
{
    std::string result_wanted = "/tmp";
    std::string result = ztd::build_path("/tmp");

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::build_path 2")
{
    std::string result_wanted = "/tmp/test";
    std::string result = ztd::build_path("/tmp", "test");

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::build_path 3")
{
    std::string result_wanted = "/tmp/test/test";
    std::string result = ztd::build_path("/tmp", "test", "test");

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::build_path 4")
{
    std::string result_wanted = "/tmp/test/test/test";
    std::string result = ztd::build_path("/tmp", "test", "test", "test");

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::build_path 5")
{
    std::string result_wanted = "/tmp/test/test/test/test";
    std::string result = ztd::build_path("/tmp", "test", "test", "test", "test");

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::build_path 6")
{
    std::string result_wanted = "/tmp/test/test/test/test/test";
    std::string result = ztd::build_path("/tmp", "test", "test", "test", "test", "test");

    REQUIRE(ztd::same(result, result_wanted));
}

TEST_CASE("::clear")
{
    std::string str1 = "a";

    ztd::clear(str1);

    REQUIRE(ztd::same(str1, ""));
}

TEST_CASE("::empty")
{
    std::string str1 = "";
    std::string str2 = "a";

    REQUIRE(ztd::empty(str1) == true);
    REQUIRE(ztd::empty(str2) == false);
}

TEST_CASE("::nempty")
{
    std::string str1 = "";
    std::string str2 = "a";

    REQUIRE(ztd::nempty(str1) == false);
    REQUIRE(ztd::nempty(str2) == true);
}

TEST_CASE("::b")
{
    std::string str1 = "";
    std::string str2 = "a";

    REQUIRE(ztd::b(str1) == false);
    REQUIRE(ztd::b(str2) == true);
}

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
