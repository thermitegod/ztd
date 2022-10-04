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

#include <string_view>

#include <sys/stat.h>

#include "ztd/internal/sys/utime.hxx"

bool
ztd::utime(std::string_view filename) noexcept
{
    return (::utimensat(0, filename.data(), nullptr, 0) == 0);
}

bool
ztd::utime(std::string_view filename, time_t atime, time_t mtime, int flags) noexcept
{
    struct timespec tspec[2];

    tspec[0].tv_sec = atime;
    tspec[0].tv_nsec = atime;

    tspec[1].tv_sec = mtime;
    tspec[1].tv_nsec = mtime;

    return (::utimensat(0, filename.data(), tspec, flags) == 0);
}

bool
ztd::utime(std::string_view filename, struct timespec atime, struct timespec mtime, int flags) noexcept
{
    struct timespec tspec[2];

    tspec[0] = atime;
    tspec[1] = mtime;

    return (::utimensat(0, filename.data(), tspec, flags) == 0);
}
