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

TEST_CASE("ztd::title")
{
    std::string str;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("title")
    {
        str = "String";
        wanted = "String";
    }

    SUBCASE("all lower")
    {
        str = "string a string";
        wanted = "String A String";
    }

    SUBCASE("all upper")
    {
        str = "STRING A STRING";
        wanted = "String A String";
    }

    SUBCASE("mixed")
    {
        str = "StRiNg a sTrInG";
        wanted = "String A String";
    }

    SUBCASE("special")
    {
        str = "String ~!@#$%^&*()-_+{}|<>?,./";
        wanted = "String ~!@#$%^&*()-_+{}|<>?,./";
    }

    SUBCASE("python example")
    {
        str = "they're bill's friends from the UK";
        wanted = "They'Re Bill'S Friends From The Uk";
    }

    CHECK_EQ(ztd::title(str), wanted);
}
