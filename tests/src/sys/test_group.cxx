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

#include <gtest/gtest.h>

#include <vector>

#include <system_error>

#include "ztd/detail/sys/group.hxx"

// enable non portable tests
// #define NON_PORTABLE_TESTS

TEST(group, constructor_name_throw)
{
#if defined(NON_PORTABLE_TESTS)
    const auto gr = ztd::group("wheel");

    EXPECT_EQ(gr.name(), "wheel");
    EXPECT_EQ(gr.password(), "x");
    EXPECT_EQ(gr.gid(), 10);
    std::vector<std::string> members{"root", "brandon"};
    EXPECT_EQ(gr.members(), members);
#endif
}

TEST(group, constructor_name_throw__bad_group)
{
    EXPECT_ANY_THROW(ztd::group("xxx"));
}

TEST(group, constructor_name_ec__bad_group)
{
    std::error_code ec;
    ztd::group("xxx", ec);
    EXPECT_TRUE(ec);
}

TEST(group, constructor_name_ec)
{
#if defined(NON_PORTABLE_TESTS)
    std::error_code ec;
    const auto gr = ztd::group("wheel", ec);

    EXPECT_EQ(gr.name(), "wheel");
    EXPECT_EQ(gr.password(), "x");
    EXPECT_EQ(gr.gid(), 10);
    std::vector<std::string> members{"root", "brandon"};
    EXPECT_EQ(gr.members(), members);
#endif
}

TEST(group, constructor_gid_throw)
{
#if defined(NON_PORTABLE_TESTS)
    const auto gr = ztd::group("wheel");

    EXPECT_EQ(gr.name(), "wheel");
    EXPECT_EQ(gr.password(), "x");
    EXPECT_EQ(gr.gid(), 10);
    std::vector<std::string> members{"root", "brandon"};
    EXPECT_EQ(gr.members(), members);
#endif
}

TEST(group, constructor_gid_throw__bad_group)
{
    EXPECT_ANY_THROW(ztd::group(500000));
}

TEST(group, constructor_gid_ec__bad_group)
{
    std::error_code ec;
    ztd::group(500000, ec);
    EXPECT_TRUE(ec);
}

TEST(group, constructor_gid_ec)
{
#if defined(NON_PORTABLE_TESTS)
    std::error_code ec;
    const auto gr = ztd::group("wheel", ec);

    EXPECT_EQ(gr.name(), "wheel");
    EXPECT_EQ(gr.password(), "x");
    EXPECT_EQ(gr.gid(), 10);
    std::vector<std::string> members{"root", "brandon"};
    EXPECT_EQ(gr.members(), members);
#endif
}
