/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
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

#if (ZTD_VERSION == 1)

#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include <vector>

#include "ztd/ztd.hxx"

/**
 * compare(string, string)
 */
TEST(string_utils, compare__string_string__eq)
{
    const std::string str1 = "aaaa";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__string_string__ge)
{
    const std::string str1 = "bbbb";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__string_string__le)
{
    const std::string str1 = "aaaa";
    const std::string str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__string_string__eq)
{
    const std::string str1 = "aaaa";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2.c_str()));
}

TEST(string_utils, compare_strcmp__string_string__ge)
{
    const std::string str1 = "bbbb";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2.c_str()));
}

TEST(string_utils, compare_strcmp__string_string__le)
{
    const std::string str1 = "aaaa";
    const std::string str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2.c_str()));
}

/**
 * compare(string, char*)
 */
TEST(string_utils, compare__string_char__eq)
{
    const std::string str1 = "aaaa";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__string_char__ge)
{
    const std::string str1 = "bbbb";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__string_char__le)
{
    const std::string str1 = "aaaa";
    const char* str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__string_char__eq)
{
    const std::string str1 = "aaaa";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2));
}

TEST(string_utils, compare_strcmp__string_char__ge)
{
    const std::string str1 = "bbbb";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2));
}

TEST(string_utils, compare_strcmp__string_char__le)
{
    const std::string str1 = "aaaa";
    const char* str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2));
}

/**
 * compare(char*, string)
 */
TEST(string_utils, compare__char_string__eq)
{
    const char* str1 = "aaaa";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__char_string__ge)
{
    const char* str1 = "bbbb";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__char_string__le)
{
    const char* str1 = "aaaa";
    const std::string str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__char_string__eq)
{
    const char* str1 = "aaaa";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2.c_str()));
}

TEST(string_utils, compare_strcmp__char_string__ge)
{
    const char* str1 = "bbbb";
    const std::string str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2.c_str()));
}

TEST(string_utils, compare_strcmp__char_string__le)
{
    const char* str1 = "aaaa";
    const std::string str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2.c_str()));
}

/**
 * compare(char*, char*)
 */
TEST(string_utils, compare__char_char__eq)
{
    const char* str1 = "aaaa";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__char_char__ge)
{
    const char* str1 = "bbbb";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__char_char__le)
{
    const char* str1 = "aaaa";
    const char* str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__char_char__eq)
{
    const char* str1 = "aaaa";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2));
}

TEST(string_utils, compare_strcmp__char_char__ge)
{
    const char* str1 = "bbbb";
    const char* str2 = "aaaa";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2));
}

TEST(string_utils, compare_strcmp__char_char__le)
{
    const char* str1 = "aaaa";
    const char* str2 = "bbbb";

    EXPECT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2));
}

/**
 * contains(string, string)
 */
TEST(string_utils, contains__string_string__true)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_string__false)
{
    const std::string str3 = "foobarbaz";
    const std::string str4 = "buz";

    EXPECT_FALSE(ztd::contains(str3, str4));
}

/**
 * contains(string, string) start/end
 */
TEST(string_utils, contains__string_string__start_end__true)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__string_string__start_end__false)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 0, 4));
}

TEST(string_utils, contains__string_string__start_end__same)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__string_string__start_end__large_start)
{
    const std::string str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 3, 2));
}

/**
 * contains(string, char*)
 */
TEST(string_utils, contains__string_char__true)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__string_char__false)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bur";

    EXPECT_FALSE(ztd::contains(str1, str2));
}

/**
 * contains(string, char*) start/end
 */
TEST(string_utils, contains__string_char__start_end__true)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__string_char__start_end__false)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 0, 4));
}

TEST(string_utils, contains__string_char__start_end__same)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__string_char__start_end__large_start)
{
    const std::string str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 3, 2));
}

/**
 * contains(char*, string)
 */
TEST(string_utils, contains__char_string__true)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_string__false)
{
    const char* str3 = "foobarbaz";
    const std::string str4 = "bur";

    EXPECT_FALSE(ztd::contains(str3, str4));
}

/**
 * contains(char*, string) start/end
 */
TEST(string_utils, contains__char_string__start_end__true)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__char_string__start_end__false)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 0, 4));
}

