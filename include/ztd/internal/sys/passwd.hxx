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

#pragma once

#include <string>
#include <string_view>

#include <filesystem>

#include <format>

#include <pwd.h>
#include <sys/types.h>

namespace ztd
{
struct passwd
{
  public:
    passwd() = delete;
    passwd(uid_t uid) noexcept { this->pw = ::getpwuid(uid); }

    passwd(const std::string_view name) noexcept { this->pw = ::getpwnam(name.data()); }

    /**
     * username
     */
    [[nodiscard]] const std::string
    name() const noexcept
    {
        if (this->pw->pw_name != nullptr)
        {
            return this->pw->pw_name;
        }
        return std::format("{}", this->pw->pw_uid);
    }

    /**
     * user password
     */
    [[nodiscard]] const std::string
    password() const noexcept
    {
        return this->pw->pw_passwd;
    }

    /**
     * user ID
     */
    [[nodiscard]] uid_t
    uid() const noexcept
    {
        return this->pw->pw_uid;
    }

    /**
     * group ID
     */
    [[nodiscard]] gid_t
    gid() const noexcept
    {
        return this->pw->pw_gid;
    }

    /**
     * user information
     */
    [[nodiscard]] const std::string
    gecos() const noexcept
    {
        return this->pw->pw_gecos;
    }

    /**
     * home directory
     */
    [[nodiscard]] const std::filesystem::path
    home() const noexcept
    {
        return this->pw->pw_dir;
    }

    /**
     * shell program
     */
    [[nodiscard]] const std::string
    shell() const noexcept
    {
        return this->pw->pw_shell;
    }

  private:
    struct ::passwd* pw = {};
};
} // namespace ztd
