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
#include <sys/statvfs.h>

#include <sys/sysmacros.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sys/statvfs.hxx"

ztd::statvfs::statvfs(const std::filesystem::path& path) noexcept
{
    this->valid_ = (::statvfs(path.c_str(), &this->stat_) == 0);
}

ztd::statvfs::statvfs(int fd) noexcept
{
    this->valid_ = (::fstatvfs(fd, &this->stat_) == 0);
}

u64
ztd::statvfs::bsize() const noexcept
{
    return this->stat_.f_bsize;
}

u64
ztd::statvfs::frsize() const noexcept
{
    return this->stat_.f_frsize;
}

fsblkcnt_t
ztd::statvfs::blocks() const noexcept
{
    return this->stat_.f_blocks;
}

fsblkcnt_t
ztd::statvfs::bfree() const noexcept
{
    return this->stat_.f_bfree;
}

fsblkcnt_t
ztd::statvfs::bavail() const noexcept
{
    return this->stat_.f_bavail;
}

fsfilcnt_t
ztd::statvfs::files() const noexcept
{
    return this->stat_.f_files;
}

fsfilcnt_t
ztd::statvfs::ffree() const noexcept
{
    return this->stat_.f_ffree;
}

fsfilcnt_t
ztd::statvfs::favail() const noexcept
{
    return this->stat_.f_favail;
}

u64
ztd::statvfs::fsid() const noexcept
{
    return this->stat_.f_fsid;
}

u64
ztd::statvfs::flag() const noexcept
{
    return this->stat_.f_flag;
}

u64
ztd::statvfs::namemax() const noexcept
{
    return this->stat_.f_namemax;
}
