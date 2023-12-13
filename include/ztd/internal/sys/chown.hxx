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

#include <filesystem>

#include <unistd.h>

namespace ztd
{
[[nodiscard]] inline bool
chown(const std::filesystem::path& pathname, uid_t owner, gid_t group) noexcept
{
    return (::chown(pathname.c_str(), owner, group) == 0);
}

[[nodiscard]] inline bool
chown(int fd, uid_t owner, gid_t group) noexcept
{
    return (::fchown(fd, owner, group) == 0);
}
} // namespace ztd
