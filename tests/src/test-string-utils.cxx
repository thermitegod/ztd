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
 * contains(string, string)
 */
TEST(string_utils, contains__string_string__true)
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_string__false)
{
    std::string str3 = "foobarbaz";
    std::string str4 = "buz";

    ASSERT_FALSE(ztd::contains(str3, str4));
}

TEST(string_utils, contains__string_string__start_end__true)
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__string_string__start_end__false)
{
    std::string str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(string, char*)
 */
TEST(string_utils, contains__string_char__true)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_char__false)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bur";

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_char__nullptr)
{
    std::string str1 = "foobarbaz";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_char__start_end__true)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__string_char__start_end__false)
{
    std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(char*, string)
 */
TEST(string_utils, contains__char_string__true)
{
    const char* str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_string__false)
{
    const char* str3 = "foobarbaz";
    std::string str4 = "bur";

    ASSERT_FALSE(ztd::contains(str3, str4));
}

TEST(string_utils, contains__char_string__nullptr)
{
    const char* str5 = nullptr;
    std::string str6 = "bar";

    ASSERT_FALSE(ztd::contains(str5, str6));
}

TEST(string_utils, contains__char_string__start_end__true)
{
    const char* str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__char_string__start_end__false)
{
    const char* str1 = "foobarbaz";
    std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(char*, char*)
 */
TEST(string_utils, contains__char_char__true)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_char__false)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bur";

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_char__nullptr_second)
{
    const char* str1 = "foobarbaz";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_char__nullptr_first)
{
    const char* str1 = nullptr;
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_char__nullptr_dual)
{
    const char* str1 = nullptr;
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_char__start_end__true)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__char_char__start_end__false)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

/**
 * contains(string, char)
 */
TEST(string_utils, contains__string_singlechar__true)
{
    std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_singlechar__false)
{
    std::string str1 = "abcd";
    const char str4 = 'z';

    ASSERT_FALSE(ztd::contains(str1, str4));
}

TEST(string_utils, contains__string_singlechar__start_end__true)
{
    std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 3));
}

TEST(string_utils, contains__string_singlechar__start_end__false)
{
    std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 1));
}

/**
 * contains(char*, char)
 */
TEST(string_utils, contains___char_singlechar__true)
{
    const char* str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains___char_singlechar__false)
{
    const char* str1 = "abcd";
    const char str2 = 'z';

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains___char_singlechar__nullptr)
{
    const char* str1 = nullptr;
    const char str2 = 'z';

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains___char_singlechar__start_end__true)
{
    const char* str1 = "test string";
    const char str2 = 't';

    ASSERT_TRUE(ztd::contains(str1, str2, 0, 2));
}

TEST(string_utils, contains___char_singlechar__start_end__false)
{
    const char* str1 = "test string";
    const char str2 = 's';

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 2));
}

/**
 * contains_any array
 */
TEST(string_utils, contains_any__array)
{
    std::string str1 = "foobar";
    std::array<std::string, 2> a1{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str1, a1));

    std::string str2 = "bazbar";
    std::array<std::string, 2> a2{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str2, a2));

    std::string str3 = "foobar";
    std::array<std::string, 2> a3{"fuz", "baz"};

    ASSERT_FALSE(ztd::contains_any(str3, a3));
}

/**
 * contains_any vector
 */
TEST(string_utils, contains_any__vector)
{
    std::string str1 = "foobar";
    std::vector<std::string> v1{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str1, v1));

    std::string str2 = "bazbar";
    std::vector<std::string> v2{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str2, v2));

    std::string str3 = "foobar";
    std::vector<std::string> v3{"fuz", "baz"};

    ASSERT_FALSE(ztd::contains_any(str3, v3));
}

/**
 * same(string, string)
 */
TEST(string_utils, same__string_string)
{
    std::string str1 = "same string";
    std::string str2 = "same string";
    std::string str3 = str2;

    ASSERT_TRUE(ztd::same(str1, str2));

    ASSERT_TRUE(ztd::same(str1, str3));

    std::string str4 = "same string";
    std::string str5 = "not same string";

    ASSERT_FALSE(ztd::same(str4, str5));
}

/**
 * same(string, char*)
 */
TEST(string_utils, same__string_char)
{
    std::string str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::same(str1, str2));

    std::string str3 = "same string";
    const char* str4 = "same string";

    ASSERT_TRUE(ztd::same(str3, str4));
}

/**
 * same(char*, string)
 */
TEST(string_utils, same__char_string)
{
    const char* str1 = nullptr;
    std::string str2 = "not same";

    ASSERT_FALSE(ztd::same(str1, str2));

    const char* str3 = "same string";
    std::string str4 = "same string";

    ASSERT_TRUE(ztd::same(str3, str4));
}

