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

#include <unistd.h>

namespace ztd
{
    static inline bool
    chown(std::string_view pathname, uid_t owner, gid_t group)
    {
        return (::chown(pathname.data(), owner, group) == 0);
    }

    static inline bool
    chown(int fd, uid_t owner, gid_t group)
    {
        return (::fchown(fd, owner, group) == 0);
    }
} // namespace ztd
