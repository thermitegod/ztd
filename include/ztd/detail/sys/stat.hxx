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

#include <array>
#include <expected>
#include <filesystem>
#include <string>
#include <system_error>

#include <cerrno>
#include <cstdint>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <unistd.h>

namespace ztd
{
class statx
{
  public:
    enum class symlink : std::uint8_t
    {
        follow,    // equivalent to using ztd::stat()
        no_follow, // equivalent to using ztd::lstat()
    };

    statx() = delete;
    statx(const statx&) = default;
    statx(statx&&) noexcept = default;
    statx& operator=(const statx&) = default;
    statx& operator=(statx&&) noexcept = default;
    ~statx() = default;

    [[nodiscard]] static std::expected<statx, std::error_code>
    create(const std::filesystem::path& path,
           const symlink follow_symlinks = symlink::follow) noexcept
    {
        constexpr std::uint32_t mask = STATX_BASIC_STATS | STATX_BTIME | STATX_MNT_ID_UNIQUE;

        return create(path, mask, follow_symlinks);
    }

    [[nodiscard]] static std::expected<statx, std::error_code>
    create(const std::filesystem::path& path, const std::uint32_t mask,
           const symlink follow_symlinks = symlink::follow) noexcept
    {
        std::error_code ec;
        auto s = statx(path, mask, follow_symlinks, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return s;
    }

    /**
     * Number of hard links
     */
    [[nodiscard]] std::uint32_t
    nlink() const noexcept
    {
        return statx_.stx_nlink;
    }

    /**
     * User ID of owner
     */
    [[nodiscard]] uid_t
    uid() const noexcept
    {
        return statx_.stx_uid;
    }

    /**
     * Group ID of owner
     */
    [[nodiscard]] gid_t
    gid() const noexcept
    {
        return statx_.stx_gid;
    }

    /**
     * File type and mode
     */
    [[nodiscard]] std::uint16_t
    mode() const noexcept
    {
        return statx_.stx_mode;
    }

    /**
     * File permissions
     */
    [[nodiscard]] std::filesystem::perms
    perms() const noexcept
    {
        return static_cast<std::filesystem::perms>(statx_.stx_mode) & std::filesystem::perms::mask;
    }

    /**
     * File permissions
     */
    [[nodiscard]] std::string
    perms_fancy() const noexcept
    {
        std::uint8_t file_type{0};
        std::uint8_t owner_read{1};
        std::uint8_t owner_write{2};
        std::uint8_t owner_exec{3};
        std::uint8_t group_read{4};
        std::uint8_t group_write{5};
        std::uint8_t group_exec{6};
        std::uint8_t other_read{7};
        std::uint8_t other_write{8};
        std::uint8_t other_exec{9};

        // blank permissions
        std::array<char, 10> perm = {
            '-',
            '-',
            '-',
            '-',
            '-',
            '-',
            '-',
            '-',
            '-',
            '-',
        };

        // File Type Permissions
        if (is_regular_file())
        {
            perm[file_type] = '-';
        }
        else if (is_directory())
        {
            perm[file_type] = 'd';
        }
        else if (is_symlink())
        {
            perm[file_type] = 'l';
        }
        else if (is_character_file())
        {
            perm[file_type] = 'c';
        }
        else if (is_block_file())
        {
            perm[file_type] = 'b';
        }
        else if (is_fifo())
        {
            perm[file_type] = 'p';
        }
        else if (is_socket())
        {
            perm[file_type] = 's';
        }

        const auto p = perms();

        // Owner
        if ((p & std::filesystem::perms::owner_read) != std::filesystem::perms::none)
        {
            perm[owner_read] = 'r';
        }

        if ((p & std::filesystem::perms::owner_write) != std::filesystem::perms::none)
        {
            perm[owner_write] = 'w';
        }

        if ((p & std::filesystem::perms::set_uid) != std::filesystem::perms::none)
        {
            if ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none)
            {
                perm[owner_exec] = 's';
            }
            else
            {
                perm[owner_exec] = 'S';
            }
        }
        else
        {
            if ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none)
            {
                perm[owner_exec] = 'x';
            }
        }

        // Group
        if ((p & std::filesystem::perms::group_read) != std::filesystem::perms::none)
        {
            perm[group_read] = 'r';
        }

        if ((p & std::filesystem::perms::group_write) != std::filesystem::perms::none)
        {
            perm[group_write] = 'w';
        }

        if ((p & std::filesystem::perms::set_gid) != std::filesystem::perms::none)
        {
            if ((p & std::filesystem::perms::group_exec) != std::filesystem::perms::none)
            {
                perm[group_exec] = 's';
            }
            else
            {
                perm[group_exec] = 'S';
            }
        }
        else
        {
            if ((p & std::filesystem::perms::group_exec) != std::filesystem::perms::none)
            {
                perm[group_exec] = 'x';
            }
        }

        // Other
        if ((p & std::filesystem::perms::others_read) != std::filesystem::perms::none)
        {
            perm[other_read] = 'r';
        }

        if ((p & std::filesystem::perms::others_write) != std::filesystem::perms::none)
        {
            perm[other_write] = 'w';
        }

