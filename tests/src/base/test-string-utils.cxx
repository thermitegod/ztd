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

// I know they are deprecated, I am the one who did it.
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include <vector>

#include "../../src/ztd.hxx"

/**
 * contains(string, string)
 */
TEST(string_utils, contains__string_string__true)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_string__false)
{
    const std::string str3 = "foobarbaz";
    const std::string str4 = "buz";

    ASSERT_FALSE(ztd::contains(str3, str4));
}

TEST(string_utils, contains__string_string__start_end__true)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__string_string__start_end__false)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

TEST(string_utils, contains__string_string__start_end__same)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__string_string__start_end__large_start)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 3, 2));
}

/**
 * contains(string, char*)
 */
TEST(string_utils, contains__string_char__true)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_char__false)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bur";

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_char__nullptr)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_char__start_end__true)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__string_char__start_end__false)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

TEST(string_utils, contains__string_char__start_end__same)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__string_char__start_end__large_start)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 3, 2));
}

/**
 * contains(char*, string)
 */
TEST(string_utils, contains__char_string__true)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_string__false)
{
    const char* str3 = "foobarbaz";
    const std::string str4 = "bur";

    ASSERT_FALSE(ztd::contains(str3, str4));
}

TEST(string_utils, contains__char_string__nullptr)
{
    const char* str5 = nullptr;
    const std::string str6 = "bar";

    ASSERT_FALSE(ztd::contains(str5, str6));
}

TEST(string_utils, contains__char_string__start_end__true)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__char_string__start_end__false)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 4));
}

TEST(string_utils, contains__char_string__start_end__same)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__char_string__start_end__large_start)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 3, 2));
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

TEST(string_utils, contains__char_char__start_end__same)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__char_char__start_end__large_start)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    ASSERT_FALSE(ztd::contains(str1, str2, 3, 2));
}

#ifndef ZTD_DISABLE_DEPRECATED
/**
 * contains(string, char)
 */
TEST(string_utils, contains__string_singlechar__true)
{
    const std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_singlechar__false)
{
    const std::string str1 = "abcd";
    const char str4 = 'z';

    ASSERT_FALSE(ztd::contains(str1, str4));
}

TEST(string_utils, contains__string_singlechar__start_end__true)
{
    const std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_TRUE(ztd::contains(str1, str2, 2, 3));
}

TEST(string_utils, contains__string_singlechar__start_end__false)
{
    const std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_FALSE(ztd::contains(str1, str2, 0, 1));
}

TEST(string_utils, contains__string_singlechar__start_end__same)
{
    const std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__string_singlechar__start_end__large_start)
{
    const std::string str1 = "abcd";
    const char str2 = 'c';

    ASSERT_FALSE(ztd::contains(str1, str2, 3, 2));
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

TEST(string_utils, contains__char_singlechar__start_end__same)
{
    const char* str1 = "test string";
    const char str2 = 's';

    ASSERT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__char_singlechar__start_end__large_start)
{
    const char* str1 = "test string";
    const char str2 = 's';

    ASSERT_FALSE(ztd::contains(str1, str2, 3, 2));
}
#endif

/**
 * contains_any array<string_view>
 */
TEST(string_utils, contains_any__array__string_view__1)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "foobar"sv;
    constexpr std::array<std::string_view, 2> a1{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str1, a1));

    std::string_view str2 = "bazbar"sv;
    constexpr std::array<std::string_view, 2> a2{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str2, a2));

    std::string_view str3 = "foobar"sv;
    constexpr std::array<std::string_view, 2> a3{"fuz"sv, "baz"sv};

    ASSERT_FALSE(ztd::contains_any(str3, a3));
}

TEST(string_utils, contains_any__array__string_view__2)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "foobar";
    constexpr std::array<std::string_view, 2> a1{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str1, a1));

    const std::string str2 = "bazbar";
    constexpr std::array<std::string_view, 2> a2{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str2, a2));

    const std::string str3 = "foobar";
    constexpr std::array<std::string_view, 2> a3{"fuz"sv, "baz"sv};

    ASSERT_FALSE(ztd::contains_any(str3, a3));
}

/**
 * contains_any array<string>
 */
TEST(string_utils, contains_any__array__string)
{
    const std::string str1 = "foobar";
    const std::array<std::string, 2> a1{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str1, a1));

    const std::string str2 = "bazbar";
    const std::array<std::string, 2> a2{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str2, a2));

    const std::string str3 = "foobar";
    const std::array<std::string, 2> a3{"fuz", "baz"};

    ASSERT_FALSE(ztd::contains_any(str3, a3));
}

