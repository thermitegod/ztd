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
    ASSERT_FALSE(timer.is_stopped());

    timer.stop();
    ASSERT_TRUE(timer.is_stopped());

    timer.start();
    ASSERT_FALSE(timer.is_stopped());
}

#ifdef ZTD_EXTRA_TIMER_TESTS

TEST(timer, timer_extra__wait_10_sec_checking)
{
    // now it is time for lots of waiting
    ztd::timer timer = ztd::timer();
    f64 elapsed;

    // cannot guarantee that timer will be exactly 0.0 here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 1.0 && elapsed <= 1.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 2.0 && elapsed <= 2.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 3.0 && elapsed <= 3.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 4.0 && elapsed <= 4.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 5.0 && elapsed <= 5.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 6.0 && elapsed <= 6.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 7.0 && elapsed <= 7.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 8.0 && elapsed <= 8.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 9.0 && elapsed <= 9.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 10.0 && elapsed <= 10.1);
}

TEST(timer, timer_extra__check_stopped)
{
    ztd::timer timer = ztd::timer();

    // cannot guarantee that timer will be exactly 0.0 here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ASSERT_TRUE(timer.elapsed() >= 5.0 && timer.elapsed() <= 5.1);

    timer.stop();
    auto elapsed = timer.elapsed();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // check that the timer did not increment while stopped
    ASSERT_TRUE(timer.elapsed() == elapsed);
}

TEST(timer, timer_extra__check_reset)
{
    ztd::timer timer = ztd::timer();

    // cannot guarantee that timer will be exactly 0.0 here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ASSERT_TRUE(timer.elapsed() >= 5.0 && timer.elapsed() <= 5.1);

    timer.reset();
    auto elapsed = timer.elapsed();
    ASSERT_TRUE(elapsed >= 0.0 && elapsed <= 0.1);
}

#endif
