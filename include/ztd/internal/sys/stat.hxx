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

#include <chrono>

#include <sys/stat.h>
// #include <errno.h>

#include "../types.hxx"

namespace ztd
{
    class stat
    {
      public:
        stat() = default;
        stat(std::string_view path) noexcept;
        stat(int fd) noexcept;
        stat(int dirfd, std::string_view pathname, int flags) noexcept;

        bool is_valid() const noexcept;
        bool is_directory() const noexcept;
        bool is_regular_file() const noexcept;
        bool is_symlink() const noexcept;
        bool is_socket() const noexcept;
        bool is_fifo() const noexcept;
        bool is_block_file() const noexcept;
        bool is_character_file() const noexcept;

      protected:
        void populate() noexcept;

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
        lstat() = default;
        lstat(std::string_view path) noexcept;
    };
} // namespace ztd
