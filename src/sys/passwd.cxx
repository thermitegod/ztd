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

#include <format>

#include <pwd.h>

#include <sys/types.h>

#include "ztd/internal/sys/passwd.hxx"

ztd::passwd::passwd(uid_t uid) noexcept
{
    this->pw = ::getpwuid(uid);
}

ztd::passwd::passwd(const std::string_view name) noexcept
{
    this->pw = ::getpwnam(name.data());
}

const std::string
ztd::passwd::name() const noexcept
{
    if (this->pw->pw_name != nullptr)
    {
        return this->pw->pw_name;
    }
    return std::format("{}", this->pw->pw_uid);
}

const std::string
ztd::passwd::password() const noexcept
{
    return this->pw->pw_passwd;
}

uid_t
ztd::passwd::uid() const noexcept
{
    return this->pw->pw_uid;
}

gid_t
ztd::passwd::gid() const noexcept
{
    return this->pw->pw_gid;
}

const std::string
ztd::passwd::gecos() const noexcept
{
    return this->pw->pw_gecos;
}

const std::string
ztd::passwd::home() const noexcept
{
    return this->pw->pw_dir;
}

const std::string
ztd::passwd::shell() const noexcept
{
    return this->pw->pw_shell;
}
