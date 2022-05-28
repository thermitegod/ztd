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

TEST(string, split)
{
    std::string str = "foo foo foo";

    std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    std::vector<std::string> result = ztd::split(str, " ");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__empty_string)
{
    std::string str = "";

    std::vector<std::string> result_wanted = {""};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__delimiter_first)
{
    std::string str = ",test,test";

    std::vector<std::string> result_wanted = {"", "test", "test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__delimiter_second)
{
    std::string str = "test,test";

    std::vector<std::string> result_wanted = {"test", "test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__delimiter_multiple_empty)
{
    std::string str = "test,,,test";

    std::vector<std::string> result_wanted = {"test", "", "", "test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__delimiter_missing)
{
    std::string str = "test|test";

    std::vector<std::string> result_wanted = {"test|test"};
    std::vector<std::string> result = ztd::split(str, ",");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__delimiter_multiple_chars)
{
    std::string str = "a<>b<>c";

    std::vector<std::string> result_wanted = {"a", "b", "c"};
    std::vector<std::string> result = ztd::split(str, "<>");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__no_delimiter)
{
    std::string str = "a,a,a";

    std::vector<std::string> result_wanted = {"a,a,a"};
    std::vector<std::string> result = ztd::split(str);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__maxsplit_0)
{
    std::string str = "a,a,a";

    std::vector<std::string> result_wanted = {"a,a,a"};
    std::vector<std::string> result = ztd::split(str, ",", 0);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__maxsplit_1)
{
    std::string str = "a,a,a";

    std::vector<std::string> result_wanted = {"a", "a,a"};
    std::vector<std::string> result = ztd::split(str, ",", 1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, split__maxsplit_2)
{
    std::string str = "a,a,a";

    std::vector<std::string> result_wanted = {"a", "a", "a"};
    std::vector<std::string> result = ztd::split(str, ",", 2);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, join)
{
    std::vector<std::string> vec = {"foo", "foo", "foo"};

    std::string result_wanted = "foo foo foo";
    std::string result = ztd::join(vec, " ");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, lower)
{
    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";
    std::string lower_wanted = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";

    std::string lower = ztd::lower(upper);

    ASSERT_TRUE(lower.compare(lower_wanted) == 0);
}

TEST(string, upper)
{
    std::string lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
    std::string upper_wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";

    std::string upper = ztd::upper(lower);

    ASSERT_TRUE(upper.compare(upper_wanted) == 0);
}

/**
 * contains(string, string)
 */
TEST(string, contains__string_string__true)
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string, contains__string_string__false)
{
    std::string str3 = "foobarbaz";
    std::string str4 = "buz";

    ASSERT_FALSE(ztd::contains(str3, str4));
}

TEST(string, contains__string_string__start_end__true)
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string, contains__string_string__start_end__false)
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(string, char*)
 */
TEST(string, contains__string_char__true)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string, contains__string_char__false)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bur";

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains__string_char__nullptr)
{
    std::string str1 = "foobarbaz";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains__string_char__start_end__true)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string, contains__string_char__start_end__false)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(char*, string)
 */
TEST(string, contains__char_string__true)
{
    const char* str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string, contains__char_string__false)
{
    const char* str3 = "foobarbaz";
    std::string str4 = "bur";

    ASSERT_FALSE(ztd::contains(str3, str4));
}

TEST(string, contains__char_string__nullptr)
{
    const char* str5 = nullptr;
    std::string str6 = "bar";

    ASSERT_FALSE(ztd::contains(str5, str6));
}

TEST(string, contains__char_string__start_end__true)
{
    const char* str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string, contains__char_string__start_end__false)
{
    const char* str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(char*, char*)
 */
TEST(string, contains__char_char__true)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string, contains__char_char__false)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bur";

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains__char_char__nullptr_second)
{
    const char* str1 = "foobarbaz";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains__char_char__nullptr_first)
{
    const char* str1 = nullptr;
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains__char_char__nullptr_dual)
{
    const char* str1 = nullptr;
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains__char_char__start_end__true)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string, contains__char_char__start_end__false)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(string, char)
 */
TEST(string, contains__string_singlechar__true)
{
    std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string, contains__string_singlechar__false)
{
    std::string str1 = "abcd";
    const char str4 = 'z';

    ASSERT_FALSE(ztd::contains(str1, str4));
}

TEST(string, contains__string_singlechar__start_end__true)
{
    std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 3));
}

TEST(string, contains__string_singlechar__start_end__false)
{
    std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 1));
}

/**
 * contains(char*, char)
 */
