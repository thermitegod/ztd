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

#include "types.hxx"

namespace ztd
{
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
    [[nodiscard]] ztd::f64
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
    [[nodiscard]] ztd::f64
    get_timer_diff() const noexcept
    {
        const auto now = std::chrono::steady_clock::now();
        const std::chrono::duration<f64, std::milli> milliseconds = now - this->internal_timer_;
        return this->timer_total_ + (milliseconds / std::chrono::milliseconds(1000));
    }

  private:
    std::chrono::steady_clock::time_point internal_timer_{std::chrono::steady_clock::now()};
    ztd::f64 timer_total_{0.0};
    bool stopped_{false};
};
} // namespace ztd
