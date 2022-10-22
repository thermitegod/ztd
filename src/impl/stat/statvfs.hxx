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

#ifndef ZTD_STAT_HEADER
#error "Only <ztd-stat.hxx> can be included directly"
#endif

#pragma once

#include <string_view>

#include <chrono>

#include <sys/types.h>
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
        statvfs() noexcept
        {
        }

        statvfs(std::string_view path) noexcept
        {
            this->valid = (::statvfs(path.data(), &this->fs_stat) == 0);

            this->populate();
        }

        statvfs(int fd) noexcept
        {
            this->valid = (::fstatvfs(fd, &this->fs_stat) == 0);

            this->populate();
        }

        bool
        is_valid() const noexcept
        {
            return this->valid;
        }

      private:
        void
        populate()
        {
            this->bsize = this->fs_stat.f_bsize;
            this->frsize = this->fs_stat.f_frsize;
            this->blocks = this->fs_stat.f_blocks;
            this->bfree = this->fs_stat.f_bfree;
            this->bavail = this->fs_stat.f_bavail;
            this->files = this->fs_stat.f_files;
            this->ffree = this->fs_stat.f_ffree;
            this->favail = this->fs_stat.f_favail;
            this->fsid = this->fs_stat.f_fsid;
            this->flag = this->fs_stat.f_flag;
            this->namemax = this->fs_stat.f_namemax;
        }

      public:
        u64 bsize;         // Filesystem block size
        u64 frsize;        // Fragment size
        fsblkcnt_t blocks; // Size of fs in f_frsize units
        fsblkcnt_t bfree;  // Number of free blocks
        fsblkcnt_t bavail; // Number of free blocks for unprivileged users
        fsfilcnt_t files;  // Number of inodes
        fsfilcnt_t ffree;  // Number of free inodes
        fsfilcnt_t favail; // Number of free inodes for unprivileged users
        u64 fsid;          // Filesystem ID
        u64 flag;          // Mount flags
        u64 namemax;       // Maximum filename length

      private:
        struct ::statvfs fs_stat;

        bool valid{false};
    };
} // namespace ztd
