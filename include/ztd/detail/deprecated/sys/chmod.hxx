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

#include <filesystem>

#include <sys/stat.h>

namespace ztd
{
[[nodiscard]] inline bool
chmod(const std::filesystem::path& pathname, mode_t mode) noexcept
{
    return (::chmod(pathname.c_str(), mode) == 0);
}

[[nodiscard]] inline bool
chmod(int fd, mode_t mode) noexcept
{
    return (::fchmod(fd, mode) == 0);
}
} // namespace ztd
