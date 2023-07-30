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
    class statx
    {
      public:
        enum class symlink
        {
            follow,    // equivilent to using stat()
            no_follow, // equivilent to using lstat()
        };

        statx() = default;
        statx(const std::filesystem::path& path, symlink follow_symlinks = symlink::no_follow) noexcept;

        operator bool() const noexcept { return this->valid; }

        [[nodiscard]] u32 nlink() const noexcept; // Number of hard links
        [[nodiscard]] u32 uid() const noexcept;   // User ID of owner
        [[nodiscard]] u32 gid() const noexcept;   // Group ID of owner
        [[nodiscard]] u16 mode() const noexcept;  // File type and mode
        [[nodiscard]] u64 ino() const noexcept;   // Inode number

        [[nodiscard]] u64 size() const noexcept;         // Total size, in bytes
        [[nodiscard]] u64 size_on_disk() const noexcept; // Total on disk size, in bytes
        [[nodiscard]] u32 blksize() const noexcept;      // Block size for filesystem I/O
        [[nodiscard]] u64 blocks() const noexcept;       // Number of 512B blocks allocated

        // The ID of the device containing the filesystem where the file resides
        [[nodiscard]] u32 dev() const noexcept;       // ID of device containing file
        [[nodiscard]] u32 dev_major() const noexcept; // Major ID of device containing file
        [[nodiscard]] u32 dev_minor() const noexcept; // Minor ID of device containing file

        // If this file represents a device, the ID of the device
        [[nodiscard]] u32 rdev() const noexcept;       // Device ID (if special file)
        [[nodiscard]] u32 rdev_major() const noexcept; // Device major ID (if special file)
        [[nodiscard]] u32 rdev_minor() const noexcept; // Device minor ID (if special file)

        [[nodiscard]] u64 mount_id() const noexcept; // The mount ID of the mount containing the file

        // Time

        [[nodiscard]] struct statx_timestamp atime() const noexcept; // Time of last access
        [[nodiscard]] struct statx_timestamp btime() const noexcept; // Time of creation
        [[nodiscard]] struct statx_timestamp ctime() const noexcept; // Time of last status change
        [[nodiscard]] struct statx_timestamp mtime() const noexcept; // Time of last modification

        // File type

        [[nodiscard]] bool is_directory() const noexcept;
        [[nodiscard]] bool is_regular_file() const noexcept;
        [[nodiscard]] bool is_symlink() const noexcept;
        [[nodiscard]] bool is_socket() const noexcept;
        [[nodiscard]] bool is_fifo() const noexcept;
        [[nodiscard]] bool is_block_file() const noexcept;
        [[nodiscard]] bool is_character_file() const noexcept;
        [[nodiscard]] bool is_other() const noexcept;

        // File attributes

        [[nodiscard]] bool is_compressed() const noexcept; // The file is compressed by the filesystem
        [[nodiscard]] bool is_immutable() const noexcept;  // The file cannot be modified
        [[nodiscard]] bool is_append() const noexcept;     // The file can only be opened in append mode for writing
        [[nodiscard]] bool is_nodump() const noexcept;     // The File is not a candidate for backup
        [[nodiscard]] bool is_encrypted() const noexcept;  // The file requires a key to be encrypted by the filesystem
        [[nodiscard]] bool is_verity() const noexcept;     // The file has fs-verity enabled
        [[nodiscard]] bool is_dax() const noexcept;        // The file is in the DAX (cpu direct access) state

      private:
        struct ::statx file_stat = {};
        bool valid{false};
    };
} // namespace ztd
