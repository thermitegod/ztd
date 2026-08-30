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

#pragma once

#include <chrono>

namespace ztd
{
template<typename P = std::chrono::milliseconds> class timer final
{
  public:
    static_assert(std::same_as<P, std::chrono::seconds> ||
                  std::same_as<P, std::chrono::milliseconds> ||
                  std::same_as<P, std::chrono::microseconds> ||
                  std::same_as<P, std::chrono::nanoseconds>);

    explicit timer(const bool autostart = true)
    {
        if (autostart)
        {
            is_running_ = true;
            start_timepoint_ = std::chrono::steady_clock::now();
            elapsed_time_ = P::zero();
        }
        else
        {
            is_running_ = false;
            elapsed_time_ = P::zero();
        }
    }

    /**
     * @brief Start
     *
     * - Start the timer, if timer is already running do nothing.
     */
    void
    start() noexcept
    {
        if (!is_running_)
        {
            start_timepoint_ = std::chrono::steady_clock::now();
            is_running_ = true;
        }
    }

    /**
     * @brief Stop
     *
     * - Stop a running timer, if timer is not running do nothing.
     */
    void
    stop() noexcept
    {
        if (is_running_)
        {
            const auto end_timepoint = std::chrono::steady_clock::now();
            elapsed_time_ += std::chrono::duration_cast<P>(end_timepoint - start_timepoint_);
            is_running_ = false;
        }
    }

    /**
     * @brief Reset
     *
     * - Reset elapsed time to zero and restart the timer
     */
    void
    reset() noexcept
    {
        stop();
        elapsed_time_ = P::zero();
        start();
    }

    /**
     * @brief Elapsed
     *
     * - Get the total elapsed time in seconds
     *
     * @return the total elapsed time in seconds
     */
    template<typename T = std::chrono::seconds>
    [[nodiscard]] T
    elapsed() const noexcept
    {
        auto total_time = elapsed_time_;
        if (is_running_)
        {
            total_time +=
                std::chrono::duration_cast<P>(std::chrono::steady_clock::now() - start_timepoint_);
        }
        return std::chrono::duration_cast<T>(total_time);
    }

    /**
     * @brief Is Running
     *
     * - Is the timer running
     *
     * @return true if the timer is running otherwise false
     */
    [[nodiscard]] bool
    is_running() const noexcept
    {
        return is_running_;
    }

    /**
     * @brief Is Stopped
     *
     * - Is the timer stopped
     *
     * @return true if the timer is stopped otherwise false
     */
    [[nodiscard]] bool
    is_stopped() const noexcept
    {
        return !is_running_;
    }

  private:
    bool is_running_;
    std::chrono::steady_clock::time_point start_timepoint_;
    P elapsed_time_;
};
} // namespace ztd
