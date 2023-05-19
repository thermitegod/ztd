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

#include <string_view>

#include <filesystem>

#include <sys/stat.h>
// #include <errno.h>

#include "../types.hxx"

namespace ztd
{
    // The inode block count for a file/directory is in units of
    // 512 byte blocks, not the filesystem block size.
    // To get the actual, on disk, size use (ztd::stat::blocks * ztd::BLOCK_SIZE)
    inline constexpr i64 BLOCK_SIZE{512};

    class stat
    {
      public:
        stat() = default;
        stat(const std::filesystem::path& path) noexcept;
        stat(int fd) noexcept;
        stat(int dirfd, const std::string_view pathname, int flags) noexcept;

        [[nodiscard]] bool is_valid() const noexcept;
        [[nodiscard]] bool exists() const noexcept;

        [[nodiscard]] dev_t dev() const noexcept;         // ID of device containing file
        [[nodiscard]] ino_t ino() const noexcept;         // Inode number
        [[nodiscard]] mode_t mode() const noexcept;       // File type and mode
        [[nodiscard]] nlink_t nlink() const noexcept;     // Number of hard links
        [[nodiscard]] uid_t uid() const noexcept;         // User ID of owner
        [[nodiscard]] gid_t gid() const noexcept;         // Group ID of owner
        [[nodiscard]] dev_t rdev() const noexcept;        // Device ID (if special file)
        [[nodiscard]] off_t size() const noexcept;        // Total size, in bytes
        [[nodiscard]] blksize_t blksize() const noexcept; // Block size for filesystem I/O
        [[nodiscard]] blkcnt_t blocks() const noexcept;   // Number of 512B blocks allocated

        [[nodiscard]] struct timespec atim() const noexcept; // Time of last access
        [[nodiscard]] struct timespec mtim() const noexcept; // Time of last modification
        [[nodiscard]] struct timespec ctim() const noexcept; // Time of last status change

        [[nodiscard]] time_t atime() const noexcept; // Backward compatibility
        [[nodiscard]] time_t mtime() const noexcept; // Backward compatibility
        [[nodiscard]] time_t ctime() const noexcept; // Backward compatibility

        [[nodiscard]] bool is_directory() const noexcept;
        [[nodiscard]] bool is_regular_file() const noexcept;
        [[nodiscard]] bool is_symlink() const noexcept;
        [[nodiscard]] bool is_socket() const noexcept;
        [[nodiscard]] bool is_fifo() const noexcept;
        [[nodiscard]] bool is_block_file() const noexcept;
        [[nodiscard]] bool is_character_file() const noexcept;
        [[nodiscard]] bool is_other() const noexcept;

      protected:
        struct ::stat file_stat = {};

        bool valid{false};
    };

    class lstat : public stat
    {
      public:
        lstat() = default;
        lstat(const std::filesystem::path& path) noexcept;
    };
} // namespace ztd
