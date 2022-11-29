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

#include <fmt/format.h>

#include <pwd.h>

#include <sys/types.h>

#include "ztd/internal/sys/passwd.hxx"

ztd::passwd::passwd(uid_t uid) noexcept
{
    this->pw = ::getpwuid(uid);

    this->populate();
}

ztd::passwd::passwd(std::string_view name) noexcept
{
    this->pw = ::getpwnam(name.data());

    this->populate();
}

void
ztd::passwd::populate() noexcept
{
    if (!this->pw)
        return;

    if (this->pw->pw_name)
        this->name = this->pw->pw_name;
    else
        this->name = fmt::format("{}", this->uid);

    if (this->pw->pw_passwd)
        this->password = this->pw->pw_passwd;

    this->uid = this->pw->pw_uid;
    this->gid = this->pw->pw_gid;

    if (this->pw->pw_gecos)
        this->gecos = this->pw->pw_gecos;

    if (this->pw->pw_dir)
        this->dir = this->pw->pw_dir;

    if (this->pw->pw_shell)
        this->shell = this->pw->pw_shell;
}