TEST(string_utils, contains__char_string__start_end__same)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__char_string__start_end__large_start)
{
    const char* str1 = "foobarbaz";
    const std::string str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 3, 2));
}

/**
 * contains(char*, char*)
 */
TEST(string_utils, contains__char_char__true)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2));
}

TEST(string_utils, contains__char_char__false)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bur";

    EXPECT_FALSE(ztd::contains(str1, str2));
}

/**
 * contains(char*, char*) start/end
 */
TEST(string_utils, contains__char_char__start_end__true)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_TRUE(ztd::contains(str1, str2, 2, 8));
}

TEST(string_utils, contains__char_char__start_end__false)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 0, 4));
}

TEST(string_utils, contains__char_char__start_end__same)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 2, 2));
}

TEST(string_utils, contains__char_char__start_end__large_start)
{
    const char* str1 = "foobarbaz";
    const char* str2 = "bar";

    EXPECT_FALSE(ztd::contains(str1, str2, 3, 2));
}

/**
 * contains(string_view, array<string_view>)
 */
TEST(string_utils, contains__string_view__array__empty1)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "";
    const std::array<std::string_view, 1> a1{"foo"sv};

    EXPECT_FALSE(ztd::contains(str1, a1));
}

TEST(string_utils, contains__string_view__array__empty2)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "";
    const std::array<std::string_view, 1> a1{"foo"sv};

    EXPECT_FALSE(ztd::contains(str1, a1));
}

TEST(string_utils, contains__string_view__array)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "foobar";
    const std::array<std::string_view, 2> a1{"foo"sv, "bar"sv};

    EXPECT_TRUE(ztd::contains(str1, a1));

    const std::string str2 = "bazbar";
    const std::array<std::string_view, 2> a2{"foo"sv, "bar"sv};

    EXPECT_TRUE(ztd::contains(str2, a2));

    const std::string str3 = "foobar";
    const std::array<std::string_view, 2> a3{"fuz"sv, "baz"sv};

    EXPECT_FALSE(ztd::contains(str3, a3));
}

/**
 * contains(array<string_view>, string_view)
 */
TEST(string_utils, contains__array__string_view__empty1)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "";
    const std::array<std::string_view, 1> a1{"foo"sv};

    EXPECT_FALSE(ztd::contains(a1, str1));
}

TEST(string_utils, contains__array__string_view__empty2)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "";
    const std::array<std::string_view, 1> a1{"foo"sv};

    EXPECT_FALSE(ztd::contains(a1, str1));
}

TEST(string_utils, contains__array__string_view)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "foobar";
    const std::array<std::string_view, 2> a1{"foo"sv, "bar"sv};

    EXPECT_FALSE(ztd::contains(a1, str1));

    const std::string str2 = "bazbar";
    const std::array<std::string_view, 2> a2{"foo"sv, "bar"sv};

    EXPECT_FALSE(ztd::contains(a2, str2));

    const std::string str3 = "foobar";
    const std::array<std::string_view, 2> a3{"fuz"sv, "baz"sv};

    EXPECT_FALSE(ztd::contains(a3, str3));

    const std::string str4 = "foo";
    const std::array<std::string_view, 2> a4{"foo"sv, "bar"sv};

    EXPECT_TRUE(ztd::contains(a4, str4));

    const std::string str5 = "baz";
    const std::array<std::string_view, 2> a5{"fuz"sv, "baz"sv};

    EXPECT_TRUE(ztd::contains(a5, str5));
}

/**
 * contains(string_view, array<string>)
 */
TEST(string_utils, contains__string_view__array_string__empty1)
{
    const std::string str1 = "";
    const std::array<std::string, 1> v1{"foo"};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string_view__array_string__empty2)
{
    std::string_view str1 = "";
    const std::array<std::string, 1> v1{"foo"};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string__array)
{
    const std::string str1 = "foobar";
    const std::array<std::string, 2> a1{"foo", "bar"};

    EXPECT_TRUE(ztd::contains(str1, a1));

    const std::string str2 = "bazbar";
    const std::array<std::string, 2> a2{"foo", "bar"};

    EXPECT_TRUE(ztd::contains(str2, a2));

    const std::string str3 = "foobar";
    const std::array<std::string, 2> a3{"fuz", "baz"};

    EXPECT_FALSE(ztd::contains(str3, a3));
}

