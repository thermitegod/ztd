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

#ifndef ZTD_SYS_HEADER
#error "Only <ztd-sys.hxx> can be included directly"
#endif

#pragma once

#include <string_view>

#include <sys/stat.h>

namespace ztd
{
    static inline bool
    utime(std::string_view filename)
    {
        return (::utimensat(0, filename.data(), nullptr, 0) == 0);
    }

    static inline bool
    utime(std::string_view filename, time_t atime, time_t mtime, int flags = 0)
    {
        struct timespec tspec[2];

        tspec[0].tv_sec = atime;
        tspec[0].tv_nsec = atime;

        tspec[1].tv_sec = mtime;
        tspec[1].tv_nsec = mtime;

        return (::utimensat(0, filename.data(), tspec, flags) == 0);
    }

    static inline bool
    utime(std::string_view filename, struct timespec atime, struct timespec mtime, int flags = 0)
    {
        struct timespec tspec[2];

        tspec[0] = atime;
        tspec[1] = mtime;

        return (::utimensat(0, filename.data(), tspec, flags) == 0);
    }
} // namespace ztd
