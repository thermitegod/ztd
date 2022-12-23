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

    GTEST_ASSERT_EQ(stat.pid(), 2988057);
    GTEST_ASSERT_EQ(stat.name(), "zsh");
    GTEST_ASSERT_EQ(stat.state(), "S");
    GTEST_ASSERT_EQ(stat.ppid(), 4020);
    GTEST_ASSERT_EQ(stat.pgrp(), 2988057);
    GTEST_ASSERT_EQ(stat.session(), 2988057);
    GTEST_ASSERT_EQ(stat.tpgid(), 3769860);
    GTEST_ASSERT_EQ(stat.minflt(), 185750);
    GTEST_ASSERT_EQ(stat.cminflt(), 431319);
    GTEST_ASSERT_EQ(stat.majflt(), 0);
    GTEST_ASSERT_EQ(stat.cmajflt(), 1424);
    GTEST_ASSERT_EQ(stat.utime(), 319);
    GTEST_ASSERT_EQ(stat.stime(), 97);
    GTEST_ASSERT_EQ(stat.cutime(), 993);
    GTEST_ASSERT_EQ(stat.cstime(), 219);
    GTEST_ASSERT_EQ(stat.priority(), 20);
    GTEST_ASSERT_EQ(stat.nice(), 0);
    GTEST_ASSERT_EQ(stat.num_threads(), 1);
    GTEST_ASSERT_EQ(stat.starttime(), 19658911);
    GTEST_ASSERT_EQ(stat.vsize(), 13017088);
    GTEST_ASSERT_EQ(stat.rss(), 1921);
    GTEST_ASSERT_EQ(stat.exit_signal(), 17);
    GTEST_ASSERT_EQ(stat.processor(), 6);
    GTEST_ASSERT_EQ(stat.exit_code(), 0);

    // State
    GTEST_ASSERT_FALSE(stat.is_running());
    GTEST_ASSERT_TRUE(stat.is_sleeping());
    GTEST_ASSERT_FALSE(stat.is_waiting());
    GTEST_ASSERT_FALSE(stat.is_zombie());
    GTEST_ASSERT_FALSE(stat.is_stopped());
    GTEST_ASSERT_FALSE(stat.is_trace_sropped());
    GTEST_ASSERT_FALSE(stat.is_dead());
    GTEST_ASSERT_FALSE(stat.is_idle());

    // Execution Time
    GTEST_ASSERT_EQ(stat.etime(), 4.16);
}

/**
 * stat-02
 */

TEST(linux_proc_stat, stat_02)
{
    const auto stat = ztd::proc::stat(get_test_data_path("data/linux/proc/stat-02"));

    GTEST_ASSERT_EQ(stat.pid(), 64342);
    GTEST_ASSERT_EQ(stat.name(), "lldb");
    GTEST_ASSERT_EQ(stat.state(), "S");
    GTEST_ASSERT_EQ(stat.ppid(), 4333);
    GTEST_ASSERT_EQ(stat.pgrp(), 64342);
    GTEST_ASSERT_EQ(stat.session(), 4333);
    GTEST_ASSERT_EQ(stat.tpgid(), 64342);
    GTEST_ASSERT_EQ(stat.minflt(), 58077);
    GTEST_ASSERT_EQ(stat.cminflt(), 1374);
    GTEST_ASSERT_EQ(stat.majflt(), 739);
    GTEST_ASSERT_EQ(stat.cmajflt(), 0);
    GTEST_ASSERT_EQ(stat.utime(), 325);
    GTEST_ASSERT_EQ(stat.stime(), 217);
    GTEST_ASSERT_EQ(stat.cutime(), 0);
    GTEST_ASSERT_EQ(stat.cstime(), 0);
    GTEST_ASSERT_EQ(stat.priority(), 20);
    GTEST_ASSERT_EQ(stat.nice(), 0);
    GTEST_ASSERT_EQ(stat.num_threads(), 38);
    GTEST_ASSERT_EQ(stat.starttime(), 27987997);
    GTEST_ASSERT_EQ(stat.vsize(), 3252342784);
    GTEST_ASSERT_EQ(stat.rss(), 65699);
    GTEST_ASSERT_EQ(stat.exit_signal(), 17);
    GTEST_ASSERT_EQ(stat.processor(), 27);
    GTEST_ASSERT_EQ(stat.exit_code(), 0);

    // State
    GTEST_ASSERT_FALSE(stat.is_running());
    GTEST_ASSERT_TRUE(stat.is_sleeping());
    GTEST_ASSERT_FALSE(stat.is_waiting());
    GTEST_ASSERT_FALSE(stat.is_zombie());
    GTEST_ASSERT_FALSE(stat.is_stopped());
    GTEST_ASSERT_FALSE(stat.is_trace_sropped());
    GTEST_ASSERT_FALSE(stat.is_dead());
    GTEST_ASSERT_FALSE(stat.is_idle());

    // Execution Time
    GTEST_ASSERT_EQ(stat.etime(), 5.42);
}

/**
 * stat-03
 */

TEST(linux_proc_stat, stat_03)
{
    const auto stat = ztd::proc::stat(get_test_data_path("data/linux/proc/stat-03"));

    GTEST_ASSERT_EQ(stat.pid(), 379117);
    GTEST_ASSERT_EQ(stat.name(), "mcomix");
    GTEST_ASSERT_EQ(stat.state(), "S");
    GTEST_ASSERT_EQ(stat.ppid(), 379041);
    GTEST_ASSERT_EQ(stat.pgrp(), 2748977);
    GTEST_ASSERT_EQ(stat.session(), 2748977);
    GTEST_ASSERT_EQ(stat.tpgid(), -1);
    GTEST_ASSERT_EQ(stat.minflt(), 269152);
    GTEST_ASSERT_EQ(stat.cminflt(), 36);
    GTEST_ASSERT_EQ(stat.majflt(), 73);
    GTEST_ASSERT_EQ(stat.cmajflt(), 0);
    GTEST_ASSERT_EQ(stat.utime(), 387);
    GTEST_ASSERT_EQ(stat.stime(), 56);
    GTEST_ASSERT_EQ(stat.cutime(), 0);
    GTEST_ASSERT_EQ(stat.cstime(), 0);
    GTEST_ASSERT_EQ(stat.priority(), 20);
    GTEST_ASSERT_EQ(stat.nice(), 0);
    GTEST_ASSERT_EQ(stat.num_threads(), 23);
    GTEST_ASSERT_EQ(stat.starttime(), 28361289);
    GTEST_ASSERT_EQ(stat.vsize(), 2117390336);
    GTEST_ASSERT_EQ(stat.rss(), 115279);
    GTEST_ASSERT_EQ(stat.exit_signal(), 17);
    GTEST_ASSERT_EQ(stat.processor(), 8);
    GTEST_ASSERT_EQ(stat.exit_code(), 0);

    // State
    GTEST_ASSERT_FALSE(stat.is_running());
    GTEST_ASSERT_TRUE(stat.is_sleeping());
    GTEST_ASSERT_FALSE(stat.is_waiting());
    GTEST_ASSERT_FALSE(stat.is_zombie());
    GTEST_ASSERT_FALSE(stat.is_stopped());
    GTEST_ASSERT_FALSE(stat.is_trace_sropped());
    GTEST_ASSERT_FALSE(stat.is_dead());
    GTEST_ASSERT_FALSE(stat.is_idle());

    // Execution Time
    GTEST_ASSERT_EQ(stat.etime(), 4.43);
}
