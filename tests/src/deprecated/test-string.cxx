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
#include <vector>

#include "../../../src/ztd.hxx"

TEST(deprecated, prefix)
{
    std::string str1 = "foobar test string";
    std::string str2 = "foobar";

    ASSERT_TRUE(ztd::prefix(str1, str2));

    std::string str3 = "foobar test string";
    std::string str4 = "test";

    ASSERT_FALSE(ztd::prefix(str3, str4));
}

TEST(deprecated, suffix)
{
    std::string str1 = "foobar test string";
    std::string str2 = "string";

    ASSERT_TRUE(ztd::suffix(str1, str2));

    std::string str3 = "foobar test string";
    std::string str4 = "test";

    ASSERT_FALSE(ztd::suffix(str3, str4));
}

TEST(deprecated, ltrim)
{
    std::string str = "  a  ";

    std::string result_wanted = "a  ";
    std::string result = ztd::ltrim(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(deprecated, rtrim)
{
    std::string str = "  a  ";

    std::string result_wanted = "  a";
    std::string result = ztd::rtrim(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
}

TEST(deprecated, trim)
{
    std::string str = "  a  ";

    std::string result_wanted = "a";
    std::string result = ztd::trim(str);

    ASSERT_TRUE(ztd::same(result, result_wanted));
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
