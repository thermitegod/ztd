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

#if (ZTD_VERSION == 1)
#include "types.hxx"
#endif

namespace ztd
{
#if (ZTD_VERSION == 1)

struct timer
{
  public:
    /**
     * @brief Start
     *
     * - Start the timer, if timer is already running do nothing.
     */
    void
    start() noexcept
    {
        if (!this->stopped_)
        {
            return;
        }
        this->stopped_ = false;

        this->internal_timer_ = std::chrono::steady_clock::now();
    }

    /**
     * @brief Stop
     *
     * - Stop a running timer, if timer is not running do nothing.
     */
    void
    stop() noexcept
    {
        if (this->stopped_)
        {
            return;
        }
        this->stopped_ = true;

        this->timer_total_ = this->get_timer_diff();
    }

    /**
     * @brief Reset
     *
     * - Reset the timer
     */
    void
    reset() noexcept
    {
        this->stop();
        this->timer_total_ = 0.0;
        this->start();
    }

    /**
     * @brief Elapsed
     *
     * - Get the total elapsed time
     *
     * @return the total elapsed time
     */
    [[nodiscard]] f64
    elapsed() const noexcept
    {
        if (this->stopped_)
        {
            return this->timer_total_;
        }

        return this->get_timer_diff();
    }

    /**
     * @brief Is Stopped
     *
     * - Is the timer stoped
     *
     * @return true if the timer is stopped otherwise false
     */
    [[nodiscard]] bool
    is_stopped() const noexcept
    {
        return this->stopped_;
    }

  private:
    [[nodiscard]] f64
    get_timer_diff() const noexcept
    {
        const auto now = std::chrono::steady_clock::now();
        const std::chrono::duration<f64, std::milli> milliseconds = now - this->internal_timer_;
        return this->timer_total_ + (milliseconds / std::chrono::milliseconds(1000));
    }

  private:
    std::chrono::steady_clock::time_point internal_timer_{std::chrono::steady_clock::now()};
    f64 timer_total_{0.0};
    bool stopped_{false};
};

#else

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
#endif
} // namespace ztd
