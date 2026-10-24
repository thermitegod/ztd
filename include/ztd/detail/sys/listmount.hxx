/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <cstddef>
#include <expected>
#include <new>
#include <stdexcept>
#include <system_error>
#include <utility>
#include <vector>

#include <cerrno>
#include <cstdint>

#include <linux/mount.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "statmount.hxx"

namespace ztd
{
class listmount
{
  public:
    listmount() = delete;
    listmount(const listmount&) = default;
    listmount(listmount&&) noexcept = default;
    listmount& operator=(const listmount&) = default;
    listmount& operator=(listmount&&) noexcept = default;
    ~listmount() = default;

    [[nodiscard]] static std::expected<listmount, std::error_code>
    create(const std::uint64_t parent_mount_id = LSMT_ROOT) noexcept
    {
        constexpr std::size_t initial_capacity = 64uz;
        // constexpr std::size_t batch_size = 2uz;
        constexpr std::size_t batch_size = 64uz;

        try
        {
            std::vector<std::uint64_t> ids;
            ids.reserve(initial_capacity);

            std::vector<std::uint64_t> batch(batch_size);

            struct mnt_id_req req{};
            req.size = sizeof(req);
            req.mnt_id = parent_mount_id;
            req.param = 0;

            for (;;)
            {
                const auto result = syscall(SYS_listmount, &req, batch.data(), batch.size(), 0uz);

                if (result == -1)
                {
                    return std::unexpected(std::error_code(errno, std::generic_category()));
                }

                if (static_cast<std::size_t>(result) > batch.size())
                {
                    return std::unexpected(std::make_error_code(std::errc::bad_message));
                }

                const auto count = static_cast<std::size_t>(result);
                if (count == 0uz)
                {
                    break;
                }

                ids.insert(ids.end(),
                           batch.begin(),
                           batch.begin() + static_cast<std::ptrdiff_t>(count));

                // uses pagination, continue after the last mount id
                req.param = batch[count - 1uz];
            }

            return listmount(std::move(ids));
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

    [[nodiscard]] std::size_t
    size() const noexcept
    {
        return ids_.size();
    }

    [[nodiscard]] bool
    empty() const noexcept
    {
        return ids_.empty();
    }

    [[nodiscard]] const std::uint64_t&
    front() const noexcept
    {
        return ids_.front();
    }

    [[nodiscard]] const std::uint64_t&
    back() const noexcept
    {
        return ids_.back();
    }

    [[nodiscard]] auto
    begin() const noexcept
    {
        return ids_.begin();
    }

    [[nodiscard]] auto
    end() const noexcept
    {
        return ids_.end();
    }

    [[nodiscard]] std::vector<ztd::statmount>
    statmounts() const noexcept
    {
        std::vector<ztd::statmount> statmounts;
        for (const auto id : ids_)
        {
            const auto result = ztd::statmount::create(id);
            if (result)
            {
                statmounts.emplace_back(*result);
            }
        }
        return statmounts;
    }

  private:
    explicit listmount(std::vector<std::uint64_t>&& ids) noexcept : ids_(std::move(ids)) {}

    std::vector<std::uint64_t> ids_;
};
} // namespace ztd
