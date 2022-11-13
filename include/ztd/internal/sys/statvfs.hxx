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

#pragma once

#include <string_view>

#include <sys/statvfs.h>
// #include <errno.h>

#include "../types.hxx"

// only need to support statvfs(), statfs() and fstatfs() are deprecated
// https://man7.org/linux/man-pages/man2/statfs.2.html

namespace ztd
{
    class statvfs
    {
      public:
        statvfs() = default;
        statvfs(std::string_view path) noexcept;
        statvfs(int fd) noexcept;

        bool is_valid() const noexcept;

      private:
        void populate() noexcept;

      public:
        u64 bsize{0};         // Filesystem block size
        u64 frsize{0};        // Fragment size
        fsblkcnt_t blocks{0}; // Size of fs in f_frsize units
        fsblkcnt_t bfree{0};  // Number of free blocks
        fsblkcnt_t bavail{0}; // Number of free blocks for unprivileged users
        fsfilcnt_t files{0};  // Number of inodes
        fsfilcnt_t ffree{0};  // Number of free inodes
        fsfilcnt_t favail{0}; // Number of free inodes for unprivileged users
        u64 fsid{0};          // Filesystem ID
        u64 flag{0};          // Mount flags
        u64 namemax{0};       // Maximum filename length

      private:
        struct ::statvfs fs_stat = {};

        bool valid{false};
    };
} // namespace ztd
