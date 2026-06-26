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

#include <system_error>
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/sys/group.hxx"

// enable non portable tests
// #define NON_PORTABLE_TESTS

TEST_SUITE("ztd::group" * doctest::description(""))
{
    TEST_CASE("constructor name throw")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto gr = ztd::group("wheel");

        CHECK_EQ(gr.name(), "wheel");
        CHECK_EQ(gr.password(), "x");
        CHECK_EQ(gr.gid(), 10);
        std::vector<std::string> members{"root", "brandon"};
        CHECK_EQ(gr.members(), members);
#endif
    }

    TEST_CASE("constructor name throw bad group")
    {
        CHECK_THROWS(ztd::group("xxx"));
    }

    TEST_CASE("constructor name ec bad group")
    {
        std::error_code ec;
        ztd::group("xxx", ec);
        CHECK_EQ(!!ec, true);
    }

    TEST_CASE("constructor name ec")
    {
#if defined(NON_PORTABLE_TESTS)
        std::error_code ec;
        const auto gr = ztd::group("wheel", ec);

        CHECK_EQ(gr.name(), "wheel");
        CHECK_EQ(gr.password(), "x");
        CHECK_EQ(gr.gid(), 10);
        std::vector<std::string> members{"root", "brandon"};
        CHECK_EQ(gr.members(), members);
#endif
    }

    TEST_CASE("constructor gid throw")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto gr = ztd::group("wheel");

        CHECK_EQ(gr.name(), "wheel");
        CHECK_EQ(gr.password(), "x");
        CHECK_EQ(gr.gid(), 10);
        std::vector<std::string> members{"root", "brandon"};
        CHECK_EQ(gr.members(), members);
#endif
    }

    TEST_CASE("constructor gid throw bad group")
    {
        CHECK_THROWS(ztd::group(500000));
    }

    TEST_CASE("constructor gid ec bad group")
    {
        std::error_code ec;
        ztd::group(500000, ec);
        CHECK_EQ(!!ec, true);
    }

    TEST_CASE("constructor gid ec")
    {
#if defined(NON_PORTABLE_TESTS)
        std::error_code ec;
        const auto gr = ztd::group("wheel", ec);

        CHECK_EQ(gr.name(), "wheel");
        CHECK_EQ(gr.password(), "x");
        CHECK_EQ(gr.gid(), 10);
        std::vector<std::string> members{"root", "brandon"};
        CHECK_EQ(gr.members(), members);
#endif
    }
}
