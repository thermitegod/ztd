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

#include <array>

#include <sys/stat.h>

#include <sys/stat.h>

namespace ztd
{
[[nodiscard]] inline bool
utime(const std::filesystem::path& filename) noexcept
{
    return (::utimensat(0, filename.c_str(), nullptr, 0) == 0);
}

[[nodiscard]] inline bool
utime(const std::filesystem::path& filename, time_t atime, time_t mtime, int flags) noexcept
{
    std::array<timespec, 2> tspecs{};

    tspecs[0].tv_sec = atime;
    tspecs[0].tv_nsec = 0;

    tspecs[1].tv_sec = mtime;
    tspecs[1].tv_nsec = 0;

    return (::utimensat(0, filename.c_str(), tspecs.data(), flags) == 0);
}

[[nodiscard]] inline bool
utime(const std::filesystem::path& filename, struct timespec atime, struct timespec mtime, int flags) noexcept
{
    const std::array<timespec, 2> tspecs{atime, mtime};

    return (::utimensat(0, filename.c_str(), tspecs.data(), flags) == 0);
}

[[nodiscard]] inline bool
utime(const std::filesystem::path& filename, struct statx_timestamp atime, struct statx_timestamp mtime,
      int flags) noexcept
{
    std::array<timespec, 2> tspecs{};

    tspecs[0].tv_sec = atime.tv_sec;
    tspecs[0].tv_nsec = atime.tv_nsec;

    tspecs[1].tv_sec = mtime.tv_sec;
    tspecs[1].tv_nsec = mtime.tv_nsec;

    return (::utimensat(0, filename.c_str(), tspecs.data(), flags) == 0);
}
} // namespace ztd
