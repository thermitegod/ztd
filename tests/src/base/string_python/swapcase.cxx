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

TEST_CASE("ztd::swapcase")
{
    std::string str;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("swapcase")
    {
        str = "String";
        wanted = "sTRING";
    }

    SUBCASE("all lower")
    {
        str = "string string";
        wanted = "STRING STRING";
    }

    SUBCASE("all upper")
    {
        str = "STRING STRING";
        wanted = "string string";
    }

    SUBCASE("mixed")
    {
        str = "StRiNg sTrInG";
        wanted = "sTrInG StRiNg";
    }

    SUBCASE("special")
    {
        str = "String ~!@#$%^&*()-_+{}|<>?,./";
        wanted = "sTRING ~!@#$%^&*()-_+{}|<>?,./";
    }

    CHECK_EQ(ztd::swapcase(str), wanted);
}