TEST(string, contains___char_singlechar__true)
{
    const char* str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string, contains___char_singlechar__false)
{
    const char* str1 = "abcd";
    const char str2 = 'z';

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains___char_singlechar__nullptr)
{
    const char* str1 = nullptr;
    const char str2 = 'z';

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string, contains___char_singlechar__start_end__true)
{
    const char* str1 = "test string";
    const char str2 = 't';

    ASSERT_TRUE(ztd::contains(str1, str2, 0, 2));
}

TEST(string, contains___char_singlechar__start_end__false)
{
    const char* str1 = "test string";
    const char str2 = 's';

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 2));
}

////////////////////////////////////////////////////////////////////////////////

TEST(string, contains_any__array)
{
    std::string str1 = "foobar";
    std::array<std::string, 2> a1{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str1, a1));

    std::string str2 = "bazbar";
    std::array<std::string, 2> a2{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str2, a2));

    std::string str3 = "foobar";
    std::array<std::string, 2> a3{"fuz", "baz"};

    ASSERT_TRUE(!ztd::contains_any(str3, a3));
}

TEST(string, contains_any__vector)
{
    std::string str1 = "foobar";
    std::vector<std::string> v1{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str1, v1));

    std::string str2 = "bazbar";
    std::vector<std::string> v2{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str2, v2));

    std::string str3 = "foobar";
    std::vector<std::string> v3{"fuz", "baz"};

    ASSERT_TRUE(!ztd::contains_any(str3, v3));
}

TEST(string, same__string_string)
{
    std::string str1 = "same string";
    std::string str2 = "same string";
    std::string str3 = str2;

    ASSERT_TRUE(ztd::same(str1, str2));

    ASSERT_TRUE(ztd::same(str1, str3));

    std::string str4 = "same string";
    std::string str5 = "not same string";

    ASSERT_TRUE(!ztd::same(str4, str5));
}

TEST(string, same__string_char)
{
    std::string str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_TRUE(!ztd::same(str1, str2));

    std::string str3 = "same string";
    const char* str4 = "same string";

    ASSERT_TRUE(ztd::same(str3, str4));
}

TEST(string, same__char_string)
{
    const char* str1 = nullptr;
    std::string str2 = "not same";

    ASSERT_TRUE(!ztd::same(str1, str2));

    const char* str3 = "same string";
    std::string str4 = "same string";

    ASSERT_TRUE(ztd::same(str3, str4));
}

TEST(string, same__char_char)
{
    const char* str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_TRUE(!ztd::same(str1, str2));

    const char* str3 = nullptr;
    const char* str4 = "not same";

    ASSERT_TRUE(!ztd::same(str3, str4));

    const char* str5 = "same string";
    const char* str6 = "same string";

    ASSERT_TRUE(ztd::same(str5, str6));

    const char* str7 = nullptr;
    const char* str8 = nullptr;

    ASSERT_TRUE(!ztd::same(str7, str8));
}

TEST(string, isame__string_string)
{
    std::string str1 = "SAME string";
    std::string str2 = "same STRING";
    std::string str3 = str2;

    ASSERT_TRUE(ztd::isame(str1, str2));

    ASSERT_TRUE(ztd::isame(str1, str3));

    std::string str4 = "SAME string";
    std::string str5 = "not same STRING";

    ASSERT_TRUE(!ztd::isame(str4, str5));
}

TEST(string, isame__string_char)
{
    std::string str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_TRUE(!ztd::isame(str1, str2));

    std::string str3 = "SAME string";
    const char* str4 = "same STRING";

    ASSERT_TRUE(ztd::isame(str3, str4));
}

TEST(string, isame__char_string)
{
    const char* str1 = nullptr;
    std::string str2 = "not same";

    ASSERT_TRUE(!ztd::isame(str1, str2));

    const char* str3 = "SAME string";
    std::string str4 = "same STRING";

    ASSERT_TRUE(ztd::isame(str3, str4));
}

TEST(string, isame__char_char)
{
    const char* str1 = "not SAME";
    const char* str2 = nullptr;

    ASSERT_TRUE(!ztd::isame(str1, str2));

    const char* str3 = nullptr;
    const char* str4 = "not same";

    ASSERT_TRUE(!ztd::isame(str3, str4));

    const char* str5 = "SAME string";
    const char* str6 = "same STRING";

    ASSERT_TRUE(ztd::isame(str5, str6));

    const char* str7 = nullptr;
    const char* str8 = nullptr;

    ASSERT_TRUE(!ztd::isame(str7, str8));
}

