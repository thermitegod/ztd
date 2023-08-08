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

#include <sys/stat.h>

#include "../types.hxx"

namespace ztd
{
    // The inode block count for a file/directory is in units of
    // 512 byte blocks, not the filesystem block size.
    // To get the actual, on disk, size use (ztd::stat::blocks * ztd::BLOCK_SIZE)
    inline constexpr i64 BLOCK_SIZE{S_BLKSIZE};

    class stat
    {
      public:
        stat() = default;
        stat(const std::filesystem::path& path) noexcept;
        stat(int fd) noexcept;
        stat(int dirfd, const std::filesystem::path& pathname, int flags) noexcept;

        operator bool() const noexcept { return this->valid_; }

        // clang-format off
        [[deprecated("use operator bool()")]] [[nodiscard]] bool is_valid() const noexcept  { return this->valid_; }
        [[deprecated("use operator bool()")]] [[nodiscard]] bool exists() const noexcept { return this->valid_; }
        // clang-format on

        [[nodiscard]] u32 nlink() const noexcept; // Number of hard links
        [[nodiscard]] u32 uid() const noexcept;   // User ID of owner
        [[nodiscard]] u32 gid() const noexcept;   // Group ID of owner
        [[nodiscard]] u32 mode() const noexcept;  // File type and mode
        [[nodiscard]] u64 ino() const noexcept;   // Inode number

        [[nodiscard]] u64 size() const noexcept;         // Total size, in bytes
        [[nodiscard]] u64 size_on_disk() const noexcept; // Total on disk size, in bytes
        [[nodiscard]] u32 blksize() const noexcept;      // Block size for filesystem I/O
        [[nodiscard]] u64 blocks() const noexcept;       // Number of 512B blocks allocated

        // The ID of the device containing the filesystem where the file resides
        [[nodiscard]] u64 dev() const noexcept;       // ID of device containing file
        [[nodiscard]] u32 dev_major() const noexcept; // Major ID of device containing file
        [[nodiscard]] u32 dev_minor() const noexcept; // Minor ID of device containing file

        // If this file represents a device, the ID of the device
        [[nodiscard]] u64 rdev() const noexcept;       // Device ID (if special file)
        [[nodiscard]] u32 rdev_major() const noexcept; // Device major ID (if special file)
        [[nodiscard]] u32 rdev_minor() const noexcept; // Device minor ID (if special file)

        // Time

        [[nodiscard]] struct timespec atim() const noexcept; // Time of last access
        [[nodiscard]] struct timespec ctim() const noexcept; // Time of last metadata change
        [[nodiscard]] struct timespec mtim() const noexcept; // Time of last modification

        [[nodiscard]] time_t atime() const noexcept; // Backward compatibility
        [[nodiscard]] time_t ctime() const noexcept; // Backward compatibility
        [[nodiscard]] time_t mtime() const noexcept; // Backward compatibility

        // File type

        [[nodiscard]] bool is_directory() const noexcept;
        [[nodiscard]] bool is_regular_file() const noexcept;
        [[nodiscard]] bool is_symlink() const noexcept;
        [[nodiscard]] bool is_socket() const noexcept;
        [[nodiscard]] bool is_fifo() const noexcept;
        [[nodiscard]] bool is_block_file() const noexcept;
        [[nodiscard]] bool is_character_file() const noexcept;
        [[nodiscard]] bool is_other() const noexcept;

      protected:
        struct ::stat stat_ = {};
        bool valid_{false};
    };

    class lstat : public stat
    {
      public:
        lstat() = default;
        lstat(const std::filesystem::path& path) noexcept;
    };
} // namespace ztd
