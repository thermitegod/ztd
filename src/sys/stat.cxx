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

#include <sys/stat.h>
// #include <errno.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sys/stat.hxx"

/**
 * ztd::stat
 */

ztd::stat::stat(std::string_view path) noexcept
{
    this->valid = (::stat(path.data(), &this->file_stat) == 0);

    this->populate();
}

ztd::stat::stat(int fd) noexcept
{
    this->valid = (::fstat(fd, &this->file_stat) == 0);

    this->populate();
}

ztd::stat::stat(int dirfd, std::string_view pathname, int flags) noexcept
{
    this->valid = (::fstatat(dirfd, pathname.data(), &this->file_stat, flags) == 0);

    this->populate();
}

bool
ztd::stat::is_valid() const noexcept
{
    return this->valid;
}

bool
ztd::stat::is_directory() const noexcept
{
    return S_ISDIR(this->mode);
}

bool
ztd::stat::is_regular_file() const noexcept
{
    return S_ISREG(this->mode);
}

bool
ztd::stat::is_symlink() const noexcept
{
    return S_ISLNK(this->mode);
}

bool
ztd::stat::is_socket() const noexcept
{
    return S_ISSOCK(this->mode);
}

bool
ztd::stat::is_fifo() const noexcept
{
    return S_ISFIFO(this->mode);
}

bool
ztd::stat::is_block_file() const noexcept
{
    return S_ISBLK(this->mode);
}

bool
ztd::stat::is_character_file() const noexcept
{
    return S_ISCHR(this->mode);
}

void
ztd::stat::populate() noexcept
{
    this->dev = this->file_stat.st_dev;
    this->ino = this->file_stat.st_ino;
    this->mode = this->file_stat.st_mode;
    this->nlink = this->file_stat.st_nlink;
    this->uid = this->file_stat.st_uid;
    this->gid = this->file_stat.st_gid;
    this->rdev = this->file_stat.st_rdev;
    this->size = this->file_stat.st_size;
    this->blksize = this->file_stat.st_blksize;
    this->blocks = this->file_stat.st_blocks;

    this->atim = this->file_stat.st_atim;
    this->mtim = this->file_stat.st_mtim;
    this->ctim = this->file_stat.st_ctim;

    this->atime = this->file_stat.st_atim.tv_sec;
    this->mtime = this->file_stat.st_mtim.tv_sec;
    this->ctime = this->file_stat.st_ctim.tv_sec;
}

/**
 * ztd::lstat
 */

ztd::lstat::lstat(std::string_view path) noexcept
{
    this->valid = (::lstat(path.data(), &this->file_stat) == 0);

    this->populate();
}
