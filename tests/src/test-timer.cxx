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
#include <vector>

#include <chrono>
#include <thread>

#include "../../src/ztd.hxx"

// Extra timer tests that involve lots of waiting
// #define ZTD_EXTRA_TIMER_TESTS

TEST(timer, timer)
{
    ztd::timer timer = ztd::timer();
    ASSERT_TRUE(!timer.is_stopped());

    timer.stop();
    ASSERT_TRUE(timer.is_stopped());

    timer.start();
    ASSERT_TRUE(!timer.is_stopped());

#ifdef ZTD_EXTRA_TIMER_TESTS
    // now it is time for lots of waiting

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 1.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 2.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 3.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 4.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 5.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 6.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 7.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 8.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 9.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE(timer.elapsed() >= 10.0);

    timer.reset();
    // cannot guarantee that timer will be exactly 0.0 here,
    // so add a little extra time for margin of error
    ASSERT_TRUE(timer.elapsed() <= 0.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    ASSERT_TRUE((timer.elapsed() >= 10.0 && timer.elapsed() <= 10.1));

    timer.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_TRUE((timer.elapsed() >= 10.0 && timer.elapsed() <= 10.1));
#endif
}
