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

#include "../../src/ztd.hxx"

/**
 * split
 */
TEST(string_python, split)
{
    std::string str = "foo foo foo";

    std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    std::vector<std::string> result = ztd::split(str, " ");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__empty_string)
{
    std::string str = "";

    std::vector<std::string> result_wanted = {""};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_first)
{
    std::string str = ",test,test";

    std::vector<std::string> result_wanted = {"", "test", "test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_second)
{
    std::string str = "test,test";

    std::vector<std::string> result_wanted = {"test", "test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_multiple_empty)
{
    std::string str = "test,,,test";

    std::vector<std::string> result_wanted = {"test", "", "", "test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_missing)
{
    std::string str = "test|test";

    std::vector<std::string> result_wanted = {"test|test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars)
{
    std::string str = "a<>b<>c";

    std::vector<std::string> result_wanted = {"a", "b", "c"};
    std::vector<std::string> result = ztd::split(str, "<>");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__no_delimiter)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a,b,c"};
    std::vector<std::string> result = ztd::split(str);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit_0)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a,b,c"};
    std::vector<std::string> result = ztd::split(str, ",", 0);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit_1)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a", "b,c"};
    std::vector<std::string> result = ztd::split(str, ",", 1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit_2)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a", "b", "c"};
    std::vector<std::string> result = ztd::split(str, ",", 2);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, split__maxsplit__larger_than_real_maxsplit)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a", "b", "c"};
    std::vector<std::string> result = ztd::split(str, ",", 500);

    ASSERT_TRUE(result == result_wanted);
}

/**
 * rsplit
 */
TEST(string_python, rsplit)
{
    std::string str = "foo foo foo";

    std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    std::vector<std::string> result = ztd::rsplit(str, " ");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__empty_string)
{
    std::string str = "";

    std::vector<std::string> result_wanted = {""};
    std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_first)
{
    std::string str = ",test,test";

    std::vector<std::string> result_wanted = {"", "test", "test"};
    std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_second)
{
    std::string str = "test,test";

    std::vector<std::string> result_wanted = {"test", "test"};
    std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_empty)
{
    std::string str = "test,,,test";

    std::vector<std::string> result_wanted = {"test", "", "", "test"};
    std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_missing)
{
    std::string str = "test|test";

    std::vector<std::string> result_wanted = {"test|test"};
    std::vector<std::string> result = ztd::rsplit(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars)
{
    std::string str = "a<>b<>c";

    std::vector<std::string> result_wanted = {"a", "b", "c"};
    std::vector<std::string> result = ztd::rsplit(str, "<>");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__no_delimiter)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a,b,c"};
    std::vector<std::string> result = ztd::rsplit(str);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit_0)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a,b,c"};
    std::vector<std::string> result = ztd::rsplit(str, ",", 0);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit_1)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a,b", "c"};
    std::vector<std::string> result = ztd::rsplit(str, ",", 1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit_2)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a", "b", "c"};
    std::vector<std::string> result = ztd::rsplit(str, ",", 2);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, rsplit__maxsplit__larger_than_real_maxsplit)
{
    std::string str = "a,b,c";

    std::vector<std::string> result_wanted = {"a", "b", "c"};
    std::vector<std::string> result = ztd::rsplit(str, ",", 500);

    ASSERT_TRUE(result == result_wanted);
}

/**
 * Join
 */
TEST(string_python, join)
{
    std::vector<std::string> vec = {"foo", "foo", "foo"};

    std::string result_wanted = "foo foo foo";
    std::string result = ztd::join(vec, " ");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, lower)
{
    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";
    std::string lower_wanted = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";

    std::string lower = ztd::lower(upper);

    ASSERT_TRUE(lower.compare(lower_wanted) == 0);
}

TEST(string_python, upper)
{
    std::string lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
    std::string upper_wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";

    std::string upper = ztd::upper(lower);

    ASSERT_TRUE(upper.compare(upper_wanted) == 0);
}

/**
 * replace
 */
TEST(string_python, replace)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar bazbar bazbar";
    std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__missing)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "fooo";
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar foobar";
    std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_neg)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar bazbar bazbar";
    std::string result = ztd::replace(str, str_find, str_replace, -5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_0)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar foobar";
    std::string result = ztd::replace(str, str_find, str_replace, 0);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_1)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar foobar foobar";
    std::string result = ztd::replace(str, str_find, str_replace, 1);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_2)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar bazbar foobar";
    std::string result = ztd::replace(str, str_find, str_replace, 2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, replace__count_3)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar bazbar bazbar";
    std::string result = ztd::replace(str, str_find, str_replace, 3);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * capitalize
 */
