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

#include <string_view>

#include <sys/stat.h>

namespace ztd
{
    bool utime(const std::string_view filename) noexcept;
    bool utime(const std::string_view filename, time_t atime, time_t mtime, int flags = 0) noexcept;
    bool utime(const std::string_view filename, struct timespec atime, struct timespec mtime, int flags = 0) noexcept;
} // namespace ztd
