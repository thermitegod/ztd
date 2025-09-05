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

TEST_CASE("ztd::center")
{
    std::string str;
    std::string wanted;
    ztd::u32 width = 0_u32;

    SUBCASE("even string even width")
    {
        str = "even";
        wanted = "   even   ";
        width = 10_u32;
    }

    SUBCASE("even string odd width")
    {
        str = "even";
        wanted = "  even   ";
        width = 9_u32;
    }

    SUBCASE("odd string odd width")
    {
        str = "odd";
        wanted = " odd ";
        width = 5_u32;
    }

    SUBCASE("odd string even width")
    {
        str = "odd";
        wanted = "   odd    ";
        width = 10_u32;
    }

    SUBCASE("str empty")
    {
        str = "";
        wanted = "     ";
        width = 5_u32;
    }

    CHECK_EQ(ztd::center(str, width), wanted);
}
