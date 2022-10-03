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

#ifndef ZTD_MAIN_HEADER
#error "Only <ztd.hxx> can be included directly"
#endif

#pragma once

#include <chrono>

#include "types.hxx"

namespace ztd
{
    class timer
    {
      public:
        timer() noexcept
        {
            this->stopped = false;
            std::time(&this->internal_timer);
        }

        ~timer() noexcept
        {
        }

        /**
         * @brief Start
         *
         * - Start the timer, if timer is already running do nothing.
         */
        void
        start() noexcept
        {
            if (!this->stopped)
                return;
            this->stopped = false;

            std::time(&this->internal_timer);
        }

        /**
         * @brief Stop
         *
         * - Stop a running timer, if timer is not running do nothing.
         */
        void
        stop() noexcept
        {
            if (this->stopped)
                return;
            this->stopped = true;

            std::time_t now;
            std::time(&now);

            const f64 seconds = difftime(now, this->internal_timer);

            this->timer_total = this->timer_total + seconds;
        }

        /**
         * @brief Reset
         *
         * - Reset the timer
         */
        void
        reset() noexcept
        {
            stop();
            this->timer_total = 0.0;
            start();
        }

        /**
         * @brief Elapsed
         *
         * - Get the total elapsed time
         *
         * @return the total elapsed time
         */
        f64
        elapsed() noexcept
        {
            if (this->stopped)
                return this->timer_total;

            std::time_t now;
            std::time(&now);

            const f64 seconds = difftime(now, this->internal_timer);

            return this->timer_total + seconds;
        }

        /**
         * @brief Is Stopped
         *
         * - Is the timer stoped
         *
         * @return true if the timer is stopped otherwise false
         */
        bool
        is_stopped() noexcept
        {
            return this->stopped;
        }

      private:
        std::time_t internal_timer{0};
        f64 timer_total{0.0};
        bool stopped{true};
    };
} // namespace ztd
