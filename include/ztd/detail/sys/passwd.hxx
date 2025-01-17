/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include <expected>
#include <filesystem>
#include <format>
#include <string>
#include <string_view>
#include <system_error>

#include <cerrno>

#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

namespace ztd
{
struct passwd
{
    explicit passwd() = delete;

    explicit passwd(const uid_t uid)
    {
        struct ::passwd pw{};
        char buf[4096];
        const auto ret = getpwuid_r(uid, &pw, buf, sizeof(buf), &this->result_);
        if (this->result_ == nullptr)
        {
            if (ret == 0)
            {
                throw std::runtime_error(
                    std::format("Could not find uid in /etc/passwd '{}'", uid));
            }
            else
            {
                throw std::system_error(errno, std::generic_category(), "getpwuid_r failed");
            }
        }
    }

    explicit passwd(const uid_t uid, std::error_code& ec) noexcept
    {
        struct ::passwd pw{};
        char buf[4096];
        const auto ret = getpwuid_r(uid, &pw, buf, sizeof(buf), &this->result_);
        if (this->result_ == nullptr)
        {
            if (ret == 0)
            {
                ec = std::make_error_code(std::errc::invalid_argument);
            }
            else
            {
                ec = std::make_error_code(std::errc(errno));
            }
        }
    }

    explicit passwd(const std::string_view name)
    {
        struct ::passwd pw{};
        char buf[4096];
        const auto ret = getpwnam_r(name.data(), &pw, buf, sizeof(buf), &this->result_);
        if (this->result_ == nullptr)
        {
            if (ret == 0)
            {
                throw std::runtime_error(
                    std::format("Could not find user name in /etc/passwd '{}'", name));
            }
            else
            {
                throw std::system_error(errno, std::generic_category(), "getpwuid_r failed");
            }
        }
    }

    explicit passwd(const std::string_view name, std::error_code& ec) noexcept
    {
        struct ::passwd pw{};
        char buf[4096];
        const auto ret = getpwnam_r(name.data(), &pw, buf, sizeof(buf), &this->result_);
        if (this->result_ == nullptr)
        {
            if (ret == 0)
            {
                ec = std::make_error_code(std::errc::invalid_argument);
            }
            else
            {
                ec = std::make_error_code(std::errc(errno));
            }
        }
    }

    [[nodiscard]] static std::expected<passwd, std::error_code>
    create(const gid_t gid) noexcept
    {
        std::error_code ec;
        auto p = passwd(gid, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return p;
    }

    [[nodiscard]] static std::expected<passwd, std::error_code>
    create(const std::string_view name) noexcept
    {
        std::error_code ec;
        auto p = passwd(name, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return p;
    }

    /**
     * username
     */
    [[nodiscard]] std::string
    name() const noexcept
    {
        if (this->result_->pw_name != nullptr)
        {
            return this->result_->pw_name;
        }
        return std::format("{}", this->result_->pw_uid);
    }

    /**
     * user password
     */
    [[nodiscard]] std::string
    password() const noexcept
    {
        return this->result_->pw_passwd;
    }

    /**
     * user ID
     */
    [[nodiscard]] uid_t
    uid() const noexcept
    {
        return this->result_->pw_uid;
    }

    /**
     * group ID
     */
    [[nodiscard]] gid_t
    gid() const noexcept
    {
        return this->result_->pw_gid;
    }

    /**
     * user information
     */
    [[nodiscard]] std::string
    gecos() const noexcept
    {
        return this->result_->pw_gecos;
    }

    /**
     * home directory
     */
    [[nodiscard]] std::filesystem::path
    home() const noexcept
    {
        return this->result_->pw_dir;
    }

    /**
     * shell program
     */
    [[nodiscard]] std::string
    shell() const noexcept
    {
        return this->result_->pw_shell;
    }

  private:
    struct ::passwd* result_{nullptr};
};
} // namespace ztd
