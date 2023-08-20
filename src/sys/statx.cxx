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

#include <filesystem>

#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <sys/sysmacros.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sys/statx.hxx"

ztd::statx::statx(const std::filesystem::path& path, symlink follow_symlinks) noexcept
{
    const auto flags = follow_symlinks == symlink::follow ? AT_SYMLINK_FOLLOW : AT_SYMLINK_NOFOLLOW;

    this->valid_ =
        (::statx(0, path.c_str(), flags, (STATX_BASIC_STATS | STATX_BTIME | STATX_MNT_ID), &this->statx_) == 0);
}

u32
ztd::statx::nlink() const noexcept
{
    return this->statx_.stx_nlink;
}

u32
ztd::statx::uid() const noexcept
{
    return this->statx_.stx_uid;
}

u32
ztd::statx::gid() const noexcept
{
    return this->statx_.stx_gid;
}

u16
ztd::statx::mode() const noexcept
{
    return this->statx_.stx_mode;
}

u64
ztd::statx::ino() const noexcept
{
    return this->statx_.stx_ino;
}

u64
ztd::statx::size() const noexcept
{
    return this->statx_.stx_size;
}

u64
ztd::statx::size_on_disk() const noexcept
{
    // The inode block count for a file/directory is in units of
    // 512 byte blocks, not the filesystem block size.
    return this->statx_.stx_blocks * S_BLKSIZE;
}

u32
ztd::statx::blksize() const noexcept
{
    return this->statx_.stx_blksize;
}

u64
ztd::statx::blocks() const noexcept
{
    return this->statx_.stx_blocks;
}

u64
ztd::statx::dev() const noexcept
{
    return gnu_dev_makedev(this->statx_.stx_dev_major, this->statx_.stx_dev_minor);
}

u32
ztd::statx::dev_major() const noexcept
{
    return this->statx_.stx_dev_major;
}

u32
ztd::statx::dev_minor() const noexcept
{
    return this->statx_.stx_dev_minor;
}

u64
ztd::statx::rdev() const noexcept
{
    return gnu_dev_makedev(this->statx_.stx_rdev_major, this->statx_.stx_rdev_minor);
}

u32
ztd::statx::rdev_major() const noexcept
{
    return this->statx_.stx_rdev_major;
}

u32
ztd::statx::rdev_minor() const noexcept
{
    return this->statx_.stx_rdev_minor;
}

u64
ztd::statx::mount_id() const noexcept
{
    return this->statx_.stx_mnt_id;
}

struct statx_timestamp
ztd::statx::atime() const noexcept
{
    return this->statx_.stx_atime;
}

struct statx_timestamp
ztd::statx::btime() const noexcept
{
    return this->statx_.stx_btime;
}

struct statx_timestamp
ztd::statx::ctime() const noexcept
{
    return this->statx_.stx_ctime;
}

struct statx_timestamp
ztd::statx::mtime() const noexcept
{
    return this->statx_.stx_mtime;
}

bool
ztd::statx::is_directory() const noexcept
{
    return S_ISDIR(this->statx_.stx_mode);
}

bool
ztd::statx::is_regular_file() const noexcept
{
    return S_ISREG(this->statx_.stx_mode);
}

bool
ztd::statx::is_symlink() const noexcept
{
    return S_ISLNK(this->statx_.stx_mode);
}

bool
ztd::statx::is_socket() const noexcept
{
    return S_ISSOCK(this->statx_.stx_mode);
}

bool
ztd::statx::is_fifo() const noexcept
{
    return S_ISFIFO(this->statx_.stx_mode);
}

bool
ztd::statx::is_block_file() const noexcept
{
    return S_ISBLK(this->statx_.stx_mode);
}

bool
ztd::statx::is_character_file() const noexcept
{
    return S_ISCHR(this->statx_.stx_mode);
}

bool
ztd::statx::is_other() const noexcept
{
    return (!this->is_directory() && !this->is_regular_file() && !this->is_symlink());
}

bool
ztd::statx::is_compressed() const noexcept
{
    return (this->statx_.stx_attributes_mask & STATX_ATTR_COMPRESSED) != 0;
}

bool
ztd::statx::is_immutable() const noexcept
{
    return (this->statx_.stx_attributes_mask & STATX_ATTR_IMMUTABLE) != 0;
}

bool
ztd::statx::is_append() const noexcept
{
    return (this->statx_.stx_attributes_mask & STATX_ATTR_APPEND) != 0;
}

bool
ztd::statx::is_nodump() const noexcept
{
    return (this->statx_.stx_attributes_mask & STATX_ATTR_NODUMP) != 0;
}

bool
ztd::statx::is_encrypted() const noexcept
{
    return (this->statx_.stx_attributes_mask & STATX_ATTR_ENCRYPTED) != 0;
}

bool
ztd::statx::is_verity() const noexcept
{
    return (this->statx_.stx_attributes_mask & STATX_ATTR_VERITY) != 0;
}

bool
ztd::statx::is_dax() const noexcept
{
    return (this->statx_.stx_attributes_mask & STATX_ATTR_DAX) != 0;
}
