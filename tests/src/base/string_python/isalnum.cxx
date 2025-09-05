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

TEST_CASE("ztd::isalnum")
{
    std::string str;
    bool wanted = false;

    SUBCASE("empty")
    {
        str = "";
        wanted = false;
    }

    SUBCASE("all alpha")
    {
        str = "alphastring";
        wanted = true;
    }

    SUBCASE("all digit")
    {
        str = "69420";
        wanted = true;
    }

    SUBCASE("mixed")
    {
        str = "alnumstring69420";
        wanted = true;
    }

    SUBCASE("specia ")
    {
        str = "!@#$%^&*()_+{}";
        wanted = false;
    }

    SUBCASE("space")
    {
        str = "not alnum string";
        wanted = false;
    }

    CHECK_EQ(ztd::isalnum(str), wanted);
}
