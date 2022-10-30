/**
 * Copyright (C) 2022 Brandon Zorn <brandonzorn@cock.li>
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

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "ztd/ztd.hxx"

/**
 * split
 */
TEST(string_python, split)
{
    const std::string str = "foo foo foo";

    const std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    const std::vector<std::string> result = ztd::split(str, " ");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__empty_string)
{
    const std::string str = "";

    const std::vector<std::string> result_wanted = {""};
    const std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_first)
{
    const std::string str = ",test,test";

    const std::vector<std::string> result_wanted = {"", "test", "test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_second)
{
    const std::string str = "test,test";

    const std::vector<std::string> result_wanted = {"test", "test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_multiple_empty)
{
    const std::string str = "test,,,test";

    const std::vector<std::string> result_wanted = {"test", "", "", "test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_missing)
{
    const std::string str = "test|test";

    const std::vector<std::string> result_wanted = {"test|test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars)
{
    const std::string str = "a<>b<>c";

    const std::vector<std::string> result_wanted = {"a", "b", "c"};
    const std::vector<std::string> result = ztd::split(str, "<>");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__no_delimiter)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a,b,c"};
    const std::vector<std::string> result = ztd::split(str);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit_0)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a,b,c"};
    const std::vector<std::string> result = ztd::split(str, ",", 0);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit_1)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a", "b,c"};
    const std::vector<std::string> result = ztd::split(str, ",", 1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit_2)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a", "b", "c"};
    const std::vector<std::string> result = ztd::split(str, ",", 2);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit__larger_than_real_maxsplit)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a", "b", "c"};
    const std::vector<std::string> result = ztd::split(str, ",", 500);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__filepath)
{
    const std::string str = "/home/user/download";

    const std::vector<std::string> result_wanted = {"", "home", "user", "download"};
    const std::vector<std::string> result = ztd::split(str, "/");

    ASSERT_TRUE(result == result_wanted);
}

/**
 * rsplit
 */
TEST(string_python, rsplit)
{
    const std::string str = "foo foo foo";

    const std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    const std::vector<std::string> result = ztd::rsplit(str, " ");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__empty_string)
{
    const std::string str = "";

    const std::vector<std::string> result_wanted = {""};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_first)
{
    const std::string str = ",test,test";

    const std::vector<std::string> result_wanted = {"", "test", "test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_second)
{
    const std::string str = "test,test";

    const std::vector<std::string> result_wanted = {"test", "test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_empty)
{
    const std::string str = "test,,,test";

    const std::vector<std::string> result_wanted = {"test", "", "", "test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_missing)
{
    const std::string str = "test|test";

    const std::vector<std::string> result_wanted = {"test|test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars)
{
    const std::string str = "a<>b<>c";

    const std::vector<std::string> result_wanted = {"a", "b", "c"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__no_delimiter)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a,b,c"};
    const std::vector<std::string> result = ztd::rsplit(str);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit_0)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a,b,c"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 0);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit_1)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a,b", "c"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit_2)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a", "b", "c"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 2);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit__larger_than_real_maxsplit)
{
    const std::string str = "a,b,c";

    const std::vector<std::string> result_wanted = {"a", "b", "c"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 500);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__filepath)
{
    const std::string str = "/home/user/download";

    const std::vector<std::string> result_wanted = {"", "home", "user", "download"};
    const std::vector<std::string> result = ztd::split(str, "/");

    ASSERT_TRUE(result == result_wanted);
}

/**
 * join vector<string>
 */
TEST(string_python, join__vector_string)
{
    const std::vector<std::string> vec = {"foo", "foo", "foo"};

    const std::string result_wanted = "foo foo foo";
    const std::string result = ztd::join(vec, " ");

    ASSERT_TRUE(result == result_wanted);
}

/**
 * join vector<string_view>
 */
TEST(string_python, join__vector_string_view)
{
    using namespace std::literals::string_view_literals;

    const std::vector<std::string_view> vec = {"foo"sv, "foo"sv, "foo"sv};

    const std::string result_wanted = "foo foo foo";
    const std::string result = ztd::join(vec, " ");

    ASSERT_TRUE(result == result_wanted);
}

/**
 * lower
 */
TEST(string_python, lower_latin)
{
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    const std::string lower_wanted = "abcdefghijklmnopqrstuvwxyz1234567890";

    const std::string lower = ztd::lower(upper);

    ASSERT_TRUE(ztd::same(lower, lower_wanted));
}

TEST(string_python, lower_special)
{
    const std::string upper = "!@$%^&*()_+";
    const std::string lower_wanted = "!@$%^&*()_+";

    const std::string lower = ztd::lower(upper);

    ASSERT_TRUE(ztd::same(lower, lower_wanted));
}

TEST(string_python, lower_mixed_special)
{
    const std::string upper = "@A@a@A@";
    const std::string lower_wanted = "@a@a@a@";

    const std::string lower = ztd::lower(upper);

    ASSERT_TRUE(ztd::same(lower, lower_wanted));
}

TEST(string_python, lower_japanese)
{
    const std::string upper = "化粧室はどこですか";
    const std::string lower_wanted = "化粧室はどこですか";

    const std::string lower = ztd::lower(upper);

    ASSERT_TRUE(ztd::same(lower, lower_wanted));
}

TEST(string_python, lower_korean)
{
    const std::string upper = "화장실이 어디야";
    const std::string lower_wanted = "화장실이 어디야";

    const std::string lower = ztd::lower(upper);

    ASSERT_TRUE(ztd::same(lower, lower_wanted));
}

/**
 * upper
 */
TEST(string_python, upper_latin)
{
    const std::string lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
    const std::string upper_wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";

    const std::string upper = ztd::upper(lower);

    ASSERT_TRUE(ztd::same(upper, upper_wanted));
}

TEST(string_python, upper_special)
{
    const std::string lower = "!@$%^&*()_+";
    const std::string upper_wanted = "!@$%^&*()_+";

    const std::string upper = ztd::upper(lower);

    ASSERT_TRUE(ztd::same(upper, upper_wanted));
}

TEST(string_python, upper_mixed_special)
{
    const std::string lower = "@a@A@a@";
    const std::string upper_wanted = "@A@A@A@";

    const std::string upper = ztd::upper(lower);

    ASSERT_TRUE(ztd::same(upper, upper_wanted));
}

TEST(string_python, upper_japanese)
{
    const std::string lower = "化粧室はどこですか";
    const std::string upper_wanted = "化粧室はどこですか";

    const std::string upper = ztd::upper(lower);

    ASSERT_TRUE(ztd::same(upper, upper_wanted));
}

TEST(string_python, upper_korean)
{
    const std::string lower = "화장실이 어디야";
    const std::string upper_wanted = "화장실이 어디야";

    const std::string upper = ztd::upper(lower);

    ASSERT_TRUE(ztd::same(upper, upper_wanted));
}

/**
 * replace
 */
TEST(string_python, replace)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar bazbar";
    const std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__missing)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "fooo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_neg)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar bazbar";
    const std::string result = ztd::replace(str, str_find, str_replace, -5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_0)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace, 0);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_1)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar foobar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace, 1);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_2)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace, 2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_3)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar bazbar";
    const std::string result = ztd::replace(str, str_find, str_replace, 3);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * capitalize
 */
TEST(string_python, capitalize__space)
{
    const std::string str = " will not capitalize the first letter.";

    const std::string result_wanted = " will not capitalize the first letter.";
    const std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, capitalize__lower)
{
    const std::string str = "capitalize only the first letter.";

    const std::string result_wanted = "Capitalize only the first letter.";
    const std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, capitalize__upper)
{
    const std::string str = "AAAA BBBB CCCC";

    const std::string result_wanted = "Aaaa bbbb cccc";
    const std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, capitalize__mixed)
{
    const std::string str = "aAaA BbBb CcCc";

    const std::string result_wanted = "Aaaa bbbb cccc";
    const std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * center
 */
TEST(string_python, center__even_string_even_width)
{
    const std::string str = "even";

    const std::string result_wanted = "   even   ";
    const std::string result = ztd::center(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, center__even_string_odd_width)
{
    const std::string str = "even";

    const std::string result_wanted = "  even   ";
    const std::string result = ztd::center(str, 9);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, center__odd_string_odd_width)
{
    const std::string str = "odd";

    const std::string result_wanted = " odd ";
    const std::string result = ztd::center(str, 5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, center__odd_string_even_width)
{
    const std::string str = "odd";

    const std::string result_wanted = "   odd    ";
    const std::string result = ztd::center(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * count
 */
TEST(string_python, count)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 6;
    const u64 result = ztd::count(str, "a");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, count__start_end)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 3;
    const u64 result = ztd::count(str, "a", 4, 15);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, count__start_end_2)
{
    const std::string str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    const u64 result_wanted = 3;
    const u64 result = ztd::count(str, "a", 0, 4);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, count__start_end__same)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "a", 1, 1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, count__start_end__large_start)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "a", 3, 2);

    ASSERT_TRUE(result == result_wanted);
}

/**
 * endswith
 */
TEST(string_python, endswith__true)
{
    const std::string str = "foobarstring";

    bool result = ztd::endswith(str, "string");

    ASSERT_TRUE(result);
}

TEST(string_python, endswith__false)
{
    const std::string str = "foobarstring";

    bool result = ztd::endswith(str, "zstring");

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__start_end_true)
{
    const std::string str = "foobarstring";

    bool result = ztd::endswith(str, "bar", 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, endswith__start_end_false)
{
    const std::string str = "foobarstring";

    bool result = ztd::endswith(str, "zbar", 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__start_end__same)
{
    const std::string str = "aaaa";

    bool result = ztd::endswith(str, "a", 2, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, endswithstart_end__large_start)
{
    const std::string str = "aaaa";

    bool result = ztd::endswith(str, "a", 3, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__long_suffix)
{
    const std::string str = "foobar";

    bool result = ztd::endswith(str, "longfoobar");

    ASSERT_FALSE(result);
}

/**
 * endswith vector<string> overload
 */
TEST(string_python, endswith__vector_string__true)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> suffixes = {"string"};

    bool result = ztd::endswith(str, suffixes);

    ASSERT_TRUE(result);
}

TEST(string_python, endswith__vector_string__false)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> suffixes = {"foo", "zstring"};

    bool result = ztd::endswith(str, suffixes);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string__start_end_true)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> suffixes = {"foo", "bar"};

    bool result = ztd::endswith(str, suffixes, 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, endswith__vector_string__start_end_false)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> suffixes = {"zfoo", "zbar"};

    bool result = ztd::endswith(str, suffixes, 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string__start_end__same)
{
    const std::string str = "aaaa";
    const std::vector<std::string> suffixes = {"a", "aa"};

    bool result = ztd::endswith(str, suffixes, 2, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string__start_end__large_start)
{
    const std::string str = "aaaa";
    const std::vector<std::string> suffixes = {"a", "aa"};

    bool result = ztd::endswith(str, suffixes, 3, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string__long_suffix)
{
    const std::string str = "foobar";
    const std::vector<std::string> suffixes = {"longfoobar", "verylongfoobar"};

    bool result = ztd::endswith(str, suffixes);

    ASSERT_FALSE(result);
}

/**
 * endswith vector<string_view> overload
 */
TEST(string_python, endswith__vector_string_view__true)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> suffixes = {"string"sv};

    bool result = ztd::endswith(str, suffixes);

    ASSERT_TRUE(result);
}

TEST(string_python, endswith__vector_string_view__false)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> suffixes = {"foo"sv, "zstring"sv};

    bool result = ztd::endswith(str, suffixes);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string_view__start_end_true)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> suffixes = {"foo"sv, "bar"sv};

    bool result = ztd::endswith(str, suffixes, 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, endswith__vector_string_view__start_end_false)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> suffixes = {"zfoo"sv, "zbar"sv};

    bool result = ztd::endswith(str, suffixes, 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string_view__start_end__same)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "aaaa";
    const std::vector<std::string_view> suffixes = {"a"sv, "aa"sv};

    bool result = ztd::endswith(str, suffixes, 2, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string_view__start_end__large_start)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "aaaa";
    const std::vector<std::string_view> suffixes = {"a"sv, "aa"sv};

    bool result = ztd::endswith(str, suffixes, 3, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__vector_string_view__long_suffix)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobar";
    const std::vector<std::string_view> suffixes = {"longfoobar"sv, "verylongfoobar"sv};

    bool result = ztd::endswith(str, suffixes);

    ASSERT_FALSE(result);
}

/**
 * startswith
 */
TEST(string_python, startswith__true)
{
    const std::string str = "foobarstring";

    bool result = ztd::startswith(str, "foo");

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__false)
{
    const std::string str = "foobarstring";

    bool result = ztd::startswith(str, "zfoo");

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__start_end_true)
{
    const std::string str = "foobarstring";

    bool result = ztd::startswith(str, "foo", 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__start_end_false)
{
    const std::string str = "foobarstring";

    bool result = ztd::startswith(str, "zfoo", 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__start_end__same)
{
    const std::string str = "aaaa";

    bool result = ztd::startswith(str, "a", 2, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__start_end__large_start)
{
    const std::string str = "aaaa";

    bool result = ztd::startswith(str, "a", 3, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__long_suffix)
{
    const std::string str = "foobar";

    bool result = ztd::startswith(str, "foobarlong");

    ASSERT_FALSE(result);
}

/**
 * startswith vector<string> overload
 */
TEST(string_python, startswith__vector_string__true)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> prefixes = {"foo"};

    bool result = ztd::startswith(str, prefixes);

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__vector_string__false)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> prefixes = {"bar", "string"};

    bool result = ztd::startswith(str, prefixes);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string__start_end_true)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> prefixes = {"foo", "bar"};

    bool result = ztd::startswith(str, prefixes, 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__vector_string__start_end_false)
{
    const std::string str = "foobarstring";
    const std::vector<std::string> prefixes = {"zfoo", "zbar"};

    bool result = ztd::startswith(str, prefixes, 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string__start_end__same)
{
    const std::string str = "aaaa";
    const std::vector<std::string> prefixes = {"a", "aa"};

    bool result = ztd::startswith(str, prefixes, 2, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string__start_end__large_start)
{
    const std::string str = "aaaa";
    const std::vector<std::string> prefixes = {"a", "aa"};

    bool result = ztd::startswith(str, prefixes, 3, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string__long_suffix)
{
    const std::string str = "foobar";
    const std::vector<std::string> prefixes = {"foobarlong", "foobarverylong"};

    bool result = ztd::startswith(str, prefixes);

    ASSERT_FALSE(result);
}

/**
 * startswith vector<string_view> overload
 */
TEST(string_python, startswith__vector_string_view__true)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> prefixes = {"foo"sv};

    bool result = ztd::startswith(str, prefixes);

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__vector_string_view__false)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> prefixes = {"bar"sv, "string"sv};

    bool result = ztd::startswith(str, prefixes);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string_view__start_end_true)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> prefixes = {"foo"sv, "bar"sv};

    bool result = ztd::startswith(str, prefixes, 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__vector_string_view__start_end_false)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobarstring";
    const std::vector<std::string_view> prefixes = {"zfoo"sv, "zbar"sv};

    bool result = ztd::startswith(str, prefixes, 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string_view__start_end__same)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "aaaa";
    const std::vector<std::string_view> prefixes = {"a"sv, "aa"sv};

    bool result = ztd::startswith(str, prefixes, 2, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string_view__start_end__large_start)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "aaaa";
    const std::vector<std::string_view> prefixes = {"a"sv, "aa"sv};

    bool result = ztd::startswith(str, prefixes, 3, 2);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__vector_string_view__long_suffix)
{
    using namespace std::literals::string_view_literals;

    const std::string str = "foobar";
    const std::vector<std::string_view> prefixes = {"foobarlong"sv, "foobarverylong"sv};

    bool result = ztd::startswith(str, prefixes);

    ASSERT_FALSE(result);
}

/**
 * expandtabs
 */
TEST(string_python, expandtabs__4)
{
    const std::string str = "01\t012\t0123\t01234";
    const std::string result_wanted = "01  012 0123    01234";

    const std::string result = ztd::expandtabs(str, 4);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, expandtabs__8)
{
    const std::string str = "01\t012\t0123\t01234";
    const std::string result_wanted = "01      012     0123    01234";

    const std::string result = ztd::expandtabs(str, 8);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * isalpha
 */
TEST(string_python, isalpha__true)
{
    const std::string str = "alphastring";

    ASSERT_TRUE(ztd::isalpha(str));
}

TEST(string_python, isalpha__false)
{
    const std::string str = "not alpha string?";

    ASSERT_FALSE(ztd::isalpha(str));
}

/**
 * isdigit
 */
TEST(string_python, isdigit__true)
{
    const std::string str = "1234567890";

    ASSERT_TRUE(ztd::isdigit(str));
}

TEST(string_python, isdigit__false)
{
    const std::string str = "1234567890a";

    ASSERT_FALSE(ztd::isdigit(str));
}

/**
 * islower
 */
TEST(string_python, islower__true)
{
    const std::string str = "string";

    ASSERT_TRUE(ztd::islower(str));
}

TEST(string_python, islower__true_special)
{
    const std::string str = "string string!@#$%^&*_+(){}[]";

    ASSERT_TRUE(ztd::islower(str));
}

TEST(string_python, islower__false)
{
    const std::string str = "STRING";

    ASSERT_FALSE(ztd::islower(str));
}

/**
 * isupper
 */
TEST(string_python, isupper__true)
{
    const std::string str = "STRING";

    ASSERT_TRUE(ztd::isupper(str));
}

TEST(string_python, isupper__true_special)
{
    const std::string str = "STRING STRING!@#$%^&*_+(){}[]";

    ASSERT_TRUE(ztd::isupper(str));
}

TEST(string_python, isupper__false)
{
    const std::string str = "string";

    ASSERT_FALSE(ztd::isupper(str));
}

/**
 * isspace
 */
TEST(string_python, isspace__true)
{
    const std::string str = "    ";

    ASSERT_TRUE(ztd::isspace(str));
}

TEST(string_python, isspace__false)
{
    const std::string str = " a ";

    ASSERT_FALSE(ztd::isspace(str));
}

/**
 * istitle
 */
TEST(string_python, istitle__empty)
{
    const std::string str = "";

    ASSERT_FALSE(ztd::istitle(str));
}

TEST(string_python, istitle__true)
{
    const std::string str = "A String A";

    ASSERT_TRUE(ztd::istitle(str));
}

TEST(string_python, istitle__false)
{
    const std::string str = "A string A";

    ASSERT_FALSE(ztd::istitle(str));
}

TEST(string_python, istitle__from_the_python_example)
{
    const std::string str = "They'Re Bill'S Friends From The Uk";

    ASSERT_TRUE(ztd::istitle(str));
}

/**
 * title
 */
TEST(string_python, title)
{
    const std::string str = "String";

    const std::string result_wanted = "String";
    const std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__all_lower)
{
    const std::string str = "string a string";

    const std::string result_wanted = "String A String";
    const std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__all_upper)
{
    const std::string str = "STRING A STRING";

    const std::string result_wanted = "String A String";
    const std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__mixed)
{
    const std::string str = "StRiNg a sTrInG";

    const std::string result_wanted = "String A String";
    const std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__special)
{
    const std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

    const std::string result_wanted = "String ~!@#$%^&*()-_+{}|<>?,./";
    const std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__from_the_python_example)
{
    const std::string str = "they're bill's friends from the UK";

    const std::string result_wanted = "They'Re Bill'S Friends From The Uk";
    const std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * swapcase
 */
TEST(string_python, swapcase)
{
    const std::string str = "String";

    const std::string result_wanted = "sTRING";
    const std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__all_lower)
{
    const std::string str = "string string";

    const std::string result_wanted = "STRING STRING";
    const std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__all_upper)
{
    const std::string str = "STRING STRING";

    const std::string result_wanted = "string string";
    const std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__mixed)
{
    const std::string str = "StRiNg sTrInG";

    const std::string result_wanted = "sTrInG StRiNg";
    const std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__special)
{
    const std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

    const std::string result_wanted = "sTRING ~!@#$%^&*()-_+{}|<>?,./";
    const std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * ljust
 */
TEST(string_python, ljust)
{
    const std::string str = "string";

    const std::string result_wanted = "string    ";
    const std::string result = ztd::ljust(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * rjust
 */
TEST(string_python, rjust)
{
    const std::string str = "string";

    const std::string result_wanted = "    string";
    const std::string result = ztd::rjust(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * lstrip
 */
TEST(string_python, lstrip)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "a  ";
    const std::string result = ztd::lstrip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, lstrip__chars)
{
    const std::string str = "z a z";

    const std::string result_wanted = " a z";
    const std::string result = ztd::lstrip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * rstrip
 */
TEST(string_python, rstrip)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "  a";
    const std::string result = ztd::rstrip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, rstrip__chars)
{
    const std::string str = "z a z";

    const std::string result_wanted = "z a ";
    const std::string result = ztd::rstrip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * strip
 */
TEST(string_python, strip)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "a";
    const std::string result = ztd::strip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, strip__chars)
{
    const std::string str = "z a z";

    const std::string result_wanted = " a ";
    const std::string result = ztd::strip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, strip__chars_all)
{
    const std::string str = "\n\r\t ";

    const std::string result_wanted = "";
    const std::string result = ztd::strip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * removeprefix
 */
TEST(string_python, removeprefix)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = "foobar ";

    const std::string result_wanted = "test string";
    const std::string result = ztd::removeprefix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * removesuffix
 */
TEST(string_python, removesuffix)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = " string";

    const std::string result_wanted = "foobar test";
    const std::string result = ztd::removesuffix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * partition
 */
TEST(string_python, partition)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar";
    const std::string result_wanted_2 = "$";
    const std::string result_wanted_3 = "foobar$foobar";

    auto result = ztd::partition(str, "$");
    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, partition__missing)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar$foobar$foobar";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    auto result = ztd::partition(str, "^");

    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, partition__recombine)
{
    const std::string str = "split/split/split";

    const std::string recombine_wanted = str;

    const std::string result_wanted_1 = "split";
    const std::string result_wanted_2 = "/";
    const std::string result_wanted_3 = "split/split";

    auto result = ztd::partition(str, "/");

    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));

    std::string recombine;
    recombine.append(result[0]);
    recombine.append(result[1]);
    recombine.append(result[2]);

    ASSERT_TRUE(ztd::same(recombine_wanted, recombine));
}

TEST(string_python, partition__multi)
{
    const std::string str = "test.tar.tar.test";

    const std::string result_wanted_1 = "test";
    const std::string result_wanted_2 = ".tar.";
    const std::string result_wanted_3 = "tar.test";

    auto result = ztd::partition(str, ".tar.");

    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

/**
 * rpartition
 */
TEST(string_python, rpartition)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar$foobar";
    const std::string result_wanted_2 = "$";
    const std::string result_wanted_3 = "foobar";

    auto result = ztd::rpartition(str, "$");

    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, rpartition__missing)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "foobar$foobar$foobar";

    auto result = ztd::rpartition(str, "^");

    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, rpartition__recombine)
{
    const std::string str = "split/split/split";

    const std::string recombine_wanted = str;

    const std::string result_wanted_1 = "split/split";
    const std::string result_wanted_2 = "/";
    const std::string result_wanted_3 = "split";

    auto result = ztd::rpartition(str, "/");

    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));

    std::string recombine;
    recombine.append(result[0]);
    recombine.append(result[1]);
    recombine.append(result[2]);

    ASSERT_TRUE(ztd::same(recombine_wanted, recombine));
}

TEST(string_python, rpartition__multi)
{
    const std::string str = "test.tar.tar.test";

    const std::string result_wanted_1 = "test.tar";
    const std::string result_wanted_2 = ".tar.";
    const std::string result_wanted_3 = "test";

    auto result = ztd::rpartition(str, ".tar.");

    const std::string& result_1 = result[0];
    const std::string& result_2 = result[1];
    const std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

/**
 * zfill
 */
TEST(string_python, zfill__str)
{
    const std::string str = "string";

    const std::string result_wanted = "0000string";
    const std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_pos)
{
    const std::string str = "+string";

    const std::string result_wanted = "+000string";
    const std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_neg)
{
    const std::string str = "-string";

    const std::string result_wanted = "-000string";
    const std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_int)
{
    const std::string str = "420";

    const std::string result_wanted = "0000000420";
    const std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_int_pos)
{
    const std::string str = "+420";

    const std::string result_wanted = "+000000420";
    const std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_int_neg)
{
    const std::string str = "-420";

    const std::string result_wanted = "-000000420";
    const std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}