/**
 * contains_any vector<string_view>
 */
TEST(string_utils, contains_any__vector__string_view__1)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "foobar";
    const std::vector<std::string_view> v1{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str1, v1));

    std::string_view str2 = "bazbar";
    const std::vector<std::string_view> v2{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str2, v2));

    std::string_view str3 = "foobar";
    const std::vector<std::string_view> v3{"fuz"sv, "baz"sv};

    ASSERT_FALSE(ztd::contains_any(str3, v3));
}

TEST(string_utils, contains_any__vector__string_view__2)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "foobar";
    const std::vector<std::string_view> v1{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str1, v1));

    const std::string str2 = "bazbar";
    const std::vector<std::string_view> v2{"foo"sv, "bar"sv};

    ASSERT_TRUE(ztd::contains_any(str2, v2));

    const std::string str3 = "foobar";
    const std::vector<std::string_view> v3{"fuz"sv, "baz"sv};

    ASSERT_FALSE(ztd::contains_any(str3, v3));
}

/**
 * contains_any vector<string>
 */
TEST(string_utils, contains_any__vector__string)
{
    const std::string str1 = "foobar";
    const std::vector<std::string> v1{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str1, v1));

    const std::string str2 = "bazbar";
    const std::vector<std::string> v2{"foo", "bar"};

    ASSERT_TRUE(ztd::contains_any(str2, v2));

    const std::string str3 = "foobar";
    const std::vector<std::string> v3{"fuz", "baz"};

    ASSERT_FALSE(ztd::contains_any(str3, v3));
}

/**
 * same(string, string)
 */
TEST(string_utils, same__string_string)
{
    const std::string str1 = "same string";
    const std::string str2 = "same string";
    const std::string str3 = str2;

    ASSERT_TRUE(ztd::same(str1, str2));

    ASSERT_TRUE(ztd::same(str1, str3));

    const std::string str4 = "same string";
    const std::string str5 = "not same string";

    ASSERT_FALSE(ztd::same(str4, str5));
}

/**
 * same(string, char*)
 */
TEST(string_utils, same__string_char)
{
    const std::string str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::same(str1, str2));

    const std::string str3 = "same string";
    const char* str4 = "same string";

    ASSERT_TRUE(ztd::same(str3, str4));
}

/**
 * same(char*, string)
 */
