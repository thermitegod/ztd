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

#include <string>

#include <vector>

#include <fmt/format.h>

#include <grp.h>

#include <sys/types.h>

#include "ztd/internal/sys/group.hxx"

ztd::group::group(gid_t gid) noexcept
{
    this->gr = ::getgrgid(gid);

    this->populate();
}

ztd::group::group(std::string_view name) noexcept
{
    this->gr = ::getgrnam(name.data());

    this->populate();
}

void
ztd::group::populate() noexcept
{
    if (!this->gr)
        return;

    if (this->gr->gr_name)
        this->name = this->gr->gr_name;
    else
        this->name = fmt::format("{}", this->gid);

    if (this->gr->gr_passwd)
        this->password = this->gr->gr_passwd;

    this->gid = this->gr->gr_gid;

    for (char** member = this->gr->gr_mem; *member != nullptr; ++member)
    {
        this->members.emplace_back(*member);
    }
}