/**
 * contains(array<string>, string_view)
 */
TEST(string_utils, contains__array_string__empty1)
{
    const std::string str1 = "";
    const std::array<std::string, 1> a1{"foo"};

    EXPECT_FALSE(ztd::contains(a1, str1));
}

TEST(string_utils, contains__array__string__empty2)
{
    std::string_view str1 = "";
    const std::array<std::string, 1> a1{"foo"};

    EXPECT_FALSE(ztd::contains(a1, str1));
}

TEST(string_utils, contains__array__string)
{
    const std::string str1 = "foobar";
    const std::array<std::string, 2> a1{"foo", "bar"};

    EXPECT_FALSE(ztd::contains(a1, str1));

    const std::string str2 = "bazbar";
    const std::array<std::string, 2> a2{"foo", "bar"};

    EXPECT_FALSE(ztd::contains(a2, str2));

    const std::string str3 = "foobar";
    const std::array<std::string, 2> a3{"fuz", "baz"};

    EXPECT_FALSE(ztd::contains(a3, str3));

    const std::string str4 = "foo";
    const std::array<std::string, 2> a4{"foo", "bar"};

    EXPECT_TRUE(ztd::contains(a4, str4));

    const std::string str5 = "baz";
    const std::array<std::string, 2> a5{"fuz", "baz"};

    EXPECT_TRUE(ztd::contains(a5, str5));
}

/**
 * contains(string_view, vector<string_view>)
 */
TEST(string_utils, contains__string_view__vector__empty1)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "";
    const std::vector<std::string_view> v1{"foo"sv};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string_view__vector__empty2)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "";
    const std::vector<std::string_view> v1{"foo"sv};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string_view__vector__vec_empty)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "foobar";
    const std::vector<std::string_view> v1{};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string_view__vector)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "foobar";
    const std::vector<std::string_view> v1{"foo"sv, "bar"sv};

    EXPECT_TRUE(ztd::contains(str1, v1));

    const std::string str2 = "bazbar";
    const std::vector<std::string_view> v2{"foo"sv, "bar"sv};

    EXPECT_TRUE(ztd::contains(str2, v2));

    const std::string str3 = "foobar";
    const std::vector<std::string_view> v3{"fuz"sv, "baz"sv};

    EXPECT_FALSE(ztd::contains(str3, v3));
}

/**
 * contains(vector<string_view>, string_view)
 */
TEST(string_utils, contains__vector__string_view__empty1)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "";
    const std::vector<std::string_view> v1{"foo"sv};

    EXPECT_FALSE(ztd::contains(v1, str1));
}

TEST(string_utils, contains__vector__string_view__empty2)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "";
    const std::vector<std::string_view> v1{"foo"sv};

    EXPECT_FALSE(ztd::contains(v1, str1));
}

TEST(string_utils, contains__vector__string_view__vec_empty)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "foobar";
    const std::vector<std::string_view> v1{};

    EXPECT_FALSE(ztd::contains(v1, str1));
}

TEST(string_utils, contains__vector__string_view)
{
    using namespace std::literals::string_view_literals;

    const std::string str1 = "foobar";
    const std::vector<std::string_view> v1{"foo"sv, "bar"sv};

    EXPECT_FALSE(ztd::contains(v1, str1));

    const std::string str2 = "bazbar";
    const std::vector<std::string_view> v2{"foo"sv, "bar"sv};

    EXPECT_FALSE(ztd::contains(v2, str2));

    const std::string str3 = "foobar";
    const std::vector<std::string_view> v3{"fuz"sv, "baz"sv};

    EXPECT_FALSE(ztd::contains(v3, str3));

    const std::string str4 = "foo";
    const std::vector<std::string_view> v4{"foo"sv, "bar"sv};

    EXPECT_TRUE(ztd::contains(v4, str4));

    const std::string str5 = "baz";
    const std::vector<std::string_view> v5{"fuz"sv, "baz"sv};

    EXPECT_TRUE(ztd::contains(v5, str5));
}

/**
 * contains(string_view, vector<string>)
 */