TEST(string_python, capitalize)
{
    std::string str = "capitalize only the first letter.";

    std::string result_wanted = "Capitalize only the first letter.";
    std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, capitalize__space)
{
    std::string str = " will not capitalize the first letter.";

    std::string result_wanted = " will not capitalize the first letter.";
    std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * center
 */
TEST(string_python, center__even_string_even_width)
{
    std::string str = "even";

    std::string result_wanted = "   even   ";
    std::string result = ztd::center(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, center__even_string_odd_width)
{
    std::string str = "even";

    std::string result_wanted = "  even   ";
    std::string result = ztd::center(str, 9);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, center__odd_string_odd_width)
{
    std::string str = "odd";

    std::string result_wanted = " odd ";
    std::string result = ztd::center(str, 5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, center__odd_string_even_width)
{
    std::string str = "odd";

    std::string result_wanted = "   odd    ";
    std::string result = ztd::center(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * count
 */
TEST(string_python, count)
{
    std::string str = "zaaazaaaz";

    int result_wanted = 6;
    int result = ztd::count(str, "a");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, count__start_end)
{
    std::string str = "zaaazaaaz";

    int result_wanted = 3;
    int result = ztd::count(str, "a", 4, 15);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string_python, count__start_end_2)
{
    std::string str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    int result_wanted = 3;
    int result = ztd::count(str, "a", 0, 4);

    ASSERT_TRUE(result == result_wanted);
}

/**
 * endswith
 */
TEST(string_python, endswith__true)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "string");

    ASSERT_TRUE(result);
}

TEST(string_python, endswith__false)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "zstring");

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__start_end_true)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "bar", 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, endswith___start_end_false)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "zbar", 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, endswith__long_suffix)
{
    std::string str = "foobar";

    bool result = ztd::endswith(str, "longfoobar");

    ASSERT_FALSE(result);
}

/**
 * startswith
 */
TEST(string_python, startswith__true)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "foo");

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__false)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "zfoo");

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__start_end_true)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "foo", 0, 6);

    ASSERT_TRUE(result);
}

TEST(string_python, startswith__start_end_false)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "zfoo", 0, 6);

    ASSERT_FALSE(result);
}

TEST(string_python, startswith__long_suffix)
{
    std::string str = "foobar";

    bool result = ztd::startswith(str, "foobarlong");

    ASSERT_FALSE(result);
}

/**
 * expandtabs
 */
