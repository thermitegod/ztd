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

TEST_CASE("ztd::capitalize")
{
    std::string str;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("space")
    {
        str = " will not capitalize the first letter.";
        wanted = " will not capitalize the first letter.";
    }

    SUBCASE("lower")
    {
        str = "capitalize only the first letter.";
        wanted = "Capitalize only the first letter.";
    }

    SUBCASE("upper")
    {
        str = "AAAA BBBB CCCC";
        wanted = "Aaaa bbbb cccc";
    }

    SUBCASE("mixed")
    {
        str = "aAaA BbBb CcCc";
        wanted = "Aaaa bbbb cccc";
    }

    CHECK_EQ(ztd::capitalize(str), wanted);
}
