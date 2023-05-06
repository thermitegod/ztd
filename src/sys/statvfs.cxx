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

#include <filesystem>

#include <chrono>

#include <sys/types.h>
#include <sys/statvfs.h>
// #include <errno.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sys/statvfs.hxx"

// only need to support statvfs(), statfs() and fstatfs() are deprecated
// https://man7.org/linux/man-pages/man2/statfs.2.html

ztd::statvfs::statvfs(const std::filesystem::path& path) noexcept
{
    this->valid = (::statvfs(path.c_str(), &this->fs_stat) == 0);
}

ztd::statvfs::statvfs(int fd) noexcept
{
    this->valid = (::fstatvfs(fd, &this->fs_stat) == 0);
}

bool
ztd::statvfs::is_valid() const noexcept
{
    return this->valid;
}

u64
ztd::statvfs::bsize() const noexcept
{
    return this->fs_stat.f_bsize;
}

u64
ztd::statvfs::frsize() const noexcept
{
    return this->fs_stat.f_frsize;
}

fsblkcnt_t
ztd::statvfs::blocks() const noexcept
{
    return this->fs_stat.f_blocks;
}

fsblkcnt_t
ztd::statvfs::bfree() const noexcept
{
    return this->fs_stat.f_bfree;
}

fsblkcnt_t
ztd::statvfs::bavail() const noexcept
{
    return this->fs_stat.f_bavail;
}

fsfilcnt_t
ztd::statvfs::files() const noexcept
{
    return this->fs_stat.f_files;
}

fsfilcnt_t
ztd::statvfs::ffree() const noexcept
{
    return this->fs_stat.f_ffree;
}

fsfilcnt_t
ztd::statvfs::favail() const noexcept
{
    return this->fs_stat.f_favail;
}

u64
ztd::statvfs::fsid() const noexcept
{
    return this->fs_stat.f_fsid;
}

u64
ztd::statvfs::flag() const noexcept
{
    return this->fs_stat.f_flag;
}

u64
ztd::statvfs::namemax() const noexcept
{
    return this->fs_stat.f_namemax;
}