/**
 * same(char*, char*)
 */
TEST(string_utils, same__char_char)
{
    const char* str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::same(str1, str2));

    const char* str3 = nullptr;
    const char* str4 = "not same";

    ASSERT_FALSE(ztd::same(str3, str4));

    const char* str5 = "same string";
    const char* str6 = "same string";

    ASSERT_TRUE(ztd::same(str5, str6));

    const char* str7 = nullptr;
    const char* str8 = nullptr;

    ASSERT_FALSE(ztd::same(str7, str8));
}

/**
 * isame(string, string)
 */
TEST(string_utils, isame__string_string)
{
    std::string str1 = "SAME string";
    std::string str2 = "same STRING";
    std::string str3 = str2;

    ASSERT_TRUE(ztd::isame(str1, str2));

    ASSERT_TRUE(ztd::isame(str1, str3));

    std::string str4 = "SAME string";
    std::string str5 = "not same STRING";

    ASSERT_FALSE(ztd::isame(str4, str5));
}

/**
 * same(string, char*)
 */
TEST(string_utils, isame__string_char)
{
    std::string str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::isame(str1, str2));

    std::string str3 = "SAME string";
    const char* str4 = "same STRING";

    ASSERT_TRUE(ztd::isame(str3, str4));
}

/**
 * same(char*, string)
 */
TEST(string_utils, isame__char_string)
{
    const char* str1 = nullptr;
    std::string str2 = "not same";

    ASSERT_FALSE(ztd::isame(str1, str2));

    const char* str3 = "SAME string";
    std::string str4 = "same STRING";

    ASSERT_TRUE(ztd::isame(str3, str4));
}

/**
 * same(char*, char*)
 */
TEST(string_utils, isame__char_char)
{
    const char* str1 = "not SAME";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::isame(str1, str2));

    const char* str3 = nullptr;
    const char* str4 = "not same";

    ASSERT_FALSE(ztd::isame(str3, str4));

    const char* str5 = "SAME string";
    const char* str6 = "same STRING";

    ASSERT_TRUE(ztd::isame(str5, str6));

    const char* str7 = nullptr;
    const char* str8 = nullptr;

    ASSERT_FALSE(ztd::isame(str7, str8));
}

/**
 * remove_before
 */
TEST(string_utils, remove_before)
{
    std::string str1 = "Just a test string in a test case";
    std::string str2 = "test ";

    std::string result_wanted = "case";
    std::string result = ztd::remove_before(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, remove_before_2)
{
    std::string str1 = "foobar$foobar$foobar";
    std::string str2 = "$";

    std::string result_wanted = "foobar";
    std::string result = ztd::remove_before(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * remove_after
 */
TEST(string_utils, remove_after)
{
    std::string str1 = "Just a test string in a test case";
    std::string str2 = " test";

    std::string result_wanted = "Just a";
    std::string result = ztd::remove_after(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, remove_after_2)
{
    std::string str1 = "foobar$foobar$foobar";
    std::string str2 = "$";

    std::string result_wanted = "foobar";
    std::string result = ztd::remove_after(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * replace_multiple array
 */
TEST(string_utils, replace_multiple__array)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> arr_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, arr_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__missing)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> arr_find = {"fooo", "baar"};
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar foobar";
    std::string result = ztd::replace_multiple(str, arr_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_neg)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> arr_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, arr_find, str_replace, -5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_0)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> arr_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar foobar";
    std::string result = ztd::replace_multiple(str, arr_find, str_replace, 0);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_1)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> arr_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz foobar foobar";
    std::string result = ztd::replace_multiple(str, arr_find, str_replace, 1);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_2)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> arr_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz foobar";
    std::string result = ztd::replace_multiple(str, arr_find, str_replace, 2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_3)
{
    std::string str = "foobar foobar foobar";
    std::array<std::string, 2> arr_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, arr_find, str_replace, 3);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * replace_multiple vector
 */
TEST(string_utils, replace_multiple__vector)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__missing)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"fooo", "baar"};
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar foobar";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_neg)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace, -5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_0)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "foobar foobar foobar";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace, 0);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_1)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz foobar foobar";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace, 1);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_2)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz foobar";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace, 2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_3)
{
    std::string str = "foobar foobar foobar";
    std::vector<std::string> vec_find = {"foo", "bar"};
    std::string str_replace = "baz";

    std::string result_wanted = "bazbaz bazbaz bazbaz";
    std::string result = ztd::replace_multiple(str, vec_find, str_replace, 3);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}
