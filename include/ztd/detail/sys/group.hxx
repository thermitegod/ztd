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

#include <string>
#include <string_view>

#include <format>

#include <vector>

#include <system_error>

#include <cerrno>

#include <grp.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>

namespace ztd
{
struct group
{
    group() = delete;

    group(const gid_t gid)
    {
        struct ::group gr{};
        char buf[4096];
        const auto ret = getgrgid_r(gid, &gr, buf, sizeof(buf), &this->result_);
        if (this->result_ == nullptr)
        {
            if (ret == 0)
            {
                throw std::runtime_error(std::format("Could not find uid in /etc/group '{}'", gid));
            }
            else
            {
                throw std::system_error(errno, std::generic_category(), "getgrgid_r failed");
            }
        }
    }

    group(const gid_t gid, std::error_code& ec) noexcept
    {
        struct ::group gr{};
        char buf[4096];
        const auto ret = getgrgid_r(gid, &gr, buf, sizeof(buf), &this->result_);
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

    group(const std::string_view name)
    {
        struct ::group gr{};
        char buf[4096];
        const auto ret = getgrnam_r(name.data(), &gr, buf, sizeof(buf), &this->result_);
        if (this->result_ == nullptr)
        {
            if (ret == 0)
            {
                throw std::runtime_error(std::format("Could not find group name in /etc/group '{}'", name));
            }
            else
            {
                throw std::system_error(errno, std::generic_category(), "getgrgid_r failed");
            }
        }
    }

    group(const std::string_view name, std::error_code& ec) noexcept
    {
        struct ::group gr{};
        char buf[4096];
        const auto ret = getgrnam_r(name.data(), &gr, buf, sizeof(buf), &this->result_);
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

    /**
     * group name
     */
    [[nodiscard]] std::string
    name() const noexcept
    {
        if (this->result_->gr_name != nullptr)
        {
            return this->result_->gr_name;
        }
        return std::format("{}", this->result_->gr_gid);
    }

    /**
     * group password
     */
    [[nodiscard]] std::string
    password() const noexcept
    {
        return this->result_->gr_passwd;
    }

    /**
     * group ID
     */
    [[nodiscard]] gid_t
    gid() const noexcept
    {
        return this->result_->gr_gid;
    }

    /**
     * group members
     */
    [[nodiscard]] std::vector<std::string>
    members() const noexcept
    {
        std::vector<std::string> members;
        for (char** member = this->result_->gr_mem; *member != nullptr; ++member)
        {
            members.emplace_back(*member);
        }
        return members;
    }

  private:
    struct ::group* result_{nullptr};
};
} // namespace ztd
