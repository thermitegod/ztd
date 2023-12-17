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

#pragma once

#include <chrono>

namespace ztd
{
struct timer
{
  public:
    timer(const bool autostart = true)
    {
        if (autostart)
        {
            this->is_running_ = true;
            this->start_timepoint_ = std::chrono::steady_clock::now();
            this->elapsed_time_ = std::chrono::milliseconds::zero();
        }
        else
        {
            this->is_running_ = false;
            this->elapsed_time_ = std::chrono::milliseconds::zero();
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
        if (!this->is_running_)
        {
            this->start_timepoint_ = std::chrono::steady_clock::now();
            this->is_running_ = true;
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
        if (this->is_running_)
        {
            auto end_timepoint = std::chrono::steady_clock::now();
            this->elapsed_time_ +=
                std::chrono::duration_cast<std::chrono::milliseconds>(end_timepoint - start_timepoint_);
            this->is_running_ = false;
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
        this->stop();
        this->elapsed_time_ = std::chrono::milliseconds::zero();
        this->start();
    }

    /**
     * @brief Elapsed
     *
     * - Get the total elapsed time in seconds
     *
     * @return the total elapsed time in seconds
     */
    const std::chrono::seconds
    elapsed() const noexcept
    {
        auto total_time = elapsed_time_;
        if (this->is_running_)
        {
            total_time += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() -
                                                                                start_timepoint_);
        }
        return std::chrono::duration_cast<std::chrono::seconds>(total_time);
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
        return this->is_running_;
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
        return !this->is_running_;
    }

  private:
    bool is_running_;
    std::chrono::steady_clock::time_point start_timepoint_;
    std::chrono::milliseconds elapsed_time_;
};
} // namespace ztd
