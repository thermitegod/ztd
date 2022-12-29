/**
 * Copyright (C) 2022 Brandon Zorn <brandonzorn@cock.li>
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

#include <filesystem>

#include "src/utils.hxx"

#include "ztd/ztd.hxx"

/**
 * stat-01
 */

TEST(linux_proc_stat, stat_01)
{
    const auto stat = ztd::proc::stat(get_test_data_path("data/linux/proc/stat-01"));

    EXPECT_EQ(stat.pid(), 2988057);
    EXPECT_EQ(stat.name(), "zsh");
    EXPECT_EQ(stat.state(), "S");
    EXPECT_EQ(stat.ppid(), 4020);
    EXPECT_EQ(stat.pgrp(), 2988057);
    EXPECT_EQ(stat.session(), 2988057);
    EXPECT_EQ(stat.tpgid(), 3769860);
    EXPECT_EQ(stat.minflt(), 185750);
    EXPECT_EQ(stat.cminflt(), 431319);
    EXPECT_EQ(stat.majflt(), 0);
    EXPECT_EQ(stat.cmajflt(), 1424);
    EXPECT_EQ(stat.utime(), 319);
    EXPECT_EQ(stat.stime(), 97);
    EXPECT_EQ(stat.cutime(), 993);
    EXPECT_EQ(stat.cstime(), 219);
    EXPECT_EQ(stat.priority(), 20);
    EXPECT_EQ(stat.nice(), 0);
    EXPECT_EQ(stat.num_threads(), 1);
    EXPECT_EQ(stat.starttime(), 19658911);
    EXPECT_EQ(stat.vsize(), 13017088);
    EXPECT_EQ(stat.rss(), 1921);
    EXPECT_EQ(stat.exit_signal(), 17);
    EXPECT_EQ(stat.processor(), 6);
    EXPECT_EQ(stat.exit_code(), 0);

    // State
    EXPECT_FALSE(stat.is_running());
    EXPECT_TRUE(stat.is_sleeping());
    EXPECT_FALSE(stat.is_waiting());
    EXPECT_FALSE(stat.is_zombie());
    EXPECT_FALSE(stat.is_stopped());
    EXPECT_FALSE(stat.is_trace_sropped());
    EXPECT_FALSE(stat.is_dead());
    EXPECT_FALSE(stat.is_idle());

    // Execution Time
    EXPECT_EQ(stat.etime(), 4.16);
}

/**
 * stat-02
 */

TEST(linux_proc_stat, stat_02)
{
    const auto stat = ztd::proc::stat(get_test_data_path("data/linux/proc/stat-02"));

    EXPECT_EQ(stat.pid(), 64342);
    EXPECT_EQ(stat.name(), "lldb");
    EXPECT_EQ(stat.state(), "S");
    EXPECT_EQ(stat.ppid(), 4333);
    EXPECT_EQ(stat.pgrp(), 64342);
    EXPECT_EQ(stat.session(), 4333);
    EXPECT_EQ(stat.tpgid(), 64342);
    EXPECT_EQ(stat.minflt(), 58077);
    EXPECT_EQ(stat.cminflt(), 1374);
    EXPECT_EQ(stat.majflt(), 739);
    EXPECT_EQ(stat.cmajflt(), 0);
    EXPECT_EQ(stat.utime(), 325);
    EXPECT_EQ(stat.stime(), 217);
    EXPECT_EQ(stat.cutime(), 0);
    EXPECT_EQ(stat.cstime(), 0);
    EXPECT_EQ(stat.priority(), 20);
    EXPECT_EQ(stat.nice(), 0);
    EXPECT_EQ(stat.num_threads(), 38);
    EXPECT_EQ(stat.starttime(), 27987997);
    EXPECT_EQ(stat.vsize(), 3252342784);
    EXPECT_EQ(stat.rss(), 65699);
    EXPECT_EQ(stat.exit_signal(), 17);
    EXPECT_EQ(stat.processor(), 27);
    EXPECT_EQ(stat.exit_code(), 0);

    // State
    EXPECT_FALSE(stat.is_running());
    EXPECT_TRUE(stat.is_sleeping());
    EXPECT_FALSE(stat.is_waiting());
    EXPECT_FALSE(stat.is_zombie());
    EXPECT_FALSE(stat.is_stopped());
    EXPECT_FALSE(stat.is_trace_sropped());
    EXPECT_FALSE(stat.is_dead());
    EXPECT_FALSE(stat.is_idle());

    // Execution Time
    EXPECT_EQ(stat.etime(), 5.42);
}

/**
 * stat-03
 */

TEST(linux_proc_stat, stat_03)
{
    const auto stat = ztd::proc::stat(get_test_data_path("data/linux/proc/stat-03"));

    EXPECT_EQ(stat.pid(), 379117);
    EXPECT_EQ(stat.name(), "mcomix");
    EXPECT_EQ(stat.state(), "S");
    EXPECT_EQ(stat.ppid(), 379041);
    EXPECT_EQ(stat.pgrp(), 2748977);
    EXPECT_EQ(stat.session(), 2748977);
    EXPECT_EQ(stat.tpgid(), -1);
    EXPECT_EQ(stat.minflt(), 269152);
    EXPECT_EQ(stat.cminflt(), 36);
    EXPECT_EQ(stat.majflt(), 73);
    EXPECT_EQ(stat.cmajflt(), 0);
    EXPECT_EQ(stat.utime(), 387);
    EXPECT_EQ(stat.stime(), 56);
    EXPECT_EQ(stat.cutime(), 0);
    EXPECT_EQ(stat.cstime(), 0);
    EXPECT_EQ(stat.priority(), 20);
    EXPECT_EQ(stat.nice(), 0);
    EXPECT_EQ(stat.num_threads(), 23);
    EXPECT_EQ(stat.starttime(), 28361289);
    EXPECT_EQ(stat.vsize(), 2117390336);
    EXPECT_EQ(stat.rss(), 115279);
    EXPECT_EQ(stat.exit_signal(), 17);
    EXPECT_EQ(stat.processor(), 8);
    EXPECT_EQ(stat.exit_code(), 0);

    // State
    EXPECT_FALSE(stat.is_running());
    EXPECT_TRUE(stat.is_sleeping());
    EXPECT_FALSE(stat.is_waiting());
    EXPECT_FALSE(stat.is_zombie());
    EXPECT_FALSE(stat.is_stopped());
    EXPECT_FALSE(stat.is_trace_sropped());
    EXPECT_FALSE(stat.is_dead());
    EXPECT_FALSE(stat.is_idle());

    // Execution Time
    EXPECT_EQ(stat.etime(), 4.43);
}
