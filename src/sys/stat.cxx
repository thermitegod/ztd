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

#include <string_view>

#include <chrono>

#include <sys/stat.h>
// #include <errno.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sys/stat.hxx"

/**
 * ztd::stat
 */

ztd::stat::stat(const std::string_view path) noexcept
{
    this->valid = (::stat(path.data(), &this->file_stat) == 0);
}

ztd::stat::stat(int fd) noexcept
{
    this->valid = (::fstat(fd, &this->file_stat) == 0);
}

ztd::stat::stat(int dirfd, const std::string_view pathname, int flags) noexcept
{
    this->valid = (::fstatat(dirfd, pathname.data(), &this->file_stat, flags) == 0);
}

bool
ztd::stat::is_valid() const noexcept
{
    return this->valid;
}

bool
ztd::stat::exists() const noexcept
{
    return this->valid;
}

dev_t
ztd::stat::dev() const noexcept
{
    return this->file_stat.st_dev;
}

ino_t
ztd::stat::ino() const noexcept
{
    return this->file_stat.st_ino;
}

mode_t
ztd::stat::mode() const noexcept
{
    return this->file_stat.st_mode;
}

nlink_t
ztd::stat::nlink() const noexcept
{
    return this->file_stat.st_nlink;
}

uid_t
ztd::stat::uid() const noexcept
{
    return this->file_stat.st_uid;
}

gid_t
ztd::stat::gid() const noexcept
{
    return this->file_stat.st_gid;
}

dev_t
ztd::stat::rdev() const noexcept
{
    return this->file_stat.st_rdev;
}

off_t
ztd::stat::size() const noexcept
{
    return this->file_stat.st_size;
}

blksize_t
ztd::stat::blksize() const noexcept
{
    return this->file_stat.st_blksize;
}

blkcnt_t
ztd::stat::blocks() const noexcept
{
    return this->file_stat.st_blocks;
}

struct timespec
ztd::stat::atim() const noexcept
{
    return this->file_stat.st_atim;
}

struct timespec
ztd::stat::mtim() const noexcept
{
    return this->file_stat.st_mtim;
}

struct timespec
ztd::stat::ctim() const noexcept
{
    return this->file_stat.st_ctim;
}

time_t
ztd::stat::atime() const noexcept
{
    return this->file_stat.st_atim.tv_sec;
}

time_t
ztd::stat::mtime() const noexcept
{
    return this->file_stat.st_mtim.tv_sec;
}

time_t
ztd::stat::ctime() const noexcept
{
    return this->file_stat.st_ctim.tv_sec;
}

bool
ztd::stat::is_directory() const noexcept
{
    return S_ISDIR(this->file_stat.st_mode);
}

bool
ztd::stat::is_regular_file() const noexcept
{
    return S_ISREG(this->file_stat.st_mode);
}

bool
ztd::stat::is_symlink() const noexcept
{
    return S_ISLNK(this->file_stat.st_mode);
}

bool
ztd::stat::is_socket() const noexcept
{
    return S_ISSOCK(this->file_stat.st_mode);
}

bool
ztd::stat::is_fifo() const noexcept
{
    return S_ISFIFO(this->file_stat.st_mode);
}

bool
ztd::stat::is_block_file() const noexcept
{
    return S_ISBLK(this->file_stat.st_mode);
}

bool
ztd::stat::is_character_file() const noexcept
{
    return S_ISCHR(this->file_stat.st_mode);
}

bool
ztd::stat::is_other() const noexcept
{
    return (!this->is_directory() && !this->is_regular_file() && !this->is_symlink());
}

/**
 * ztd::lstat
 */

ztd::lstat::lstat(const std::string_view path) noexcept
{
    this->valid = (::lstat(path.data(), &this->file_stat) == 0);
}