TEST(string_utils, contains__string__vector__empty1)
{
    const std::string str1 = "";
    const std::vector<std::string> v1{"foo"};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string__vector__empty2)
{
    using namespace std::literals::string_view_literals;

    std::string_view str1 = "";
    const std::vector<std::string_view> v1{"foo"sv};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string__vector__vec_empty)
{
    const std::string str1 = "foobar";
    const std::vector<std::string> v1{};

    EXPECT_FALSE(ztd::contains(str1, v1));
}

TEST(string_utils, contains__string__vector)
{
    const std::string str1 = "foobar";
    const std::vector<std::string> v1{"foo", "bar"};

    EXPECT_TRUE(ztd::contains(str1, v1));

    const std::string str2 = "bazbar";
    const std::vector<std::string> v2{"foo", "bar"};

    EXPECT_TRUE(ztd::contains(str2, v2));

    const std::string str3 = "foobar";
    const std::vector<std::string> v3{"fuz", "baz"};

    EXPECT_FALSE(ztd::contains(str3, v3));
}

/**
 * contains(vector<string>, string_view)
 */
TEST(string_utils, contains__vector__string__empty1)
{
    const std::string str1 = "";
    const std::vector<std::string> v1{"foo"};

    EXPECT_FALSE(ztd::contains(v1, str1));
}

TEST(string_utils, contains__vector__string__empty2)
{
    std::string_view str1 = "";
    const std::vector<std::string> v1{"foo"};

    EXPECT_FALSE(ztd::contains(v1, str1));
}

TEST(string_utils, contains__vector__string__vec_empty)
{
    std::string_view str1 = "foobar";
    const std::vector<std::string> v1{};

    EXPECT_FALSE(ztd::contains(v1, str1));
}

TEST(string_utils, contains__vector__string)
{
    const std::string str1 = "foobar";
    const std::vector<std::string> v1{"foo", "bar"};

    EXPECT_FALSE(ztd::contains(v1, str1));

    const std::string str2 = "bazbar";
    const std::vector<std::string> v2{"foo", "bar"};

    EXPECT_FALSE(ztd::contains(v2, str2));

    const std::string str3 = "foobar";
    const std::vector<std::string> v3{"fuz", "baz"};

    EXPECT_FALSE(ztd::contains(v3, str3));

    const std::string str4 = "foo";
    const std::vector<std::string> v4{"foo", "bar"};

    EXPECT_TRUE(ztd::contains(v4, str4));

    const std::string str5 = "baz";
    const std::vector<std::string> v5{"fuz", "baz"};

    EXPECT_TRUE(ztd::contains(v5, str5));
}

/**
 * same(string, string)
 */
TEST(string_utils, same__string_string)
{
    const std::string str1 = "same string";
    const std::string str2 = "same string";
    const std::string str3 = str2;

    EXPECT_TRUE(ztd::same(str1, str2));
    EXPECT_TRUE(ztd::same(str1, str3));

    const std::string str4 = "same string";
    const std::string str5 = "not same string";

    EXPECT_FALSE(ztd::same(str4, str5));
}

/**
 * same(string, char*)
 */
TEST(string_utils, same__string_char)
{
    const std::string str1 = "same";
    const char* str2 = "not same";

    EXPECT_FALSE(ztd::same(str1, str2));

    const std::string str3 = "same string";
    const char* str4 = "same string";

    EXPECT_TRUE(ztd::same(str3, str4));
}

/**
 * same(char*, string)
 */
TEST(string_utils, same__char_string)
{
    const char* str1 = "same";
    const std::string str2 = "not same";

    EXPECT_FALSE(ztd::same(str1, str2));

    const std::string str3 = "same string";
    const char* str4 = "same string";

    EXPECT_TRUE(ztd::same(str3, str4));
}

/**
 * same(char*, char*)
 */
TEST(string_utils, same__char_char)
{
    const char* str1 = "same";
    const char* str2 = "not same";

    EXPECT_FALSE(ztd::same(str1, str2));

    const char* str3 = "same";
    const char* str4 = "not same";

    EXPECT_FALSE(ztd::same(str3, str4));

    const char* str5 = "same string";
    const char* str6 = "same string";

    EXPECT_TRUE(ztd::same(str5, str6));
}

#endif