TEST(string, remove_prefix)
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar ";

    std::string result_wanted = "test string";
    std::string result = ztd::remove_prefix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, remove_suffix)
{
    std::string str1 = "foobar test string";
    std::string str2 = " string";

    std::string result_wanted = "foobar test";
    std::string result = ztd::remove_suffix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, remove_before)
{
    std::string str1 = "Just a test string in a test case";
    std::string str2 = "test ";

    std::string result_wanted = "case";
    std::string result = ztd::remove_before(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, remove_before_2)
{
    std::string str1 = "foobar$foobar$foobar";
    std::string str2 = "$";

    std::string result_wanted = "foobar";
    std::string result = ztd::remove_before(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, remove_after)
{
    std::string str1 = "Just a test string in a test case";
    std::string str2 = " test";

    std::string result_wanted = "Just a";
    std::string result = ztd::remove_after(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, remove_after_2)
{
    std::string str1 = "foobar$foobar$foobar";
    std::string str2 = "$";

    std::string result_wanted = "foobar";
    std::string result = ztd::remove_after(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, replace)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar bazbar bazbar";
    std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, replace_first)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "bazbar foobar foobar";
    std::string result = ztd::replace_first(str, str_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, replace_last)
{
    std::string str = "foobar foobar foobar";
    std::string str_find = "foo";
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar bazbar";
    std::string result = ztd::replace_last(str, str_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, replace_multiple__array)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, replace_multiple__vector)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, replace_multiple__vector_pair)
{
    std::string str = "foobar %f%b %f%b";
    std::vector<std::pair<std::string, std::string>> find_replace = {{"%f", "foo"}, {"%b", "bar"}};

    std::string result_wanted = "foobar foobar foobar";
    std::string result = ztd::replace_multiple(str, find_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * Python string methods
 */

TEST(string, capitalize)
{
    std::string str = "capitalize only the first letter.";

    std::string result_wanted = "Capitalize only the first letter.";
    std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, capitalize__space)
{
    std::string str = " will not capitalize the first letter.";

    std::string result_wanted = " will not capitalize the first letter.";
    std::string result = ztd::capitalize(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, center__even_string_even_width)
{
    std::string str = "even";

    std::string result_wanted = "   even   ";
    std::string result = ztd::center(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, center__even_string_odd_width)
{
    std::string str = "even";

    std::string result_wanted = "  even   ";
    std::string result = ztd::center(str, 9);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, center__odd_string_odd_width)
{
    std::string str = "odd";

    std::string result_wanted = " odd ";
    std::string result = ztd::center(str, 5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, center__odd_string_even_width)
{
    std::string str = "odd";

    std::string result_wanted = "   odd    ";
    std::string result = ztd::center(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, count)
{
    std::string str = "zaaazaaaz";

    int result_wanted = 6;
    int result = ztd::count(str, "a");

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, count__start_end)
{
    std::string str = "zaaazaaaz";

    int result_wanted = 3;
    int result = ztd::count(str, "a", 4, 15);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, count__start_end_2)
{
    std::string str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    int result_wanted = 3;
    int result = ztd::count(str, "a", 0, 4);

    ASSERT_TRUE(result == result_wanted);
}

TEST(string, endswith__true)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "string");

    ASSERT_TRUE(result);
}

TEST(string, endswith__false)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "zstring");

    ASSERT_TRUE(!result);
}

TEST(string, endswith__start_end_true)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "bar", 0, 6);

    ASSERT_TRUE(result);
}

TEST(string, endswith___start_end_false)
{
    std::string str = "foobarstring";

    bool result = ztd::endswith(str, "zbar", 0, 6);

    ASSERT_TRUE(!result);
}

TEST(string, endswith__long_suffix)
{
    std::string str = "foobar";

    bool result = ztd::endswith(str, "longfoobar");

    ASSERT_TRUE(!result);
}

TEST(string, startswith__true)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "foo");

    ASSERT_TRUE(result);
}

TEST(string, startswith__false)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "zfoo");

    ASSERT_TRUE(!result);
}

TEST(string, startswith__start_end_true)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "foo", 0, 6);

    ASSERT_TRUE(result);
}

TEST(string, startswith__start_end_false)
{
    std::string str = "foobarstring";

    bool result = ztd::startswith(str, "zfoo", 0, 6);

    ASSERT_TRUE(!result);
}

TEST(string, startswith__long_suffix)
{
    std::string str = "foobar";

    bool result = ztd::startswith(str, "foobarlong");

    ASSERT_TRUE(!result);
}

