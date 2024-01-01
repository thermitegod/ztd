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

#if (ZTD_VERSION == 1)

#include <gtest/gtest.h>

#include <string>
#include <filesystem>

#include "ztd/ztd.hxx"

#define TEST_SUITE_NAME "test_suite"

TEST(program, exe)
{
    const std::string path = ztd::program::exe();

    EXPECT_TRUE(std::filesystem::exists(path));
}

TEST(program, name)
{
    const std::string name = ztd::program::name();

    EXPECT_EQ(name, TEST_SUITE_NAME);
}

#endif
