/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

TEST_CASE("ztd::zfill")
{
    std::string str;
    ztd::usize width = 10_usize;
    std::string wanted;

    SUBCASE("str")
    {
        str = "string";
        wanted = "0000string";
    }

    SUBCASE("str pos")
    {
        str = "+string";
        wanted = "+000string";
    }

    SUBCASE("str neg")
    {
        str = "-string";
        wanted = "-000string";
    }

    SUBCASE("str int")
    {
        str = "420";
        wanted = "0000000420";
    }

    SUBCASE("str int pos")
    {
        str = "+420";
        wanted = "+000000420";
    }

    SUBCASE("str int neg")
    {
        str = "-420";
        wanted = "-000000420";
    }

    SUBCASE("empty")
    {
        str = "";
        wanted = "0000000000";
    }

    SUBCASE("sign pos only")
    {
        str = "+";
        wanted = "+000000000";
    }

    SUBCASE("sign neg only")
    {
        str = "-";
        wanted = "-000000000";
    }

    SUBCASE("sign no fill")
    {
        str = "string";
        width = str.size();
        wanted = "string";
    }

    CHECK_EQ(ztd::zfill(str, width), wanted);
}
