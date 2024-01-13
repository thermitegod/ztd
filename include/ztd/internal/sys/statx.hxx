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

#include "../types.hxx"

namespace ztd
{
namespace detail
{
/**
 * @brief flags_set
 *
 * @param[in] v a bitmask
 * @param[in] flags bitmask flags
 *
 * @return True if the flags bitmask is set in the bitmask
 */
[[nodiscard]] [[gnu::always_inline]] inline constexpr bool
flags_set(const u64 v, const u64 flags) noexcept
{
    return (~(v) & (flags)) == 0;
}
} // namespace detail

struct statx
{
  public:
    enum class symlink
    {
        follow,    // equivilent to using ztd::stat()
        no_follow, // equivilent to using ztd::lstat()
    };

    statx() = default;

    statx(const std::filesystem::path& path, symlink follow_symlinks = symlink::no_follow) noexcept
    {
        const auto flags = follow_symlinks == symlink::follow ? AT_SYMLINK_FOLLOW : AT_SYMLINK_NOFOLLOW;

        this->valid_ =
            (::statx(0, path.c_str(), flags, (STATX_BASIC_STATS | STATX_BTIME | STATX_MNT_ID), &this->statx_) == 0);
    }

    operator bool() const noexcept { return this->valid_; }

    /**
     * Number of hard links
     */
    [[nodiscard]] u32
    nlink() const noexcept
    {
        return this->statx_.stx_nlink;
    }

    /**
     * User ID of owner
     */
    [[nodiscard]] u32
    uid() const noexcept
    {
        return this->statx_.stx_uid;
    }

    /**
     * Group ID of owner
     */
    [[nodiscard]] u32
    gid() const noexcept
    {
        return this->statx_.stx_gid;
    }

    /**
     * File type and mode
     */
    [[nodiscard]] u16
    mode() const noexcept
    {
        return this->statx_.stx_mode;
    }

    /**
     * Inode number
     */
    [[nodiscard]] u64
    ino() const noexcept
    {
        return this->statx_.stx_ino;
    }

    /**
     * Total size, in bytes
     */
    [[nodiscard]] u64
    size() const noexcept
    {
        return this->statx_.stx_size;
    }

    /**
     * Total on disk size, in bytes
     */
    [[nodiscard]] u64
    size_on_disk() const noexcept
    {
        // The inode block count for a file/directory is in units of
        // 512 byte blocks, not the filesystem block size.
        return this->statx_.stx_blocks * S_BLKSIZE;
    }

    /**
     * Block size for filesystem I/O
     */
    [[nodiscard]] u32
    blksize() const noexcept
    {
        return this->statx_.stx_blksize;
    }

    /**
     * Number of 512B blocks allocated
     */
    [[nodiscard]] u64
    blocks() const noexcept
    {
        return this->statx_.stx_blocks;
    }

    /**
     * The mount ID of the mount containing the file
     */
    [[nodiscard]] u64
    mount_id() const noexcept
    {
        return this->statx_.stx_mnt_id;
    }

    // The ID of the device containing the filesystem where the file resides

    /**
     * ID of device containing file
     */
    [[nodiscard]] u64
    dev() const noexcept
    {
        return gnu_dev_makedev(this->statx_.stx_dev_major, this->statx_.stx_dev_minor);
    }

    /**
     * Major ID of device containing file
     */
    [[nodiscard]] u32
    dev_major() const noexcept
    {
        return this->statx_.stx_dev_major;
    }

    /**
     * Minor ID of device containing file
     */
    [[nodiscard]] u32
    dev_minor() const noexcept
    {
        return this->statx_.stx_dev_minor;
    }

    // If this file represents a device, the ID of the device

    /**
     * Device ID (if special file)
     */
    [[nodiscard]] u64
    rdev() const noexcept
    {
        return gnu_dev_makedev(this->statx_.stx_rdev_major, this->statx_.stx_rdev_minor);
    }

    /**
     * Device major ID (if special file)
     */
    [[nodiscard]] u32
    rdev_major() const noexcept
    {
        return this->statx_.stx_rdev_major;
    }

    /**
     * Device minor ID (if special file)
     */
    [[nodiscard]] u32
    rdev_minor() const noexcept
    {
        return this->statx_.stx_rdev_minor;
    }

    // Time

    /**
     * Time of last access
     */
    [[nodiscard]] struct statx_timestamp
    atime() const noexcept
    {
        return this->statx_.stx_atime;
    }

    /**
     * Time of creation
     */
    [[nodiscard]] struct statx_timestamp
    btime() const noexcept
    {
        return this->statx_.stx_btime;
    }

    /**
     * Time of last metadata change
     */
    [[nodiscard]] struct statx_timestamp
    ctime() const noexcept
    {
        return this->statx_.stx_ctime;
    }

    /**
     * Time of last modification
     */
    [[nodiscard]] struct statx_timestamp
    mtime() const noexcept
    {
        return this->statx_.stx_mtime;
    }

    // File type

    [[nodiscard]] bool
    is_directory() const noexcept
    {
        return S_ISDIR(this->statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_regular_file() const noexcept
    {
        return S_ISREG(this->statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_symlink() const noexcept
    {
        return S_ISLNK(this->statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_socket() const noexcept
    {
        return S_ISSOCK(this->statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_fifo() const noexcept
    {
        return S_ISFIFO(this->statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_block_file() const noexcept
    {
        return S_ISBLK(this->statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_character_file() const noexcept
    {
        return S_ISCHR(this->statx_.stx_mode);
    }

    [[nodiscard]] bool
    is_other() const noexcept
    {
        return (!this->is_directory() && !this->is_regular_file() && !this->is_symlink());
    }

    // File attributes

    /**
     * The file is compressed by the filesystem
     */
    [[nodiscard]] bool
    is_compressed() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_COMPRESSED))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_COMPRESSED);
        }
        return false;
    }

    /**
     * The file cannot be modified
     */
    [[nodiscard]] bool
    is_immutable() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_IMMUTABLE))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_IMMUTABLE);
        }
        return false;
    }

    /**
     * The file can only be opened in append mode for writing
     */
    [[nodiscard]] bool
    is_append() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_APPEND))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_APPEND);
        }
        return false;
    }

    /**
     * The file is not a candidate for backup
     */
    [[nodiscard]] bool
    is_nodump() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_NODUMP))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_NODUMP);
        }
        return false;
    }

    /**
     * The file requires a key to be encrypted by the filesystem
     */
    [[nodiscard]] bool
    is_encrypted() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_ENCRYPTED))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_ENCRYPTED);
        }
        return false;
    }

    /**
     * The file is a automount trigger
     */
    [[nodiscard]] bool
    is_automount() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_AUTOMOUNT))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_AUTOMOUNT);
        }
        return false;
    }

    /**
     * The file is the root of a mount
     */
    [[nodiscard]] bool
    is_mount_root() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_MOUNT_ROOT))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_MOUNT_ROOT);
        }
        return false;
    }

    /**
     * The file has fs-verity enabled
     */
    [[nodiscard]] bool
    is_verity() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_VERITY))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_VERITY);
        }
        return false;
    }

    /**
     * The file is in the DAX (cpu direct access) state
     */
    [[nodiscard]] bool
    is_dax() const noexcept
    {
        if (detail::flags_set(this->statx_.stx_attributes_mask, STATX_ATTR_DAX))
        {
            return detail::flags_set(this->statx_.stx_attributes, STATX_ATTR_DAX);
        }
        return false;
    }

  private:
    struct ::statx statx_ = {};
    bool valid_{false};
};
} // namespace ztd
