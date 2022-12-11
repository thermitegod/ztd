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

#include <chrono>

#include "ztd/internal/types.hxx"

#include "ztd/internal/timer.hxx"

void
ztd::timer::start() noexcept
{
    if (!this->stopped)
        return;
    this->stopped = false;

    this->internal_timer = std::chrono::system_clock::now();
}

void
ztd::timer::stop() noexcept
{
    if (this->stopped)
        return;
    this->stopped = true;

    this->timer_total = this->get_timer_diff();
}

void
ztd::timer::reset() noexcept
{
    stop();
    this->timer_total = 0.0;
    start();
}

f64
ztd::timer::elapsed() const noexcept
{
    if (this->stopped)
        return this->timer_total;

    return this->get_timer_diff();
}

bool
ztd::timer::is_stopped() const noexcept
{
    return this->stopped;
}

f64
ztd::timer::get_timer_diff() const noexcept
{
    const auto now = std::chrono::system_clock::now();
    const std::chrono::duration<f64, std::milli> msec = now - this->internal_timer;
    return this->timer_total + (msec.count() / 1000);
}
