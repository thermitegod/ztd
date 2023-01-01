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

#include <gtest/gtest.h>

#include <string>

#include "ztd/ztd.hxx"

/**
 * strdup char*
 */
TEST(c_interface, strdup__char)
{
    const char* str = "test string";

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same(str, result));
}

TEST(c_interface, strdup__char__nullptr)
{
    char* n = nullptr;

    const char* result = ztd::strdup(n);

    EXPECT_TRUE(result == nullptr);
}

/**
 * strdup std::string
 */
TEST(c_interface, strdup__string)
{
    const std::string str = "test string";

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same(str, result));
}

/**
 * strdup std::string*
 */
TEST(c_interface, strdup__string_ptr)
{
    const std::string* str = new std::string("test string");

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same(str->c_str(), result));

    delete str;
}

TEST(c_interface, strdup__string_ptr__nullptr)
{
    const std::string* str = nullptr;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(result == nullptr);
}

/**
 * strdup std::enable_if std::is_integral overload
 */
TEST(c_interface, strdup__int)
{
    int str = 69420;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420", result));
}

TEST(c_interface, strdup__unsigned_int)
{
    unsigned int str = 69420;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420", result));
}

TEST(c_interface, strdup__long)
{
    long str = 69420;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420", result));
}

TEST(c_interface, strdup__unsigned_long)
{
    unsigned long str = 69420;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420", result));
}

TEST(c_interface, strdup__long_long)
{
    long long str = 69420;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420", result));
}

TEST(c_interface, strdup__unsigned_long_long)
{
    unsigned long long str = 69420;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420", result));
}

/**
 * strdup std::enable_if std::is_floating_point overload
 */
TEST(c_interface, strdup__float)
{
    float str = 69420.0;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420.000000", result));
}

TEST(c_interface, strdup__double)
{
    double str = 69420.0;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420.000000", result));
}

TEST(c_interface, strdup__long_double)
{
    long double str = 69420.0;

    const char* result = ztd::strdup(str);

    EXPECT_TRUE(ztd::same("69420.000000", result));
}

/**
 * strdup std::enable_if std::is_enum
 */
TEST(c_interface, strdup__enum)
{
    enum TestEnum
    {
        T1,
        T2,
        T3,
    };

    const char* result1 = ztd::strdup(TestEnum::T1);
    EXPECT_TRUE(ztd::same("0", result1));

    const char* result2 = ztd::strdup(TestEnum::T2);
    EXPECT_TRUE(ztd::same("1", result2));

    const char* result3 = ztd::strdup(TestEnum::T3);
    EXPECT_TRUE(ztd::same("2", result3));
}

TEST(c_interface, strdup__enum_class)
{
    enum class TestEnum
    {
        T1,
        T2,
        T3,
    };

    const char* result1 = ztd::strdup(TestEnum::T1);
    EXPECT_TRUE(ztd::same("0", result1));

    const char* result2 = ztd::strdup(TestEnum::T2);
    EXPECT_TRUE(ztd::same("1", result2));

    const char* result3 = ztd::strdup(TestEnum::T3);
    EXPECT_TRUE(ztd::same("2", result3));
}
