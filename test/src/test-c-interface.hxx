/**
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

#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include "../../src/ztd.hxx"

TEST_CASE("::null_check")
{
    char* n = nullptr;

    std::string str = ztd::null_check(n);

    REQUIRE(ztd::same(str, ""));
}

TEST_CASE("::strdup char*")
{
    const char* str = "test string";

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same(str, result));
}

TEST_CASE("::strdup std::string")
{
    std::string str = "test string";

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same(str, result));
}

/*
TEST_CASE("::strdup std::string*")
{
    std::string* str = new std::string("test string");

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same(str->c_str(), result));

    delete str;
}
*/

TEST_CASE("::strdup int")
{
    int str = 69420;

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same("69420", result));
}

TEST_CASE("::strdup unsigned int")
{
    unsigned int str = 69420;

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same("69420", result));
}

TEST_CASE("::strdup long")
{
    long str = 69420;

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same("69420", result));
}

TEST_CASE("::strdup unsigned long")
{
    unsigned long str = 69420;

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same("69420", result));
}

TEST_CASE("::strdup long long")
{
    long long str = 69420;

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same("69420", result));
}

TEST_CASE("::strdup unsigned long long")
{
    unsigned long long str = 69420;

    const char* result = ztd::strdup(str);

    REQUIRE(ztd::same("69420", result));
}

TEST_CASE("::strdup float")
{
    float str = 69420.0;

    const char* result = ztd::strdup(str);

    INFO(result);

    REQUIRE(ztd::same("69420.000000", result));
}

TEST_CASE("::strdup double")
{
    double str = 69420.0;

    const char* result = ztd::strdup(str);

    INFO(result);

    REQUIRE(ztd::same("69420.000000", result));
}

TEST_CASE("::strdup long double")
{
    long double str = 69420.0;

    const char* result = ztd::strdup(str);

    INFO(result);

    REQUIRE(ztd::same("69420.000000", result));
}
