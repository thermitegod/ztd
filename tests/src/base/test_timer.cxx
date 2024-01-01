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

#include <chrono>
#include <thread>

#include "ztd/ztd.hxx"

// Extra timer tests that involve lots of waiting
// #define ZTD_EXTRA_TIMER_TESTS

#if (ZTD_VERSION == 1)

TEST(timer, timer)
{
    ztd::timer timer = ztd::timer();
    EXPECT_FALSE(timer.is_stopped());

    timer.stop();
    EXPECT_TRUE(timer.is_stopped());

    timer.start();
    EXPECT_FALSE(timer.is_stopped());
}

#else

TEST(timer, timer_autostart_default)
{
    ztd::timer timer;
    EXPECT_FALSE(timer.is_stopped());
    EXPECT_TRUE(timer.is_running());

    timer.stop();
    EXPECT_TRUE(timer.is_stopped());
    EXPECT_FALSE(timer.is_running());

    timer.start();
    EXPECT_FALSE(timer.is_stopped());
    EXPECT_TRUE(timer.is_running());
}

TEST(timer, timer_autostart_true)
{
    ztd::timer timer = ztd::timer(true);
    EXPECT_FALSE(timer.is_stopped());
    EXPECT_TRUE(timer.is_running());
}

TEST(timer, timer_autostart_false)
{
    ztd::timer timer = ztd::timer(false);
    EXPECT_TRUE(timer.is_stopped());
    EXPECT_FALSE(timer.is_running());
}

TEST(timer, elapsed)
{
    ztd::timer timer = ztd::timer(false);
    EXPECT_EQ(timer.elapsed(), std::chrono::seconds::zero());
}

#endif

#if defined(ZTD_EXTRA_TIMER_TESTS)

#if (ZTD_VERSION == 1)

TEST(timer, timer_extra__wait_10_sec_checking)
{
    // now it is time for lots of waiting
    auto timer = ztd::timer();
    f64 elapsed;

    // cannot guarantee that timer will be exactly 0.0 here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 1.0 && elapsed <= 1.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 2.0 && elapsed <= 2.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 3.0 && elapsed <= 3.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 4.0 && elapsed <= 4.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 5.0 && elapsed <= 5.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 6.0 && elapsed <= 6.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 7.0 && elapsed <= 7.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 8.0 && elapsed <= 8.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 9.0 && elapsed <= 9.1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 10.0 && elapsed <= 10.1);
}

TEST(timer, timer_extra__check_stopped)
{
    auto timer = ztd::timer();

    // cannot guarantee that timer will be exactly 0.0 here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    EXPECT_TRUE(timer.elapsed() >= 5.0 && timer.elapsed() <= 5.1);

    timer.stop();
    const auto elapsed = timer.elapsed();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // check that the timer did not increment while stopped
    EXPECT_TRUE(timer.elapsed() == elapsed);
}

TEST(timer, timer_extra__check_reset)
{
    auto timer = ztd::timer();

    // cannot guarantee that timer will be exactly 0.0 here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    EXPECT_TRUE(timer.elapsed() >= 5.0 && timer.elapsed() <= 5.1);

    timer.reset();
    const auto elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 0.0 && elapsed <= 0.1);
}

#else

TEST(timer, timer_extra__wait_10_sec_checking)
{
    using namespace std::chrono_literals;

    // now it is time for lots of waiting
    ztd::timer timer;
    std::chrono::seconds elapsed;

    // cannot guarantee that timer will be exactly 0s here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 1000ms && elapsed <= 1100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 2000ms && elapsed <= 2100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 3000ms && elapsed <= 3100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 4000ms && elapsed <= 4100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 5000ms && elapsed <= 5100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 6000ms && elapsed <= 6100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 7000ms && elapsed <= 7100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 8000ms && elapsed <= 8100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 9000ms && elapsed <= 9100ms);

    std::this_thread::sleep_for(1s);
    elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 10000ms && elapsed <= 11000ms);
}

TEST(timer, timer_extra__check_stopped)
{
    using namespace std::chrono_literals;

    ztd::timer timer;

    // cannot guarantee that timer will be exactly 0s here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(5s);
    EXPECT_TRUE(timer.elapsed() >= 5000ms && timer.elapsed() <= 5100ms);

    timer.stop();
    const auto elapsed = timer.elapsed();
    std::this_thread::sleep_for(5s);

    // check that the timer did not increment while stopped
    EXPECT_TRUE(timer.elapsed() == elapsed);
}

TEST(timer, timer_extra__check_reset)
{
    using namespace std::chrono_literals;

    ztd::timer timer;

    // cannot guarantee that timer will be exactly 0s here,
    // so add a little extra time for margin of error

    std::this_thread::sleep_for(5s);
    EXPECT_TRUE(timer.elapsed() >= 5000ms && timer.elapsed() <= 5100ms);

    timer.reset();
    const auto elapsed = timer.elapsed();
    EXPECT_TRUE(elapsed >= 0ms && elapsed <= 100ms);
}

#endif

#endif
