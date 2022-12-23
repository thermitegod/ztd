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

TEST(linux_proc_statm, statm_01)
{
    const auto statm = ztd::proc::statm(get_test_data_path("data/linux/proc/statm-01"));

    GTEST_ASSERT_EQ(statm.size(), 3178);
    GTEST_ASSERT_EQ(statm.resident(), 1921);
    GTEST_ASSERT_EQ(statm.shared(), 771);
    GTEST_ASSERT_EQ(statm.text(), 175);
    GTEST_ASSERT_EQ(statm.lib(), 0);
    GTEST_ASSERT_EQ(statm.data(), 1182);
    GTEST_ASSERT_EQ(statm.dt(), 0);
}

/**
 * stat-02
 */

TEST(linux_proc_statm, statm_02)
{
    const auto statm = ztd::proc::statm(get_test_data_path("data/linux/proc/statm-02"));

    GTEST_ASSERT_EQ(statm.size(), 794029);
    GTEST_ASSERT_EQ(statm.resident(), 65699);
    GTEST_ASSERT_EQ(statm.shared(), 21640);
    GTEST_ASSERT_EQ(statm.text(), 7);
    GTEST_ASSERT_EQ(statm.lib(), 0);
    GTEST_ASSERT_EQ(statm.data(), 163785);
    GTEST_ASSERT_EQ(statm.dt(), 0);
}

/**
 * stat-03
 */

TEST(linux_proc_statm, statm_03)
{
    const auto statm = ztd::proc::statm(get_test_data_path("data/linux/proc/statm-03"));

    GTEST_ASSERT_EQ(statm.size(), 516941);
    GTEST_ASSERT_EQ(statm.resident(), 115279);
    GTEST_ASSERT_EQ(statm.shared(), 6598);
    GTEST_ASSERT_EQ(statm.text(), 1);
    GTEST_ASSERT_EQ(statm.lib(), 0);
    GTEST_ASSERT_EQ(statm.data(), 236228);
    GTEST_ASSERT_EQ(statm.dt(), 0);
}
