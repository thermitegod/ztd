/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
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

#include "ztd/ztd.hxx"

/**
 * ztd::fuse
 */

TEST(type_fuse, fuse__init_default)
{
    ztd::fuse fuse;
    EXPECT_FALSE(fuse);
}

TEST(type_fuse, fuse__init_true)
{
    ztd::fuse fuse = true;
    EXPECT_TRUE(fuse);
}

TEST(type_fuse, fuse__init_false)
{
    ztd::fuse fuse = false;
    EXPECT_FALSE(fuse);
}

TEST(type_fuse, fuse__init_false__set_true)
{
    ztd::fuse fuse = false;
    EXPECT_FALSE(fuse);

    fuse = true;
    EXPECT_TRUE(fuse);

    fuse = false;
    EXPECT_TRUE(fuse);
}

TEST(type_fuse, fuse__init_true__set_false)
{
    ztd::fuse fuse = true;
    EXPECT_TRUE(fuse);

    fuse = false;
    EXPECT_FALSE(fuse);

    fuse = true;
    EXPECT_FALSE(fuse);
}

TEST(type_fuse, fuse__init_true__set_true)
{
    ztd::fuse fuse = true;
    EXPECT_TRUE(fuse);

    fuse = true;
    EXPECT_TRUE(fuse);

    fuse = false;
    EXPECT_TRUE(fuse);
}

TEST(type_fuse, fuse__init_false__set_false)
{
    ztd::fuse fuse = false;
    EXPECT_FALSE(fuse);

    fuse = false;
    EXPECT_FALSE(fuse);

    fuse = true;
    EXPECT_FALSE(fuse);
}
