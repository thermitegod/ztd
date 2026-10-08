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

TEST_SUITE("ztd::fuse")
{
    TEST_CASE("fuse default init")
    {
        ztd::fuse fuse;
        REQUIRE_FALSE(fuse);
    }

    TEST_CASE("fuse init true")
    {
        ztd::fuse fuse = true;
        REQUIRE(fuse);

        SUBCASE("set true")
        {
            CHECK_FALSE(fuse.is_blown());

            fuse = true;
            CHECK(fuse);

            fuse = false;
            CHECK(fuse);

            CHECK(fuse.is_blown());
        }

        SUBCASE("set false")
        {
            CHECK_FALSE(fuse.is_blown());

            fuse = false;
            CHECK_FALSE(fuse);

            fuse = true;
            CHECK_FALSE(fuse);

            CHECK(fuse.is_blown());
        }
    }

    TEST_CASE("fuse init false")
    {
        ztd::fuse fuse = false;
        REQUIRE_FALSE(fuse);

        SUBCASE("set true")
        {
            CHECK_FALSE(fuse.is_blown());

            fuse = true;
            CHECK(fuse);

            fuse = false;
            CHECK(fuse);

            CHECK(fuse.is_blown());
        }

        SUBCASE("set false")
        {
            CHECK_FALSE(fuse.is_blown());

            fuse = false;
            CHECK_FALSE(fuse);

            fuse = true;
            CHECK_FALSE(fuse);

            CHECK(fuse.is_blown());
        }
    }
}
