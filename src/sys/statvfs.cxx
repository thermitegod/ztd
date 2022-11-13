/**
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

#include <sys/types.h>
#include <sys/statvfs.h>
// #include <errno.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sys/statvfs.hxx"

// only need to support statvfs(), statfs() and fstatfs() are deprecated
// https://man7.org/linux/man-pages/man2/statfs.2.html

ztd::statvfs::statvfs(std::string_view path) noexcept
{
    this->valid = (::statvfs(path.data(), &this->fs_stat) == 0);
    if (this->valid)
        this->populate();
}

ztd::statvfs::statvfs(int fd) noexcept
{
    this->valid = (::fstatvfs(fd, &this->fs_stat) == 0);
    if (this->valid)
        this->populate();
}

bool
ztd::statvfs::is_valid() const noexcept
{
    return this->valid;
}

void
ztd::statvfs::populate() noexcept
{
    this->bsize = this->fs_stat.f_bsize;
    this->frsize = this->fs_stat.f_frsize;
    this->blocks = this->fs_stat.f_blocks;
    this->bfree = this->fs_stat.f_bfree;
    this->bavail = this->fs_stat.f_bavail;
    this->files = this->fs_stat.f_files;
    this->ffree = this->fs_stat.f_ffree;
    this->favail = this->fs_stat.f_favail;
    this->fsid = this->fs_stat.f_fsid;
    this->flag = this->fs_stat.f_flag;
    this->namemax = this->fs_stat.f_namemax;
}
