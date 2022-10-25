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

#include <chrono>

#include <sys/stat.h>
// #include <errno.h>

#include "../types.hxx"

namespace ztd
{
    class stat
    {
      public:
        stat() noexcept
        {
        }

        stat(std::string_view path) noexcept
        {
            this->valid = (::stat(path.data(), &this->file_stat) == 0);

            this->populate();
        }

        stat(int fd) noexcept
        {
            this->valid = (::fstat(fd, &this->file_stat) == 0);

            this->populate();
        }

        stat(int dirfd, std::string_view pathname, int flags) noexcept
        {
            this->valid = (::fstatat(dirfd, pathname.data(), &this->file_stat, flags) == 0);

            this->populate();
        }

        bool
        is_valid() const noexcept
        {
            return this->valid;
        }

        bool
        is_directory() const noexcept
        {
            return S_ISDIR(this->mode);
        }

        bool
        is_regular_file() const noexcept
        {
            return S_ISREG(this->mode);
        }

        bool
        is_symlink() const noexcept
        {
            return S_ISLNK(this->mode);
        }

        bool
        is_socket() const noexcept
        {
            return S_ISSOCK(this->mode);
        }

        bool
        is_fifo() const noexcept
        {
            return S_ISFIFO(this->mode);
        }

        bool
        is_block_file() const noexcept
        {
            return S_ISBLK(this->mode);
        }

        bool
        is_character_file() const noexcept
        {
            return S_ISCHR(this->mode);
        }

      protected:
        void
        populate()
        {
            this->dev = this->file_stat.st_dev;
            this->ino = this->file_stat.st_ino;
            this->mode = this->file_stat.st_mode;
            this->nlink = this->file_stat.st_nlink;
            this->uid = this->file_stat.st_uid;
            this->gid = this->file_stat.st_gid;
            this->rdev = this->file_stat.st_rdev;
            this->size = this->file_stat.st_size;
            this->blksize = this->file_stat.st_blksize;
            this->blocks = this->file_stat.st_blocks;

            this->atim = this->file_stat.st_atim;
            this->mtim = this->file_stat.st_mtim;
            this->ctim = this->file_stat.st_ctim;

            this->atime = this->file_stat.st_atim.tv_sec;
            this->mtime = this->file_stat.st_mtim.tv_sec;
            this->ctime = this->file_stat.st_ctim.tv_sec;
        }

      public:
        dev_t dev;         // ID of device containing file
        ino_t ino;         // Inode number
        mode_t mode;       // File type and mode
        nlink_t nlink;     // Number of hard links
        uid_t uid;         // User ID of owner
        gid_t gid;         // Group ID of owner
        dev_t rdev;        // Device ID (if special file)
        off_t size;        // Total size, in bytes
        blksize_t blksize; // Block size for filesystem I/O
        blkcnt_t blocks;   // Number of 512B blocks allocated

        struct timespec atim; // Time of last access
        struct timespec mtim; // Time of last modification
        struct timespec ctim; // Time of last status change

        time_t atime; // Backward compatibility
        time_t mtime;
        time_t ctime;

      protected:
        struct ::stat file_stat;

        bool valid{false};
    };

    class lstat : public stat
    {
      public:
        lstat() noexcept
        {
        }

        lstat(std::string_view path) noexcept
        {
            this->valid = (::lstat(path.data(), &this->file_stat) == 0);

            this->populate();
        }
    };
} // namespace ztd
