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

#include <string>

#include <vector>

#include <fmt/format.h>

#include <grp.h>

#include <sys/types.h>

#include "ztd/internal/sys/group.hxx"

ztd::group::group(gid_t gid) noexcept
{
    this->gr = ::getgrgid(gid);
}

ztd::group::group(std::string_view name) noexcept
{
    this->gr = ::getgrnam(name.data());
}

const std::string
ztd::group::name() const noexcept
{
    if (this->gr->gr_name != nullptr)
    {
        return this->gr->gr_name;
    }
    return fmt::format("{}", this->gr->gr_gid);
}

const std::string
ztd::group::password() const noexcept
{
    return this->gr->gr_passwd;
}

gid_t
ztd::group::gid() const noexcept
{
    return this->gr->gr_gid;
}

const std::vector<std::string>
ztd::group::members() const noexcept
{
    std::vector<std::string> members;
    for (char** member = this->gr->gr_mem; *member != nullptr; ++member)
    {
        members.emplace_back(*member);
    }
    return members;
}
