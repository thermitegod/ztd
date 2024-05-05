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

#include "ztd/detail/sys/passwd.hxx"

// enable non portable tests
// #define NON_PORTABLE_TESTS

TEST(passwd, constructor_name_throw)
{
#if defined(NON_PORTABLE_TESTS)
    const auto pw = ztd::passwd("brandon");

    EXPECT_EQ(pw.name(), "brandon");
    EXPECT_EQ(pw.password(), "x");
    EXPECT_EQ(pw.uid(), 1000);
    EXPECT_EQ(pw.gid(), 1000);
    EXPECT_EQ(pw.gecos(), "");
    EXPECT_EQ(pw.home(), "/home/brandon");
    EXPECT_EQ(pw.shell(), "/bin/fish");
#endif
}

TEST(passwd, constructor_name_throw__bad_group)
{
    EXPECT_ANY_THROW(ztd::passwd("xxx"));
}

TEST(passwd, constructor_name_ec__bad_group)
{
    std::error_code ec;
    ztd::passwd("xxx", ec);
    EXPECT_TRUE(ec);
}

TEST(passwd, constructor_name_ec)
{
#if defined(NON_PORTABLE_TESTS)
    std::error_code ec;
    const auto pw = ztd::passwd("brandon", ec);
    EXPECT_FALSE(ec);

    EXPECT_EQ(pw.name(), "brandon");
    EXPECT_EQ(pw.password(), "x");
    EXPECT_EQ(pw.uid(), 1000);
    EXPECT_EQ(pw.gid(), 1000);
    EXPECT_EQ(pw.gecos(), "");
    EXPECT_EQ(pw.home(), "/home/brandon");
    EXPECT_EQ(pw.shell(), "/bin/fish");
#endif
}

TEST(passwd, constructor_uid_throw)
{
#if defined(NON_PORTABLE_TESTS)
    const auto pw = ztd::passwd("brandon");

    EXPECT_EQ(pw.name(), "brandon");
    EXPECT_EQ(pw.password(), "x");
    EXPECT_EQ(pw.uid(), 1000);
    EXPECT_EQ(pw.gid(), 1000);
    EXPECT_EQ(pw.gecos(), "");
    EXPECT_EQ(pw.home(), "/home/brandon");
    EXPECT_EQ(pw.shell(), "/bin/fish");
#endif
}

TEST(passwd, constructor_uid_throw__bad_group)
{
    EXPECT_ANY_THROW(ztd::passwd(500000));
}

TEST(passwd, constructor_uid_ec__bad_group)
{
    std::error_code ec;
    ztd::passwd(500000, ec);
    EXPECT_TRUE(ec);
}

TEST(passwd, constructor_uid_ec)
{
#if defined(NON_PORTABLE_TESTS)
    std::error_code ec;
    const auto pw = ztd::passwd("brandon", ec);
    EXPECT_FALSE(ec);

    EXPECT_EQ(pw.name(), "brandon");
    EXPECT_EQ(pw.password(), "x");
    EXPECT_EQ(pw.uid(), 1000);
    EXPECT_EQ(pw.gid(), 1000);
    EXPECT_EQ(pw.gecos(), "");
    EXPECT_EQ(pw.home(), "/home/brandon");
    EXPECT_EQ(pw.shell(), "/bin/fish");
#endif
}