        if ((p & std::filesystem::perms::sticky_bit) != std::filesystem::perms::none)
        {
            if ((p & std::filesystem::perms::others_exec) != std::filesystem::perms::none)
            {
                perm[other_exec] = 't';
            }
            else
            {
                perm[other_exec] = 'T';
            }
        }
        else
        {
            if ((p & std::filesystem::perms::others_exec) != std::filesystem::perms::none)
            {
                perm[other_exec] = 'x';
            }
        }

        return {perm.cbegin(), perm.cend()};
    }

    /**
     * Inode number
     */
    [[nodiscard]] std::uint64_t
    ino() const noexcept
    {
        return statx_.stx_ino;
    }

    /**
     * Total size, in bytes
     */
    [[nodiscard]] std::uint64_t
    size() const noexcept
    {
        return statx_.stx_size;
    }

    /**
     * Total on disk size, in bytes
     */
    [[nodiscard]] std::uint64_t
    size_on_disk() const noexcept
    {
        return statx_.stx_blocks * block_size;
    }

    /**
     * Block size for filesystem I/O
     */
    [[nodiscard]] std::uint32_t
    blksize() const noexcept
    {
        return statx_.stx_blksize;
    }

    /**
     * Number of 512B blocks allocated
     */
    [[nodiscard]] std::uint64_t
    blocks() const noexcept
    {
        return statx_.stx_blocks;
    }

    // The ID of the device containing the filesystem where the file resides

    /**
     * ID of device containing file
     */
    [[nodiscard]] std::uint64_t
    dev() const noexcept
    {
        return gnu_dev_makedev(statx_.stx_dev_major, statx_.stx_dev_minor);
    }

    /**
     * Major ID of device containing file
     */
    [[nodiscard]] std::uint32_t
    dev_major() const noexcept
    {
        return statx_.stx_dev_major;
    }

    /**
     * Minor ID of device containing file
     */
    [[nodiscard]] std::uint32_t
    dev_minor() const noexcept
    {
        return statx_.stx_dev_minor;
    }

    // If this file represents a device, the ID of the device

    /**
     * Device ID (if special file)
     */
    [[nodiscard]] std::uint64_t
    rdev() const noexcept
    {
        return gnu_dev_makedev(statx_.stx_rdev_major, statx_.stx_rdev_minor);
    }

    /**
     * Device major ID (if special file)
     */
    [[nodiscard]] std::uint32_t
    rdev_major() const noexcept
    {
        return statx_.stx_rdev_major;
    }

    /**
     * Device minor ID (if special file)
     */
    [[nodiscard]] std::uint32_t
    rdev_minor() const noexcept
    {
        return statx_.stx_rdev_minor;
    }

    /**
     * The mount ID of the mount containing the file
     */
    [[nodiscard]] std::uint64_t
    mount_id() const noexcept
    {
        return statx_.stx_mnt_id;
    }

    [[nodiscard]] std::uint64_t
    subvol() const noexcept
    {
        return statx_.stx_subvol;
    }

    // Time

    /**
     * Time of last access
     */
    [[nodiscard]] std::chrono::system_clock::time_point
    atime() const noexcept
    {
        return std::chrono::system_clock::from_time_t(statx_.stx_atime.tv_sec) +
               std::chrono::nanoseconds(statx_.stx_atime.tv_nsec);
    }

    /**
     * Time of creation
     */
    [[nodiscard]] std::chrono::system_clock::time_point
    btime() const noexcept
    {
        return std::chrono::system_clock::from_time_t(statx_.stx_btime.tv_sec) +
               std::chrono::nanoseconds(statx_.stx_btime.tv_nsec);
    }

    /**
     * Time of last metadata change
     */
    [[nodiscard]] std::chrono::system_clock::time_point
    ctime() const noexcept
    {
        return std::chrono::system_clock::from_time_t(statx_.stx_ctime.tv_sec) +
               std::chrono::nanoseconds(statx_.stx_ctime.tv_nsec);
    }

    /**
     * Time of last modification
     */
    [[nodiscard]] std::chrono::system_clock::time_point
    mtime() const noexcept
    {
        return std::chrono::system_clock::from_time_t(statx_.stx_mtime.tv_sec) +
               std::chrono::nanoseconds(statx_.stx_mtime.tv_nsec);
    }

    // File type