TEST(string_utils, same__char_string)
{
    const char* str1 = nullptr;
    const std::string str2 = "not same";

    ASSERT_FALSE(ztd::same(str1, str2));

    const char* str3 = "same string";
    const std::string str4 = "same string";

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
 * replace_multiple array
 */
TEST(string_utils, replace_multiple__array)
{
    const std::string str = "foobar foobar foobar";
    const std::array<std::string, 2> arr_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz bazbaz";
    const std::string result = ztd::replace_multiple(str, arr_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__missing)
{
    const std::string str = "foobar foobar foobar";
    const std::array<std::string, 2> arr_find = {"fooo", "baar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace_multiple(str, arr_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_neg)
{
    const std::string str = "foobar foobar foobar";
    const std::array<std::string, 2> arr_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz bazbaz";
    const std::string result = ztd::replace_multiple(str, arr_find, str_replace, -5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_0)
{
    const std::string str = "foobar foobar foobar";
    const std::array<std::string, 2> arr_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace_multiple(str, arr_find, str_replace, 0);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_1)
{
    const std::string str = "foobar foobar foobar";
    const std::array<std::string, 2> arr_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz foobar foobar";
    const std::string result = ztd::replace_multiple(str, arr_find, str_replace, 1);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_2)
{
    const std::string str = "foobar foobar foobar";
    const std::array<std::string, 2> arr_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz foobar";
    const std::string result = ztd::replace_multiple(str, arr_find, str_replace, 2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__array__count_3)
{
    const std::string str = "foobar foobar foobar";
    const std::array<std::string, 2> arr_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz bazbaz";
    const std::string result = ztd::replace_multiple(str, arr_find, str_replace, 3);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * replace_multiple vector
 */
TEST(string_utils, replace_multiple__vector)
{
    const std::string str = "foobar foobar foobar";
    const std::vector<std::string> vec_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz bazbaz";
    const std::string result = ztd::replace_multiple(str, vec_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__missing)
{
    const std::string str = "foobar foobar foobar";
    const std::vector<std::string> vec_find = {"fooo", "baar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace_multiple(str, vec_find, str_replace);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_neg)
{
    const std::string str = "foobar foobar foobar";
    const std::vector<std::string> vec_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz bazbaz";
    const std::string result = ztd::replace_multiple(str, vec_find, str_replace, -5);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_0)
{
    const std::string str = "foobar foobar foobar";
    const std::vector<std::string> vec_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace_multiple(str, vec_find, str_replace, 0);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_1)
{
    const std::string str = "foobar foobar foobar";
    const std::vector<std::string> vec_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz foobar foobar";
    const std::string result = ztd::replace_multiple(str, vec_find, str_replace, 1);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_2)
{
    const std::string str = "foobar foobar foobar";
    const std::vector<std::string> vec_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz foobar";
    const std::string result = ztd::replace_multiple(str, vec_find, str_replace, 2);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(string_utils, replace_multiple__vector__count_3)
{
    const std::string str = "foobar foobar foobar";
    const std::vector<std::string> vec_find = {"foo", "bar"};
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbaz bazbaz bazbaz";
    const std::string result = ztd::replace_multiple(str, vec_find, str_replace, 3);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

#ifndef ZTD_DISABLE_DEPRECATED
/**
 * prefix
 */
TEST(deprecated, prefix)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = "foobar";

    ASSERT_TRUE(ztd::prefix(str1, str2));

    const std::string str3 = "foobar test string";
    const std::string str4 = "test";

    ASSERT_FALSE(ztd::prefix(str3, str4));
}

/**
 * suffix
 */
TEST(deprecated, suffix)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = "string";

    ASSERT_TRUE(ztd::suffix(str1, str2));

    const std::string str3 = "foobar test string";
    const std::string str4 = "test";

    ASSERT_FALSE(ztd::suffix(str3, str4));
}

/**
 * ltrim
 */
TEST(deprecated, ltrim)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "a  ";
    const std::string result = ztd::ltrim(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * rtrim
 */
TEST(deprecated, rtrim)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "  a";
    const std::string result = ztd::rtrim(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * trim
 */
TEST(deprecated, trim)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "a";
    const std::string result = ztd::trim(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

/**
 * isame(string, string)
 */
TEST(string_utils, isame__string_string)
{
    const std::string str1 = "SAME string";
    const std::string str2 = "same STRING";
    const std::string str3 = str2;

    ASSERT_TRUE(ztd::isame(str1, str2));

    ASSERT_TRUE(ztd::isame(str1, str3));

    const std::string str4 = "SAME string";
    const std::string str5 = "not same STRING";

    ASSERT_FALSE(ztd::isame(str4, str5));
}

/**
 * same(string, char*)
 */
TEST(string_utils, isame__string_char)
{
    const std::string str1 = "not same";
    const char* str2 = nullptr;

    ASSERT_FALSE(ztd::isame(str1, str2));

    const std::string str3 = "SAME string";
    const char* str4 = "same STRING";

    ASSERT_TRUE(ztd::isame(str3, str4));
}

/**
 * same(char*, string)
 */
TEST(string_utils, isame__char_string)
{
    const char* str1 = nullptr;
    const std::string str2 = "not same";

    ASSERT_FALSE(ztd::isame(str1, str2));

    const char* str3 = "SAME string";
    const std::string str4 = "same STRING";

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
    const std::string str1 = "Just a test string in a test case";
    const std::string str2 = "test ";

    const std::string result_wanted = "case";
    const std::string result = ztd::remove_before(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));

    ASSERT_TRUE(ztd::same(ztd::rpartition(str1, str2)[2], result_wanted));
}

TEST(string_utils, remove_before_2)
{
    const std::string str1 = "foobar$foobar$foobar";
    const std::string str2 = "$";

    const std::string result_wanted = "foobar";
    const std::string result = ztd::remove_before(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));

    ASSERT_TRUE(ztd::same(ztd::rpartition(str1, str2)[2], result_wanted));
}

/**
 * remove_after
 */
TEST(string_utils, remove_after)
{
    const std::string str1 = "Just a test string in a test case";
    const std::string str2 = " test";

    const std::string result_wanted = "Just a";
    const std::string result = ztd::remove_after(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));

    ASSERT_TRUE(ztd::same(ztd::partition(str1, str2)[0], result_wanted));
}

TEST(string_utils, remove_after_2)
{
    const std::string str1 = "foobar$foobar$foobar";
    const std::string str2 = "$";

    const std::string result_wanted = "foobar";
    const std::string result = ztd::remove_after(str1, str2);

    ASSERT_TRUE(ztd::same(result, result_wanted));

    ASSERT_TRUE(ztd::same(ztd::partition(str1, str2)[0], result_wanted));
}
#endif
