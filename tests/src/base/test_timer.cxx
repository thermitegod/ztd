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

#include <doctest/doctest.h>

#include <chrono>
#include <thread>

#include "ztd/detail/timer.hxx"

// Extra timer tests that involve lots of waiting
// #define ZTD_EXTRA_TIMER_TESTS

TEST_SUITE("ztd::timer" * doctest::description(""))
{
    TEST_CASE("default init autostart")
    {
        ztd::timer timer;
        CHECK_EQ(timer.is_stopped(), false);
        CHECK_EQ(timer.is_running(), true);

        timer.stop();
        CHECK_EQ(timer.is_stopped(), true);
        CHECK_EQ(timer.is_running(), false);

        timer.start();
        CHECK_EQ(timer.is_stopped(), false);
        CHECK_EQ(timer.is_running(), true);
    }

    TEST_CASE("init autostart true")
    {
        ztd::timer timer = ztd::timer(true);
        CHECK_EQ(timer.is_stopped(), false);
        CHECK_EQ(timer.is_running(), true);
    }

    TEST_CASE("init autostart false")
    {
        ztd::timer timer = ztd::timer(false);
        CHECK_EQ(timer.is_stopped(), true);
        CHECK_EQ(timer.is_running(), false);
    }

    TEST_CASE("elapsed")
    {
        ztd::timer timer = ztd::timer(false);
        CHECK_EQ(timer.elapsed(), std::chrono::seconds::zero());
        CHECK_EQ(timer.elapsed<std::chrono::milliseconds>(), std::chrono::milliseconds::zero());
    }

#if defined(ZTD_EXTRA_TIMER_TESTS)

    TEST_CASE("extra: wait 10 seconds")
    {
        using namespace std::chrono_literals;

        // now it is time for lots of waiting
        ztd::timer timer;
        std::chrono::seconds elapsed_s;
        std::chrono::milliseconds elapsed_ms;

        // cannot guarantee that timer will be exactly 0s here,
        // so add a little extra time for margin of error

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 1s && elapsed_s <= 1.1s), true);
        CHECK_EQ((elapsed_ms >= 1000ms && elapsed_ms <= 1100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 2s && elapsed_s <= 2.1s), true);
        CHECK_EQ((elapsed_ms >= 2000ms && elapsed_ms <= 2100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 3s && elapsed_s <= 3.1s), true);
        CHECK_EQ((elapsed_ms >= 3000ms && elapsed_ms <= 3100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 4s && elapsed_s <= 4.1s), true);
        CHECK_EQ((elapsed_ms >= 4000ms && elapsed_ms <= 4100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 5s && elapsed_s <= 5.1s), true);
        CHECK_EQ((elapsed_ms >= 5000ms && elapsed_ms <= 5100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 6s && elapsed_s <= 6.1s), true);
        CHECK_EQ((elapsed_ms >= 6000ms && elapsed_ms <= 6100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 7s && elapsed_s <= 7.1s), true);
        CHECK_EQ((elapsed_ms >= 7000ms && elapsed_ms <= 7100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 8s && elapsed_s <= 8.1s), true);
        CHECK_EQ((elapsed_ms >= 8000ms && elapsed_ms <= 8100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 9s && elapsed_s <= 9.1s), true);
        CHECK_EQ((elapsed_ms >= 9000ms && elapsed_ms <= 9100ms), true);

        std::this_thread::sleep_for(1s);
        elapsed_s = timer.elapsed();
        elapsed_ms = timer.elapsed<std::chrono::milliseconds>();
        CHECK_EQ((elapsed_s >= 10s && elapsed_s <= 10.1s), true);
        CHECK_EQ((elapsed_ms >= 10000ms && elapsed_ms <= 11000ms), true);
    }

    TEST_CASE("extra: check stopped")
    {
        using namespace std::chrono_literals;

        ztd::timer timer;

        // cannot guarantee that timer will be exactly 0s here,
        // so add a little extra time for margin of error

        std::this_thread::sleep_for(5s);
        CHECK_EQ((timer.elapsed() >= 5000ms && timer.elapsed() <= 5100ms), true);

        timer.stop();
        const auto elapsed = timer.elapsed();
        std::this_thread::sleep_for(5s);

        // check that the timer did not increment while stopped
        CHECK_EQ(timer.elapsed(), elapsed);
    }

    TEST_CASE("extra: check reset")
    {
        using namespace std::chrono_literals;

        ztd::timer timer;

        // cannot guarantee that timer will be exactly 0s here,
        // so add a little extra time for margin of error

        std::this_thread::sleep_for(5s);
        CHECK_EQ((timer.elapsed() >= 5000ms && timer.elapsed() <= 5100ms), true);

        timer.reset();
        const auto elapsed = timer.elapsed();
        CHECK_EQ((elapsed >= 0ms && elapsed <= 100ms), true);
    }

#endif
}
