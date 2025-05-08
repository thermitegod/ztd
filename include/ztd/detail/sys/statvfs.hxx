/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include <expected>
#include <filesystem>
#include <system_error>

#include <cerrno>

#include <fcntl.h>
#include <sys/statvfs.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <unistd.h>

#include "../types.hxx"

namespace ztd
{
struct statvfs
{
    statvfs() = default;

    statvfs(const std::filesystem::path& path)
    {
        if (::statvfs(path.c_str(), &this->statvfs_) != 0)
        {
            throw std::system_error(errno, std::generic_category(), "statvfs failed");
        }
    }

    statvfs(const std::filesystem::path& path, std::error_code& ec) noexcept
    {
        if (::statvfs(path.c_str(), &this->statvfs_) != 0)
        {
            ec = std::make_error_code(std::errc(errno));
        }
    }

    [[nodiscard]] static std::expected<statvfs, std::error_code>
    create(const std::filesystem::path& path) noexcept
    {
        std::error_code ec;
        auto s = statvfs(path, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return s;
    }

    /**
     * Filesystem block size
     */
    [[nodiscard]] u64
    bsize() const noexcept
    {
        return this->statvfs_.f_bsize;
    }

    /**
     * Fragment size
     */
    [[nodiscard]] u64
    frsize() const noexcept
    {
        return this->statvfs_.f_frsize;
    }

    /**
     * Size of fs in f_frsize units
     */
    [[nodiscard]] u64
    blocks() const noexcept
    {
        return this->statvfs_.f_blocks;
    }

    /**
     * Number of free blocks
     */
    [[nodiscard]] u64
    bfree() const noexcept
    {
        return this->statvfs_.f_bfree;
    }

    /**
     * Number of free blocks for unprivileged users
     */
    [[nodiscard]] u64
    bavail() const noexcept
    {
        return this->statvfs_.f_bavail;
    }

    /**
     * Number of inodes
     */
    [[nodiscard]] u64
    files() const noexcept
    {
        return this->statvfs_.f_files;
    }

    /**
     * Number of free inodes
     */
    [[nodiscard]] u64
    ffree() const noexcept
    {
        return this->statvfs_.f_ffree;
    }

    /**
     * Number of free inodes for unprivileged users
     */
    [[nodiscard]] u64
    favail() const noexcept
    {
        return this->statvfs_.f_favail;
    }

    /**
     * Filesystem ID
     */
    [[nodiscard]] u64
    fsid() const noexcept
    {
        return this->statvfs_.f_fsid;
    }

    /**
     * Mount flags
     */
    [[nodiscard]] u64
    flag() const noexcept
    {
        return this->statvfs_.f_flag;
    }

    /**
     * Maximum filename length
     */
    [[nodiscard]] u64
    namemax() const noexcept
    {
        return this->statvfs_.f_namemax;
    }

#if defined(__GLIBC__) && ((__GLIBC__ > 2) || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 39))
    /**
     * Type of filesystem, defined in <linux/magic.h>
     */
    [[nodiscard]] u32
    type() const noexcept
    {
        return this->statvfs_.f_type;
    }
#endif

  private:
    struct ::statvfs statvfs_ = {};
};
} // namespace ztd
