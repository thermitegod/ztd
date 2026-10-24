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
#include <memory>
#include <string_view>
#include <system_error>
#include <vector>

#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

namespace ztd
{
class passwd final
{
  public:
    passwd() = delete;
    passwd(const passwd&) = delete;
    passwd& operator=(const passwd&) = delete;
    passwd(passwd&&) noexcept = default;
    passwd& operator=(passwd&&) noexcept = default;
    ~passwd() = default;

    [[nodiscard]] static std::expected<passwd, std::error_code>
    create(uid_t uid) noexcept
    {
        std::error_code ec;
        auto p = passwd(uid, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return p;
    }

    [[nodiscard]] static std::expected<passwd, std::error_code>
    create(std::string_view name) noexcept
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
    [[nodiscard]] std::string_view
    name() const noexcept
    {
        return result_->pw_name;
    }

    /**
     * user password
     */
    [[nodiscard]] std::string_view
    password() const noexcept
    {
        return result_->pw_passwd;
    }

    /**
     * user ID
     */
    [[nodiscard]] uid_t
    uid() const noexcept
    {
        return result_->pw_uid;
    }

    /**
     * group ID
     */
    [[nodiscard]] gid_t
    gid() const noexcept
    {
        return result_->pw_gid;
    }

    /**
     * user information
     */
    [[nodiscard]] std::string_view
    gecos() const noexcept
    {
        return result_->pw_gecos;
    }

    /**
     * home directory
     */
    [[nodiscard]] std::filesystem::path
    home() const noexcept
    {
        return result_->pw_dir;
    }

    /**
     * shell program
     */
    [[nodiscard]] std::string_view
    shell() const noexcept
    {
        return result_->pw_shell;
    }

  private:
    explicit passwd(uid_t uid, std::error_code& ec) noexcept
    {
        try
        {
            buffer_.resize(4096);
            result_ = std::make_unique<struct ::passwd>();

            struct ::passwd* tmp = nullptr;
            const auto ret = getpwuid_r(uid, result_.get(), buffer_.data(), buffer_.size(), &tmp);

            if (tmp == nullptr)
            {
                if (ret == 0)
                {
                    ec = std::make_error_code(std::errc::invalid_argument);
                }
                else
                {
                    ec = std::error_code(ret, std::generic_category());
                }
            }
        }
        catch (const std::bad_alloc&)
        {
            ec = std::make_error_code(std::errc::not_enough_memory);
        }
        catch (const std::length_error&)
        {
            ec = std::make_error_code(std::errc::value_too_large);
        }
    }

    explicit passwd(std::string_view name, std::error_code& ec) noexcept
    {
        try
        {
            buffer_.resize(4096);
            result_ = std::make_unique<struct ::passwd>();

            struct ::passwd* tmp = nullptr;
            const auto ret =
                getpwnam_r(name.data(), result_.get(), buffer_.data(), buffer_.size(), &tmp);

            if (tmp == nullptr)
            {
                if (ret == 0)
                {
                    ec = std::make_error_code(std::errc::invalid_argument);
                }
                else
                {
                    ec = std::error_code(ret, std::generic_category());
                }
            }
        }
        catch (const std::bad_alloc&)
        {
            ec = std::make_error_code(std::errc::not_enough_memory);
        }
        catch (const std::length_error&)
        {
            ec = std::make_error_code(std::errc::value_too_large);
        }
    }

    std::unique_ptr<struct ::passwd> result_{nullptr};
    std::vector<char> buffer_;
};
} // namespace ztd
