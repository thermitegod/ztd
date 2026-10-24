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
#include <memory>
#include <string_view>
#include <system_error>
#include <vector>

#include <fcntl.h>
#include <grp.h>
#include <sys/types.h>
#include <unistd.h>

namespace ztd
{
class group final
{
  public:
    group() = delete;
    group(const group&) = delete;
    group& operator=(const group&) = delete;
    group(group&&) noexcept = default;
    group& operator=(group&&) noexcept = default;
    ~group() = default;

    [[nodiscard]] static std::expected<group, std::error_code>
    create(gid_t gid) noexcept
    {
        std::error_code ec;
        auto g = group(gid, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return g;
    }

    [[nodiscard]] static std::expected<group, std::error_code>
    create(std::string_view name) noexcept
    {
        std::error_code ec;
        auto g = group(name, ec);
        if (ec)
        {
            return std::unexpected(ec);
        }
        return g;
    }

    /**
     * group name
     */
    [[nodiscard]] std::string_view
    name() const noexcept
    {
        return result_->gr_name;
    }

    /**
     * group password
     */
    [[nodiscard]] std::string_view
    password() const noexcept
    {
        return result_->gr_passwd;
    }

    /**
     * group ID
     */
    [[nodiscard]] gid_t
    gid() const noexcept
    {
        return result_->gr_gid;
    }

    /**
     * group members
     */
    [[nodiscard]] std::vector<std::string_view>
    members() const noexcept
    {
        std::vector<std::string_view> members;
        for (char** member = result_->gr_mem; *member != nullptr; ++member)
        {
            members.emplace_back(*member);
        }
        return members;
    }

  private:
    explicit group(gid_t gid, std::error_code& ec) noexcept
    {
        try
        {
            buffer_.resize(4096);
            result_ = std::make_unique<struct ::group>();

            struct ::group* tmp = nullptr;
            const auto ret = getgrgid_r(gid, result_.get(), buffer_.data(), buffer_.size(), &tmp);

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

    explicit group(std::string_view name, std::error_code& ec) noexcept
    {
        try
        {
            buffer_.resize(4096);
            result_ = std::make_unique<struct ::group>();

            struct ::group* tmp = nullptr;
            const auto ret =
                getgrnam_r(name.data(), result_.get(), buffer_.data(), buffer_.size(), &tmp);

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

    std::unique_ptr<struct ::group> result_{nullptr};
    std::vector<char> buffer_;
};
} // namespace ztd