TEST(string_python, expandtabs__4)
{
    std::string str = "01\t012\t0123\t01234";
    std::string result_wanted = "01  012 0123    01234";

    std::string result = ztd::expandtabs(str, 4);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, expandtabs__8)
{
    std::string str = "01\t012\t0123\t01234";
    std::string result_wanted = "01      012     0123    01234";

    std::string result = ztd::expandtabs(str, 8);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * isalpha
 */
TEST(string_python, isalpha__true)
{
    std::string str = "alphastring";

    ASSERT_TRUE(ztd::isalpha(str));
}

TEST(string_python, isalpha__false)
{
    std::string str = "not alpha string?";

    ASSERT_FALSE(ztd::isalpha(str));
}

/**
 * isdigit
 */
TEST(string_python, isdigit__true)
{
    std::string str = "1234567890";

    ASSERT_TRUE(ztd::isdigit(str));
}

TEST(string_python, isdigit__false)
{
    std::string str = "1234567890a";

    ASSERT_FALSE(ztd::isdigit(str));
}

/**
 * islower
 */
TEST(string_python, islower__true)
{
    std::string str = "string";

    ASSERT_TRUE(ztd::islower(str));
}

TEST(string_python, islower__true_special)
{
    std::string str = "string string!@#$%^&*_+(){}[]";

    ASSERT_TRUE(ztd::islower(str));
}

TEST(string_python, islower__false)
{
    std::string str = "STRING";

    ASSERT_FALSE(ztd::islower(str));
}

/**
 * isupper
 */
TEST(string_python, isupper__true)
{
    std::string str = "STRING";

    ASSERT_TRUE(ztd::isupper(str));
}

TEST(string_python, isupper__true_special)
{
    std::string str = "STRING STRING!@#$%^&*_+(){}[]";

    ASSERT_TRUE(ztd::isupper(str));
}

TEST(string_python, isupper__false)
{
    std::string str = "string";

    ASSERT_FALSE(ztd::isupper(str));
}

/**
 * isspace
 */
TEST(string_python, isspace__true)
{
    std::string str = "    ";

    ASSERT_TRUE(ztd::isspace(str));
}

TEST(string_python, isspace__false)
{
    std::string str = " a ";

    ASSERT_FALSE(ztd::isspace(str));
}

/**
 * istitle
 */
TEST(string_python, istitle__empty)
{
    std::string str = "";

    ASSERT_FALSE(ztd::istitle(str));
}

TEST(string_python, istitle__true)
{
    std::string str = "A String A";

    ASSERT_TRUE(ztd::istitle(str));
}

TEST(string_python, istitle__false)
{
    std::string str = "A string A";

    ASSERT_FALSE(ztd::istitle(str));
}

TEST(string_python, istitle__from_the_python_example)
{
    std::string str = "They'Re Bill'S Friends From The Uk";

    ASSERT_TRUE(ztd::istitle(str));
}

/**
 * title
 */
TEST(string_python, title)
{
    std::string str = "String";

    std::string result_wanted = "String";
    std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__empty)
{
    std::string str = "";

    std::string result_wanted = "";
    std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__all_lower)
{
    std::string str = "string a string";

    std::string result_wanted = "String A String";
    std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__all_upper)
{
    std::string str = "STRING A STRING";

    std::string result_wanted = "String A String";
    std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__mixed)
{
    std::string str = "StRiNg a sTrInG";

    std::string result_wanted = "String A String";
    std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__special)
{
    std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

    std::string result_wanted = "String ~!@#$%^&*()-_+{}|<>?,./";
    std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, title__from_the_python_example)
{
    std::string str = "they're bill's friends from the UK";

    std::string result_wanted = "They'Re Bill'S Friends From The Uk";
    std::string result = ztd::title(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * swapcase
 */
TEST(string_python, swapcase)
{
    std::string str = "String";

    std::string result_wanted = "sTRING";
    std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__empty)
{
    std::string str = "";

    std::string result_wanted = "";
    std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__all_lower)
{
    std::string str = "string string";

    std::string result_wanted = "STRING STRING";
    std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__all_upper)
{
    std::string str = "STRING STRING";

    std::string result_wanted = "string string";
    std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__mixed)
{
    std::string str = "StRiNg sTrInG";

    std::string result_wanted = "sTrInG StRiNg";
    std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, swapcase__special)
{
    std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

    std::string result_wanted = "sTRING ~!@#$%^&*()-_+{}|<>?,./";
    std::string result = ztd::swapcase(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * ljust
 */
TEST(string_python, ljust)
{
    std::string str = "string";

    std::string result_wanted = "string    ";
    std::string result = ztd::ljust(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * rjust
 */
TEST(string_python, rjust)
{
    std::string str = "string";

    std::string result_wanted = "    string";
    std::string result = ztd::rjust(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * lstrip
 */
TEST(string_python, lstrip)
{
    std::string str = "  a  ";

    std::string result_wanted = "a  ";
    std::string result = ztd::lstrip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, lstrip__chars)
{
    std::string str = "z a z";

    std::string result_wanted = " a z";
    std::string result = ztd::lstrip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * rstrip
 */
TEST(string_python, rstrip)
{
    std::string str = "  a  ";

    std::string result_wanted = "  a";
    std::string result = ztd::rstrip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, rstrip__chars)
{
    std::string str = "z a z";

    std::string result_wanted = "z a ";
    std::string result = ztd::rstrip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * strip
 */
TEST(string_python, strip)
{
    std::string str = "  a  ";

    std::string result_wanted = "a";
    std::string result = ztd::strip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, strip__chars)
{
    std::string str = "z a z";

    std::string result_wanted = " a ";
    std::string result = ztd::strip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, strip__chars_all)
{
    std::string str = "\n\r\t ";

    std::string result_wanted = "";
    std::string result = ztd::strip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * removeprefix
 */
TEST(string_python, removeprefix)
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar ";

    std::string result_wanted = "test string";
    std::string result = ztd::removeprefix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * removesuffix
 */
TEST(string_python, removesuffix)
{
    std::string str1 = "foobar test string";
    std::string str2 = " string";

    std::string result_wanted = "foobar test";
    std::string result = ztd::removesuffix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * partition
 */
TEST(string_python, partition)
{
    std::string str = "foobar$foobar$foobar";

    std::string result_wanted_1 = "foobar";
    std::string result_wanted_2 = "$";
    std::string result_wanted_3 = "foobar$foobar";

    auto result = ztd::partition(str, "$");
    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, partition__missing)
{
    std::string str = "foobar$foobar$foobar";

    std::string result_wanted_1 = "foobar$foobar$foobar";
    std::string result_wanted_2 = "";
    std::string result_wanted_3 = "";

    auto result = ztd::partition(str, "^");

    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, partition__recombine)
{
    std::string str = "split/split/split";

    std::string recombine_wanted = str;

    std::string result_wanted_1 = "split";
    std::string result_wanted_2 = "/";
    std::string result_wanted_3 = "split/split";

    auto result = ztd::partition(str, "/");

    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

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
    std::string str = "test.tar.tar.test";

    std::string result_wanted_1 = "test";
    std::string result_wanted_2 = ".tar.";
    std::string result_wanted_3 = "tar.test";

    auto result = ztd::partition(str, ".tar.");

    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

/**
 * rpartition
 */
TEST(string_python, rpartition)
{
    std::string str = "foobar$foobar$foobar";

    std::string result_wanted_1 = "foobar$foobar";
    std::string result_wanted_2 = "$";
    std::string result_wanted_3 = "foobar";

    auto result = ztd::rpartition(str, "$");

    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, rpartition__missing)
{
    std::string str = "foobar$foobar$foobar";

    std::string result_wanted_1 = "";
    std::string result_wanted_2 = "";
    std::string result_wanted_3 = "foobar$foobar$foobar";

    auto result = ztd::rpartition(str, "^");

    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

TEST(string_python, rpartition__recombine)
{
    std::string str = "split/split/split";

    std::string recombine_wanted = str;

    std::string result_wanted_1 = "split/split";
    std::string result_wanted_2 = "/";
    std::string result_wanted_3 = "split";

    auto result = ztd::rpartition(str, "/");

    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

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
    std::string str = "test.tar.tar.test";

    std::string result_wanted_1 = "test.tar";
    std::string result_wanted_2 = ".tar.";
    std::string result_wanted_3 = "test";

    auto result = ztd::rpartition(str, ".tar.");

    std::string& result_1 = result[0];
    std::string& result_2 = result[1];
    std::string& result_3 = result[2];

    ASSERT_TRUE(ztd::same(result_1, result_wanted_1));
    ASSERT_TRUE(ztd::same(result_2, result_wanted_2));
    ASSERT_TRUE(ztd::same(result_3, result_wanted_3));
}

/**
 * zfill
 */
TEST(string_python, zfill__str)
{
    std::string str = "string";

    std::string result_wanted = "0000string";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_pos)
{
    std::string str = "+string";

    std::string result_wanted = "+000string";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_neg)
{
    std::string str = "-string";

    std::string result_wanted = "-000string";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_int)
{
    std::string str = "420";

    std::string result_wanted = "0000000420";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_int_pos)
{
    std::string str = "+420";

    std::string result_wanted = "+000000420";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, zfill__str_int_neg)
{
    std::string str = "-420";

    std::string result_wanted = "-000000420";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * function alias
 */
TEST(string_python, remove_prefix)
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar ";

    std::string result_wanted = "test string";
    std::string result = ztd::remove_prefix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_python, remove_suffix)
{
    std::string str1 = "foobar test string";
    std::string str2 = " string";

    std::string result_wanted = "foobar test";
    std::string result = ztd::remove_suffix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}
