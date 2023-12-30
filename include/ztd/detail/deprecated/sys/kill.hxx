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

#include <span>

#include <algorithm>

#include <csignal>
#include <sys/types.h>

#include <sys/types.h>

namespace ztd
{
inline void
kill(pid_t pid, int signal) noexcept
{
    ::kill(pid, signal);
}

inline void
kill(const std::span<const pid_t>& pids, int signal) noexcept
{
    const auto action = [signal](pid_t pid) { ztd::kill(pid, signal); };
    std::ranges::for_each(pids, action);
}
} // namespace ztd
