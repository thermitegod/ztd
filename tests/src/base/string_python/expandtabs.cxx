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

TEST_CASE("ztd::expandtabs")
{
    std::string str;
    std::string wanted;
    ztd::u32 tabsize = 8_u32;

    SUBCASE("4")
    {
        str = "01\t012\t0123\t01234";
        wanted = "01  012 0123    01234";
        tabsize = 4_u32;
    }

    SUBCASE("8")
    {
        str = "01\t012\t0123\t01234";
        wanted = "01      012     0123    01234";
        tabsize = 8_u32;
    }

    SUBCASE("LF")
    {
        str = "01\t012\t0123\t01234\n012345\t0123";
        wanted = "01      012     0123    01234\n012345  0123";
    }

    SUBCASE("CR")
    {
        str = "01\t012\t0123\t01234\r012345\t0123";
        wanted = "01      012     0123    01234\r012345  0123";
    }

    SUBCASE("CRLF")
    {
        str = "01\t012\t0123\t01234\r\n012345\t0123";
        wanted = "01      012     0123    01234\r\n012345  0123";
    }

    CHECK_EQ(ztd::expandtabs(str, tabsize), wanted);
}