    [[nodiscard]] bool
    is_directory() const noexcept
    {
        return S_ISDIR(statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_regular_file() const noexcept
    {
        return S_ISREG(statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_symlink() const noexcept
    {
        return S_ISLNK(statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_socket() const noexcept
    {
        return S_ISSOCK(statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_fifo() const noexcept
    {
        return S_ISFIFO(statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_block_file() const noexcept
    {
        return S_ISBLK(statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_character_file() const noexcept
    {
        return S_ISCHR(statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_other() const noexcept
    {
        return (!is_directory() && !is_regular_file() && !is_symlink());
    }

    // File attributes

    /**
     * The file is compressed by the filesystem
     */
    [[nodiscard]] bool
    is_compressed() const noexcept
    {
        return has_attribute(STATX_ATTR_COMPRESSED);
    }

    /**
     * The file cannot be modified
     */
    [[nodiscard]] bool
    is_immutable() const noexcept
    {
        return has_attribute(STATX_ATTR_IMMUTABLE);
    }

    /**
     * The file can only be opened in append mode for writing
     */
    [[nodiscard]] bool
    is_append() const noexcept
    {
        return has_attribute(STATX_ATTR_APPEND);
    }

    /**
     * The file is not a candidate for backup
     */
    [[nodiscard]] bool
    is_nodump() const noexcept
    {
        return has_attribute(STATX_ATTR_NODUMP);
    }

    /**
     * The file requires a key to be encrypted by the filesystem
     */
    [[nodiscard]] bool
    is_encrypted() const noexcept
    {
        return has_attribute(STATX_ATTR_ENCRYPTED);
    }

    /**
     * The file is a automount trigger
     */
    [[nodiscard]] bool
    is_automount() const noexcept
    {
        return has_attribute(STATX_ATTR_AUTOMOUNT);
    }

    /**
     * The file is the root of a mount
     */
    [[nodiscard]] bool
    is_mount_root() const noexcept
    {
        return has_attribute(STATX_ATTR_MOUNT_ROOT);
    }

    /**
     * The file has fs-verity enabled
     */
    [[nodiscard]] bool
    is_verity() const noexcept
    {
        return has_attribute(STATX_ATTR_VERITY);
    }

    /**
     * The file is in the DAX (cpu direct access) state
     */
    [[nodiscard]] bool
    is_dax() const noexcept
    {
        return has_attribute(STATX_ATTR_DAX);
    }

  private:
    friend class stat;
    friend class lstat;

    explicit statx(const std::filesystem::path& path, const std::uint32_t mask,
                   symlink follow_symlinks, std::error_code& ec) noexcept
    {
        const auto flags = follow_symlinks == symlink::follow ? 0 : AT_SYMLINK_NOFOLLOW;

        if (::statx(AT_FDCWD, path.c_str(), flags, mask, &statx_) != 0)
        {
            ec = std::error_code(errno, std::generic_category());
        }
    }

    /**
     * @brief flags_set
     *
     * @param[in] v a bitmask
     * @param[in] flags bitmask flags
     *
     * @return True if the flags bitmask is set in the bitmask
     */
    [[nodiscard]] [[gnu::always_inline]] static constexpr bool
    flags_set(std::uint64_t v, std::uint64_t flags) noexcept
    {
        return (~v & flags) == 0;
    }

    // if an attribute is both supported and set
    [[nodiscard]] constexpr bool
    has_attribute(const std::uint64_t attribute) const noexcept
    {
        return flags_set(statx_.stx_attributes_mask, attribute) &&
               flags_set(statx_.stx_attributes, attribute);
    }

    // The inode block count for a file/directory is in units of
    // 512 byte blocks, not the filesystem block size.
    static constexpr std::uint64_t block_size = S_BLKSIZE;

    struct ::statx statx_ = {};
};

class stat : public statx
{
  public:
    stat() = delete;
    stat(const stat&) = default;
    stat(stat&&) noexcept = default;
    stat& operator=(const stat&) = default;
    stat& operator=(stat&&) noexcept = default;
    ~stat() = default;

    [[nodiscard]] static std::expected<stat, std::error_code>
    create(const std::filesystem::path& path) noexcept
    {
        constexpr std::uint32_t mask = STATX_BASIC_STATS | STATX_BTIME | STATX_MNT_ID_UNIQUE;

        return create(path, mask);
    }

    [[nodiscard]] static std::expected<stat, std::error_code>
    create(const std::filesystem::path& path, const std::uint32_t mask) noexcept
    {
        std::error_code ec;
        auto s = stat(path, mask, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return s;
    }

  private:
    explicit stat(const std::filesystem::path& path, const std::uint32_t mask,
                  std::error_code& ec) noexcept
        : statx(path, mask, symlink::follow, ec)
    {
    }
};

class lstat : public statx
{
  public:
    lstat() = delete;
    lstat(const lstat&) = default;
    lstat(lstat&&) noexcept = default;
    lstat& operator=(const lstat&) = default;
    lstat& operator=(lstat&&) noexcept = default;
    ~lstat() = default;

    [[nodiscard]] static std::expected<lstat, std::error_code>
    create(const std::filesystem::path& path) noexcept
    {
        constexpr std::uint32_t mask = STATX_BASIC_STATS | STATX_BTIME | STATX_MNT_ID_UNIQUE;

        return create(path, mask);
    }

    [[nodiscard]] static std::expected<lstat, std::error_code>
    create(const std::filesystem::path& path, const std::uint32_t mask) noexcept
    {
        std::error_code ec;
        auto s = lstat(path, mask, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return s;
    }

  private:
    explicit lstat(const std::filesystem::path& path, const std::uint32_t mask,
                   std::error_code& ec) noexcept
        : statx(path, mask, symlink::no_follow, ec)
    {
    }
};
} // namespace ztd
