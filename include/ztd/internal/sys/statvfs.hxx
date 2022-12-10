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

        [[nodiscard]] bool is_valid() const noexcept;

        [[nodiscard]] u64 bsize() const noexcept;         // Filesystem block size
        [[nodiscard]] u64 frsize() const noexcept;        // Fragment size
        [[nodiscard]] fsblkcnt_t blocks() const noexcept; // Size of fs in f_frsize units
        [[nodiscard]] fsblkcnt_t bfree() const noexcept;  // Number of free blocks
        [[nodiscard]] fsblkcnt_t bavail() const noexcept; // Number of free blocks for unprivileged users
        [[nodiscard]] fsfilcnt_t files() const noexcept;  // Number of inodes
        [[nodiscard]] fsfilcnt_t ffree() const noexcept;  // Number of free inodes
        [[nodiscard]] fsfilcnt_t favail() const noexcept; // Number of free inodes for unprivileged users
        [[nodiscard]] u64 fsid() const noexcept;          // Filesystem ID
        [[nodiscard]] u64 flag() const noexcept;          // Mount flags
        [[nodiscard]] u64 namemax() const noexcept;       // Maximum filename length

      private:
        struct ::statvfs fs_stat = {};

        bool valid{false};
    };
} // namespace ztd
