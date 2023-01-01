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

#include <string>
#include <string_view>

#include <chrono>

#include <sys/stat.h>
#include <fcntl.h>

#include "ztd/ztd.hxx"

// #define STAT_TESTS

#if defined(STAT_TESTS)

constexpr std::string_view stat_file = "/home/brandon/projects/ztd/LICENSE";

TEST(stat_stat, constructor__stat)
{
    ztd::stat file_stat = ztd::stat(stat_file);

    EXPECT_TRUE(file_stat.is_valid());
}

TEST(stat_stat, constructor__fstat)
{
    int fd = open(stat_file.data(), O_RDONLY);

    ztd::stat file_stat = ztd::stat(fd);

    close(fd);

    EXPECT_TRUE(file_stat.is_valid());
}

TEST(stat_stat, constructor__fstatat)
{
    int fd = open(stat_file.data(), O_RDONLY);

    ztd::stat file_stat = ztd::stat(fd);

    close(fd);

    EXPECT_TRUE(file_stat.is_valid());
}

#endif
