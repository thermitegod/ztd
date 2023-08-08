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

#include "ztd/internal/sys/stat.hxx"

/**
 * ztd::stat
 */

ztd::stat::stat(const std::filesystem::path& path) noexcept
{
    this->valid_ = (::stat(path.c_str(), &this->stat_) == 0);
}

ztd::stat::stat(int fd) noexcept
{
    this->valid_ = (::fstat(fd, &this->stat_) == 0);
}

ztd::stat::stat(int dirfd, const std::filesystem::path& pathname, int flags) noexcept
{
    this->valid_ = (::fstatat(dirfd, pathname.c_str(), &this->stat_, flags) == 0);
}

u32
ztd::stat::nlink() const noexcept
{
    return this->stat_.st_nlink;
}

u32
ztd::stat::uid() const noexcept
{
    return this->stat_.st_uid;
}

u32
ztd::stat::gid() const noexcept
{
    return this->stat_.st_gid;
}

u32
ztd::stat::mode() const noexcept
{
    return this->stat_.st_mode;
}

u64
ztd::stat::ino() const noexcept
{
    return this->stat_.st_ino;
}

u64
ztd::stat::size() const noexcept
{
    return this->stat_.st_size;
}

u64
ztd::stat::size_on_disk() const noexcept
{
    // The inode block count for a file/directory is in units of
    // 512 byte blocks, not the filesystem block size.
    return this->stat_.st_blocks * S_BLKSIZE;
}

u32
ztd::stat::blksize() const noexcept
{
    return this->stat_.st_blksize;
}

u64
ztd::stat::blocks() const noexcept
{
    return this->stat_.st_blocks;
}

u64
ztd::stat::dev() const noexcept
{
    return this->stat_.st_dev;
}

u32
ztd::stat::dev_major() const noexcept
{
    return gnu_dev_major(this->stat_.st_dev);
}

u32
ztd::stat::dev_minor() const noexcept
{
    return gnu_dev_minor(this->stat_.st_dev);
}

u64
ztd::stat::rdev() const noexcept
{
    return this->stat_.st_rdev;
}

u32
ztd::stat::rdev_major() const noexcept
{
    return gnu_dev_major(this->stat_.st_rdev);
}

u32
ztd::stat::rdev_minor() const noexcept
{
    return gnu_dev_minor(this->stat_.st_rdev);
}

struct timespec
ztd::stat::atim() const noexcept
{
    return this->stat_.st_atim;
}

struct timespec
ztd::stat::ctim() const noexcept
{
    return this->stat_.st_ctim;
}

struct timespec
ztd::stat::mtim() const noexcept
{
    return this->stat_.st_mtim;
}

time_t
ztd::stat::atime() const noexcept
{
    return this->stat_.st_atim.tv_sec;
}

time_t
ztd::stat::ctime() const noexcept
{
    return this->stat_.st_ctim.tv_sec;
}

time_t
ztd::stat::mtime() const noexcept
{
    return this->stat_.st_mtim.tv_sec;
}

bool
ztd::stat::is_directory() const noexcept
{
    return S_ISDIR(this->stat_.st_mode);
}

bool
ztd::stat::is_regular_file() const noexcept
{
    return S_ISREG(this->stat_.st_mode);
}

bool
ztd::stat::is_symlink() const noexcept
{
    return S_ISLNK(this->stat_.st_mode);
}

bool
ztd::stat::is_socket() const noexcept
{
    return S_ISSOCK(this->stat_.st_mode);
}

bool
ztd::stat::is_fifo() const noexcept
{
    return S_ISFIFO(this->stat_.st_mode);
}

bool
ztd::stat::is_block_file() const noexcept
{
    return S_ISBLK(this->stat_.st_mode);
}

bool
ztd::stat::is_character_file() const noexcept
{
    return S_ISCHR(this->stat_.st_mode);
}

bool
ztd::stat::is_other() const noexcept
{
    return (!this->is_directory() && !this->is_regular_file() && !this->is_symlink());
}

/**
 * ztd::lstat
 */

ztd::lstat::lstat(const std::filesystem::path& path) noexcept
{
    this->valid_ = (::lstat(path.c_str(), &this->stat_) == 0);
}
