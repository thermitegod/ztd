/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
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

#include <ctime>

namespace ztd
{
    class timer
    {
      public:
        timer() noexcept
        {
            m_timer_total = 0;
            m_stopped = true;

            start();
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
            if (!m_stopped)
                return;
            m_stopped = false;

            std::time(&m_timer);
        }

        /**
         * @brief Stop
         *
         * - Stop a running timer, if timer is not running do nothing.
         */
        void
        stop() noexcept
        {
            if (m_stopped)
                return;
            m_stopped = true;

            std::time_t now;
            double seconds;

            std::time(&now);
            seconds = difftime(now, m_timer);

            m_timer_total = m_timer_total + seconds;
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
            m_timer_total = 0;
            start();
        }

        /**
         * @brief Elapsed
         *
         * - Get the total elapsed time
         *
         * @return the total elapsed time
         */
        double
        elapsed() noexcept
        {
            if (m_stopped)
                return m_timer_total;

            std::time_t now;
            double seconds;

            std::time(&now);
            seconds = difftime(now, m_timer);

            return m_timer_total + seconds;
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
            return m_stopped;
        }

      private:
        std::time_t m_timer;
        double m_timer_total;
        bool m_stopped;
    };
} // namespace ztd
