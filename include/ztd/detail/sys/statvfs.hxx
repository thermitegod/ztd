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
#include <cstdint>

#include <fcntl.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <unistd.h>

namespace ztd
{
struct statvfs
{
    statvfs() = delete;
    statvfs(const statvfs&) = default;
    statvfs(statvfs&&) noexcept = default;
    statvfs& operator=(const statvfs&) = default;
    statvfs& operator=(statvfs&&) noexcept = default;
    ~statvfs() = default;

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
    [[nodiscard]] std::uint64_t
    bsize() const noexcept
    {
        return statvfs_.f_bsize;
    }

    /**
     * Fragment size
     */
    [[nodiscard]] std::uint64_t
    frsize() const noexcept
    {
        return statvfs_.f_frsize;
    }

    /**
     * Size of fs in f_frsize units
     */
    [[nodiscard]] std::uint64_t
    blocks() const noexcept
    {
        return statvfs_.f_blocks;
    }

    /**
     * Number of free blocks
     */
    [[nodiscard]] std::uint64_t
    bfree() const noexcept
    {
        return statvfs_.f_bfree;
    }

    /**
     * Number of free blocks for unprivileged users
     */
    [[nodiscard]] std::uint64_t
    bavail() const noexcept
    {
        return statvfs_.f_bavail;
    }

    /**
     * Number of inodes
     */
    [[nodiscard]] std::uint64_t
    files() const noexcept
    {
        return statvfs_.f_files;
    }

    /**
     * Number of free inodes
     */
    [[nodiscard]] std::uint64_t
    ffree() const noexcept
    {
        return statvfs_.f_ffree;
    }

    /**
     * Number of free inodes for unprivileged users
     */
    [[nodiscard]] std::uint64_t
    favail() const noexcept
    {
        return statvfs_.f_favail;
    }

    /**
     * Filesystem ID
     */
    [[nodiscard]] std::uint64_t
    fsid() const noexcept
    {
        return statvfs_.f_fsid;
    }

    /**
     * Mount flags
     */
    [[nodiscard]] std::uint64_t
    flag() const noexcept
    {
        return statvfs_.f_flag;
    }

    /**
     * Maximum filename length
     */
    [[nodiscard]] std::uint64_t
    namemax() const noexcept
    {
        return statvfs_.f_namemax;
    }

    /**
     * Type of filesystem, defined in <linux/magic.h>
     */
    [[nodiscard]] std::uint32_t
    type() const noexcept
    {
        return statvfs_.f_type;
    }

  private:
    statvfs(const std::filesystem::path& path, std::error_code& ec) noexcept
    {
        if (::statvfs(path.c_str(), &statvfs_) != 0)
        {
            ec = std::error_code(errno, std::generic_category());
        }
    }

    struct ::statvfs statvfs_ = {};
};
} // namespace ztd
