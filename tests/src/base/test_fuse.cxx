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

#include <doctest/doctest.h>

#include "ztd/detail/fuse.hxx"

TEST_SUITE("ztd::fuse" * doctest::description(""))
{
    TEST_CASE("fuse default init")
    {
        ztd::fuse fuse;
        REQUIRE_EQ(fuse, false);
    }

    TEST_CASE("fuse init true")
    {
        ztd::fuse fuse = true;
        REQUIRE_EQ(fuse, true);

        SUBCASE("set true")
        {
            CHECK_EQ(fuse.is_blown(), false);

            fuse = true;
            CHECK_EQ(fuse, true);

            fuse = false;
            CHECK_EQ(fuse, true);

            CHECK_EQ(fuse.is_blown(), true);
        }

        SUBCASE("set false")
        {
            CHECK_EQ(fuse.is_blown(), false);

            fuse = false;
            CHECK_EQ(fuse, false);

            fuse = true;
            CHECK_EQ(fuse, false);

            CHECK_EQ(fuse.is_blown(), true);
        }
    }

    TEST_CASE("fuse init false")
    {
        ztd::fuse fuse = false;
        REQUIRE_EQ(fuse, false);

        SUBCASE("set true")
        {
            CHECK_EQ(fuse.is_blown(), false);

            fuse = true;
            CHECK_EQ(fuse, true);

            fuse = false;
            CHECK_EQ(fuse, true);

            CHECK_EQ(fuse.is_blown(), true);
        }

        SUBCASE("set false")
        {
            CHECK_EQ(fuse.is_blown(), false);

            fuse = false;
            CHECK_EQ(fuse, false);

            fuse = true;
            CHECK_EQ(fuse, false);

            CHECK_EQ(fuse.is_blown(), true);
        }
    }
}
