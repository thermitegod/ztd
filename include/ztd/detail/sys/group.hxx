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

#include <algorithm>
#include <expected>
#include <memory>
#include <new>
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
        constexpr std::size_t buffer_size = 1024uz;
        constexpr std::size_t max_buffer_size = 1024uz * 1024uz;

        try
        {
            auto result = std::make_unique<struct ::group>();
            std::vector<char> buffer(buffer_size);

            for (;;)
            {
                struct ::group* tmp = nullptr;

                const auto ret = getgrgid_r(gid, result.get(), buffer.data(), buffer.size(), &tmp);

                if (std::errc{ret} == std::errc::result_out_of_range)
                {
                    if (buffer.size() >= max_buffer_size)
                    {
                        return std::unexpected(
                            std::make_error_code(std::errc::result_out_of_range));
                    }

                    buffer.resize(std::min(buffer.size() * 2, max_buffer_size));
                    continue;
                }

                if (ret != 0)
                {
                    return std::unexpected(std::error_code(ret, std::generic_category()));
                }

                if (tmp == nullptr)
                {
                    return std::unexpected(std::make_error_code(std::errc::bad_message));
                }

                return group(std::move(result), std::move(buffer));
            }
        }
        catch (const std::bad_alloc&)
        {
            return std::unexpected(std::make_error_code(std::errc::not_enough_memory));
        }
        catch (const std::length_error&)
        {
            return std::unexpected(std::make_error_code(std::errc::value_too_large));
        }
    }

    [[nodiscard]] static std::expected<group, std::error_code>
    create(std::string_view name) noexcept
    {
        constexpr std::size_t buffer_size = 1024uz;
        constexpr std::size_t max_buffer_size = 1024uz * 1024uz;

        try
        {
            auto result = std::make_unique<struct ::group>();
            std::vector<char> buffer(buffer_size);

            for (;;)
            {
                struct ::group* tmp = nullptr;

                const auto ret =
                    getgrnam_r(name.data(), result.get(), buffer.data(), buffer.size(), &tmp);

                if (std::errc{ret} == std::errc::result_out_of_range)
                {
                    if (buffer.size() >= max_buffer_size)
                    {
                        return std::unexpected(
                            std::make_error_code(std::errc::result_out_of_range));
                    }

                    buffer.resize(std::min(buffer.size() * 2, max_buffer_size));
                    continue;
                }

                if (ret != 0)
                {
                    return std::unexpected(std::error_code(ret, std::generic_category()));
                }

                if (tmp == nullptr)
                {
                    return std::unexpected(std::make_error_code(std::errc::bad_message));
                }

                return group(std::move(result), std::move(buffer));
            }
        }
        catch (const std::bad_alloc&)
        {
            return std::unexpected(std::make_error_code(std::errc::not_enough_memory));
        }
        catch (const std::length_error&)
        {
            return std::unexpected(std::make_error_code(std::errc::value_too_large));
        }
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

        if (!result_ || result_->gr_mem == nullptr)
        {
            return members;
        }

        for (char** member = result_->gr_mem; *member != nullptr; ++member)
        {
            members.emplace_back(*member);
        }
        return members;
    }

  private:
    explicit group(std::unique_ptr<struct ::group>&& result, std::vector<char>&& buffer) noexcept
        : result_(std::move(result)), buffer_(std::move(buffer))
    {
    }

    std::unique_ptr<struct ::group> result_{nullptr};
    std::vector<char> buffer_;
};
} // namespace ztd
