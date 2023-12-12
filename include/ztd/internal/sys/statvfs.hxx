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
#include <sys/statvfs.h>

#include <sys/sysmacros.h>

#include "../types.hxx"

namespace ztd
{
struct statvfs
{
  public:
    statvfs() = default;

    statvfs(const std::filesystem::path& path) noexcept { this->valid_ = (::statvfs(path.c_str(), &this->stat_) == 0); }

    statvfs(int fd) noexcept { this->valid_ = (::fstatvfs(fd, &this->stat_) == 0); }

    operator bool() const noexcept { return this->valid_; }

    [[deprecated("use operator bool()")]] [[nodiscard]] bool
    is_valid() const noexcept
    {
        return this->valid_;
    }

    /**
     * Filesystem block size
     */
    [[nodiscard]] u64
    bsize() const noexcept
    {
        return this->stat_.f_bsize;
    }
    /**
     * Fragment size
     */
    [[nodiscard]] u64
    frsize() const noexcept
    {
        return this->stat_.f_frsize;
    }

    /**
     * Size of fs in f_frsize units
     */
    [[nodiscard]] fsblkcnt_t
    blocks() const noexcept
    {
        return this->stat_.f_blocks;
    }
    /**
     * Number of free blocks
     */
    [[nodiscard]] fsblkcnt_t
    bfree() const noexcept
    {
        return this->stat_.f_bfree;
    }
    /**
     * Number of free blocks for unprivileged users
     */
    [[nodiscard]] fsblkcnt_t
    bavail() const noexcept
    {
        return this->stat_.f_bavail;
    }

    /**
     * Number of inodes
     */
    [[nodiscard]] fsfilcnt_t
    files() const noexcept
    {
        return this->stat_.f_files;
    }
    /**
     * Number of free inodes
     */
    [[nodiscard]] fsfilcnt_t
    ffree() const noexcept
    {
        return this->stat_.f_ffree;
    }
    /**
     * Number of free inodes for unprivileged users
     */
    [[nodiscard]] fsfilcnt_t
    favail() const noexcept
    {
        return this->stat_.f_favail;
    }

    /**
     * Filesystem ID
     */
    [[nodiscard]] u64
    fsid() const noexcept
    {
        return this->stat_.f_fsid;
    }

    /**
     * Mount flags
     */
    [[nodiscard]] u64
    flag() const noexcept
    {
        return this->stat_.f_flag;
    }

    /**
     * Maximum filename length
     */
    [[nodiscard]] u64
    namemax() const noexcept
    {
        return this->stat_.f_namemax;
    }

  private:
    struct ::statvfs stat_ = {};
    bool valid_{false};
};
} // namespace ztd
