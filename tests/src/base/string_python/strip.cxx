/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <string>

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::ljust")
{
    std::string str;
    std::string wanted;
    ztd::usize width = 10_usize;
    char fillchar = ' ';

    SUBCASE("empty")
    {
        str = "";
        wanted = "          ";
    }

    SUBCASE("empty fillchar")
    {
        str = "";
        fillchar = 'x';
        wanted = "xxxxxxxxxx";
    }

    SUBCASE("ljust")
    {
        str = "string";
        wanted = "string    ";
    }

    CHECK_EQ(ztd::ljust(str, width, fillchar), wanted);
}

TEST_CASE("ztd::rjust")
{
    std::string str;
    std::string wanted;
    ztd::usize width = 10_usize;
    char fillchar = ' ';

    SUBCASE("empty")
    {
        str = "";
        wanted = "          ";
    }

    SUBCASE("empty fillchar")
    {
        str = "";
        fillchar = 'x';
        wanted = "xxxxxxxxxx";
    }

    SUBCASE("rjust")
    {
        str = "string";
        wanted = "    string";
    }

    CHECK_EQ(ztd::rjust(str, width, fillchar), wanted);
}

TEST_CASE("ztd::lstrip")
{
    std::string str;
    std::string chars = " \r\n\t";
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("lstrip")
    {
        str = "  a  ";
        wanted = "a  ";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = " a z";
    }

    CHECK_EQ(ztd::lstrip(str, chars), wanted);
}

TEST_CASE("ztd::rstrip")
{
    std::string str;
    std::string chars = " \r\n\t";
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("rstrip")
    {
        str = "  a  ";
        wanted = "  a";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = "z a ";
    }

    CHECK_EQ(ztd::rstrip(str, chars), wanted);
}

TEST_CASE("ztd::strip")
{
    std::string str;
    std::string chars = " \r\n\t";
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("strip")
    {
        str = "  a  ";
        wanted = "a";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = " a ";
    }

    CHECK_EQ(ztd::strip(str, chars), wanted);
}