TEST(string, expandtabs__4)
{
    std::string str = "01\t012\t0123\t01234";
    std::string result_wanted = "01  012 0123    01234";

    std::string result = ztd::expandtabs(str, 4);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, expandtabs__8)
{
    std::string str = "01\t012\t0123\t01234";
    std::string result_wanted = "01      012     0123    01234";

    std::string result = ztd::expandtabs(str, 8);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, isalpha__true)
{
    std::string str = "alphastring";

    ASSERT_TRUE(ztd::isalpha(str));
}

TEST(string, isalpha__false)
{
    std::string str = "not alpha string?";

    ASSERT_TRUE(!ztd::isalpha(str));
}

TEST(string, isdigit__true)
{
    std::string str = "1234567890";

    ASSERT_TRUE(ztd::isdigit(str));
}

TEST(string, isdigit__false)
{
    std::string str = "1234567890a";

    ASSERT_TRUE(!ztd::isdigit(str));
}

TEST(string, islower__true)
{
    std::string str = "string";

    ASSERT_TRUE(ztd::islower(str));
}

TEST(string, islower__true_special)
{
    std::string str = "string string!@#$%^&*_+(){}[]";

    ASSERT_TRUE(ztd::islower(str));
}

TEST(string, islower__false)
{
    std::string str = "STRING";

    ASSERT_TRUE(!ztd::islower(str));
}

TEST(string, isupper__true)
{
    std::string str = "STRING";

    ASSERT_TRUE(ztd::isupper(str));
}

TEST(string, isupper__true_special)
{
    std::string str = "STRING STRING!@#$%^&*_+(){}[]";

    ASSERT_TRUE(ztd::isupper(str));
}

TEST(string, isupper__false)
{
    std::string str = "string";

    ASSERT_TRUE(!ztd::isupper(str));
}

TEST(string, isspace__true)
{
    std::string str = "    ";

    ASSERT_TRUE(ztd::isspace(str));
}

TEST(string, isspace__false)
{
    std::string str = " a ";

    ASSERT_TRUE(!ztd::isspace(str));
}

TEST(string, ljust)
{
    std::string str = "string";

    std::string result_wanted = "string    ";
    std::string result = ztd::ljust(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, rjust)
{
    std::string str = "string";

    std::string result_wanted = "    string";
    std::string result = ztd::rjust(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, lstrip)
{
    std::string str = "  a  ";

    std::string result_wanted = "a  ";
    std::string result = ztd::lstrip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, lstrip__chars)
{
    std::string str = "z a z";

    std::string result_wanted = " a z";
    std::string result = ztd::lstrip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, rstrip)
{
    std::string str = "  a  ";

    std::string result_wanted = "  a";
    std::string result = ztd::rstrip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, rstrip__chars)
{
    std::string str = "z a z";

    std::string result_wanted = "z a ";
    std::string result = ztd::rstrip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, strip)
{
    std::string str = "  a  ";

    std::string result_wanted = "a";
    std::string result = ztd::strip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, strip__chars)
{
    std::string str = "z a z";

    std::string result_wanted = " a ";
    std::string result = ztd::strip(str, "z");

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, strip__chars_all)
{
    std::string str = "\n\r\t ";

    std::string result_wanted = "";
    std::string result = ztd::strip(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, removeprefix)
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar ";

    std::string result_wanted = "test string";
    std::string result = ztd::removeprefix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, removesuffix)
{
    std::string str1 = "foobar test string";
    std::string str2 = " string";

    std::string result_wanted = "foobar test";
    std::string result = ztd::removesuffix(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, partition)
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

TEST(string, partition__missing)
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

TEST(string, partition__recombine)
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

TEST(string, partition__multi)
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

TEST(string, rpartition)
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

TEST(string, rpartition__missing)
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

TEST(string, rpartition__recombine)
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

TEST(string, rpartition__multi)
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

TEST(string, zfill__str)
{
    std::string str = "string";

    std::string result_wanted = "0000string";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, zfill__str_pos)
{
    std::string str = "+string";

    std::string result_wanted = "+000string";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, zfill__str_neg)
{
    std::string str = "-string";

    std::string result_wanted = "-000string";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, zfill__str_int)
{
    std::string str = "420";

    std::string result_wanted = "0000000420";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, zfill__str_int_pos)
{
    std::string str = "+420";

    std::string result_wanted = "+000000420";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string, zfill__str_int_neg)
{
    std::string str = "-420";

    std::string result_wanted = "-000000420";
    std::string result = ztd::zfill(str, 10);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}
