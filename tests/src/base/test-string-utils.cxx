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

    ASSERT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__string_string__ge)
{
    const std::string str1 = "bbbb";
    const std::string str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__string_string__le)
{
    const std::string str1 = "aaaa";
    const std::string str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__string_string__eq)
{
    const std::string str1 = "aaaa";
    const std::string str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2.c_str()));
}

TEST(string_utils, compare_strcmp__string_string__ge)
{
    const std::string str1 = "bbbb";
    const std::string str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2.c_str()));
}

TEST(string_utils, compare_strcmp__string_string__le)
{
    const std::string str1 = "aaaa";
    const std::string str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2.c_str()));
}

/**
 * compare(string, char*)
 */
TEST(string_utils, compare__string_char__eq)
{
    const std::string str1 = "aaaa";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__string_char__ge)
{
    const std::string str1 = "bbbb";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__string_char__le)
{
    const std::string str1 = "aaaa";
    const char* str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__string_char__eq)
{
    const std::string str1 = "aaaa";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2));
}

TEST(string_utils, compare_strcmp__string_char__ge)
{
    const std::string str1 = "bbbb";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2));
}

TEST(string_utils, compare_strcmp__string_char__le)
{
    const std::string str1 = "aaaa";
    const char* str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1.c_str(), str2));
}

/**
 * compare(char*, string)
 */
TEST(string_utils, compare__char_string__eq)
{
    const char* str1 = "aaaa";
    const std::string str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__char_string__ge)
{
    const char* str1 = "bbbb";
    const std::string str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__char_string__le)
{
    const char* str1 = "aaaa";
    const std::string str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__char_string__eq)
{
    const char* str1 = "aaaa";
    const std::string str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2.c_str()));
}

TEST(string_utils, compare_strcmp__char_string__ge)
{
    const char* str1 = "bbbb";
    const std::string str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2.c_str()));
}

TEST(string_utils, compare_strcmp__char_string__le)
{
    const char* str1 = "aaaa";
    const std::string str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2.c_str()));
}

/**
 * compare(char*, char*)
 */
TEST(string_utils, compare__char_char__eq)
{
    const char* str1 = "aaaa";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == 0);
}

TEST(string_utils, compare__char_char__ge)
{
    const char* str1 = "bbbb";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) > 0);
}

TEST(string_utils, compare__char_char__le)
{
    const char* str1 = "aaaa";
    const char* str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) < 0);
}

TEST(string_utils, compare_strcmp__char_char__eq)
{
    const char* str1 = "aaaa";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2));
}

TEST(string_utils, compare_strcmp__char_char__ge)
{
    const char* str1 = "bbbb";
    const char* str2 = "aaaa";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2));
}

TEST(string_utils, compare_strcmp__char_char__le)
{
    const char* str1 = "aaaa";
    const char* str2 = "bbbb";

    ASSERT_TRUE(ztd::compare(str1, str2) == strcmp(str1, str2));
}

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
    const std::string str1 = "same";
    const char* str2 = "not same";

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
    const char* str1 = "same";
    const std::string str2 = "not same";

    ASSERT_FALSE(ztd::same(str1, str2));

    const std::string str3 = "same string";
    const char* str4 = "same string";

    ASSERT_TRUE(ztd::same(str3, str4));
}

/**
 * same(char*, char*)
 */
TEST(string_utils, same__char_char)
{
    const char* str1 = "same";
    const char* str2 = "not same";

    ASSERT_FALSE(ztd::same(str1, str2));

    const char* str3 = "same";
    const char* str4 = "not same";

    ASSERT_FALSE(ztd::same(str3, str4));

    const char* str5 = "same string";
    const char* str6 = "same string";

    ASSERT_TRUE(ztd::same(str5, str6));
}
