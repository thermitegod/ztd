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

#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <sys/sysmacros.h>

#include "../../types.hxx"

namespace ztd
{
// The inode block count for a file/directory is in units of
// 512 byte blocks, not the filesystem block size.
// To get the actual, on disk, size use (ztd::stat::blocks * ztd::BLOCK_SIZE)
[[deprecated]] inline constexpr i64 BLOCK_SIZE{S_BLKSIZE};

struct stat
{
  public:
    stat() = default;

    stat(const std::filesystem::path& path) noexcept { this->valid_ = (::stat(path.c_str(), &this->stat_) == 0); }

    [[deprecated]] stat(int fd) noexcept { this->valid_ = (::fstat(fd, &this->stat_) == 0); }

    [[deprecated]] stat(int dirfd, const std::filesystem::path& pathname, int flags) noexcept
    {
        this->valid_ = (::fstatat(dirfd, pathname.c_str(), &this->stat_, flags) == 0);
    }

    [[deprecated("use operator bool()")]] [[nodiscard]] bool
    is_valid() const noexcept
    {
        return this->valid_;
    }
    [[deprecated("use operator bool()")]] [[nodiscard]] bool
    exists() const noexcept
    {
        return this->valid_;
    }

    operator bool() const noexcept { return this->valid_; }

    /**
     * Number of hard links
     */
    [[nodiscard]] u32
    nlink() const noexcept
    {
        return this->stat_.st_nlink;
    }

    /**
     * User ID of owner
     */
    [[nodiscard]] u32
    uid() const noexcept
    {
        return this->stat_.st_uid;
    }

    /**
     * Group ID of owner
     */
    [[nodiscard]] u32
    gid() const noexcept
    {
        return this->stat_.st_gid;
    }

    /**
     * File type and mode
     */
    [[nodiscard]] u32
    mode() const noexcept
    {
        return this->stat_.st_mode;
    }

    /**
     * Inode number
     */
    [[nodiscard]] u64
    ino() const noexcept
    {
        return this->stat_.st_ino;
    }

    /**
     * Total size, in bytes
     */
    [[nodiscard]] u64
    size() const noexcept
    {
        return this->stat_.st_size;
    }

    /**
     * Total on disk size, in bytes
     */
    [[nodiscard]] u64
    size_on_disk() const noexcept
    {
        // The inode block count for a file/directory is in units of
        // 512 byte blocks, not the filesystem block size.
        return this->stat_.st_blocks * S_BLKSIZE;
    }

    /**
     * Block size for filesystem I/O
     */
    [[nodiscard]] u32
    blksize() const noexcept
    {
        return this->stat_.st_blksize;
    }

    /**
     * Number of 512B blocks allocated
     */
    [[nodiscard]] u64
    blocks() const noexcept
    {
        return this->stat_.st_blocks;
    }

    // The ID of the device containing the filesystem where the file resides

    /**
     * ID of device containing file
     */
    [[nodiscard]] u64
    dev() const noexcept
    {
        return this->stat_.st_dev;
    }

    /**
     * Major ID of device containing file
     */
    [[nodiscard]] u32
    dev_major() const noexcept
    {
        return gnu_dev_major(this->stat_.st_dev);
    }

    /**
     * Minor ID of device containing file
     */
    [[nodiscard]] u32
    dev_minor() const noexcept
    {
        return gnu_dev_minor(this->stat_.st_dev);
    }

    // If this file represents a device, the ID of the device

    /**
     * Device ID (if special file)
     */
    [[nodiscard]] u64
    rdev() const noexcept
    {
        return this->stat_.st_rdev;
    }

    /**
     * Device major ID (if special file)
     */
    [[nodiscard]] u32
    rdev_major() const noexcept
    {
        return gnu_dev_major(this->stat_.st_rdev);
    }

    /**
     * Device minor ID (if special file)
     */
    [[nodiscard]] u32
    rdev_minor() const noexcept
    {
        return gnu_dev_minor(this->stat_.st_rdev);
    }

    // Time

    /**
     * Time of last access
     */
    [[nodiscard]] struct timespec
    atim() const noexcept
    {
        return this->stat_.st_atim;
    }

    /**
     * Time of last metadata change
     */
    [[nodiscard]] struct timespec
    ctim() const noexcept
    {
        return this->stat_.st_atim;
    }

    /**
     * Time of last modification
     */
    [[nodiscard]] struct timespec
    mtim() const noexcept
    {
        return this->stat_.st_atim;
    }

    /**
     * Time of last access, Backward compatibility
     */
    [[nodiscard]] time_t
    atime() const noexcept
    {
        return this->stat_.st_mtim.tv_sec;
    }

    /**
     * Time of last metadata change, Backward compatibility
     */
    [[nodiscard]] time_t
    ctime() const noexcept
    {
        return this->stat_.st_mtim.tv_sec;
    }

    /**
     * Time of last modification, Backward compatibility
     */
    [[nodiscard]] time_t
    mtime() const noexcept
    {
        return this->stat_.st_mtim.tv_sec;
    }

    // File type

    [[nodiscard]] bool
    is_directory() const noexcept
    {
        return S_ISDIR(this->stat_.st_mode);
    }

    [[nodiscard]] bool
    is_regular_file() const noexcept
    {
        return S_ISREG(this->stat_.st_mode);
    }

    [[nodiscard]] bool
    is_symlink() const noexcept
    {
        return S_ISLNK(this->stat_.st_mode);
    }

    [[nodiscard]] bool
    is_socket() const noexcept
    {
        return S_ISSOCK(this->stat_.st_mode);
    }

    [[nodiscard]] bool
    is_fifo() const noexcept
    {
        return S_ISFIFO(this->stat_.st_mode);
    }

    [[nodiscard]] bool
    is_block_file() const noexcept
    {
        return S_ISBLK(this->stat_.st_mode);
    }

    [[nodiscard]] bool
    is_character_file() const noexcept
    {
        return S_ISCHR(this->stat_.st_mode);
    }

    [[nodiscard]] bool
    is_other() const noexcept
    {
        return (!this->is_directory() && !this->is_regular_file() && !this->is_symlink());
    }

  protected:
    struct ::stat stat_ = {};
    bool valid_{false};
};

struct lstat : public stat
{
  public:
    lstat() = default;
    lstat(const std::filesystem::path& path) noexcept { this->valid_ = (::lstat(path.c_str(), &this->stat_) == 0); }
};
} // namespace ztd
