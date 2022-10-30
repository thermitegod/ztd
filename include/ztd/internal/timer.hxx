/**
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
    class timer
    {
      public:
        timer() noexcept;

        /**
         * @brief Start
         *
         * - Start the timer, if timer is already running do nothing.
         */
        void start() noexcept;

        /**
         * @brief Stop
         *
         * - Stop a running timer, if timer is not running do nothing.
         */
        void stop() noexcept;

        /**
         * @brief Reset
         *
         * - Reset the timer
         */
        void reset() noexcept;

        /**
         * @brief Elapsed
         *
         * - Get the total elapsed time
         *
         * @return the total elapsed time
         */
        f64 elapsed() noexcept;

        /**
         * @brief Is Stopped
         *
         * - Is the timer stoped
         *
         * @return true if the timer is stopped otherwise false
         */
        bool is_stopped() noexcept;

      private:
        f64 get_timer_diff();

      private:
        std::chrono::system_clock::time_point internal_timer;
        f64 timer_total{0.0};
        bool stopped{true};
    };
} // namespace ztd