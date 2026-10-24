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

#include <algorithm>
#include <cstddef>
#include <expected>
#include <new>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include <cerrno>
#include <cstdint>
#include <cstring>

#include <linux/mount.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <sys/sysmacros.h>
#include <unistd.h>

namespace ztd
{
class statmount
{
  public:
    statmount() = delete;
    statmount(const statmount&) = default;
    statmount(statmount&&) noexcept = default;
    statmount& operator=(const statmount&) = default;
    statmount& operator=(statmount&&) noexcept = default;
    ~statmount() = default;

    [[nodiscard]] static std::expected<statmount, std::error_code>
    create(const std::uint64_t mount_id) noexcept
    {
        constexpr std::uint64_t mask =
            STATMOUNT_SB_BASIC | STATMOUNT_MNT_BASIC | STATMOUNT_PROPAGATE_FROM |
            STATMOUNT_MNT_NS_ID | STATMOUNT_MNT_OPTS | STATMOUNT_FS_SUBTYPE | STATMOUNT_SB_SOURCE |
            STATMOUNT_MNT_ROOT | STATMOUNT_MNT_POINT | STATMOUNT_FS_TYPE;

        return create(mount_id, mask);
    }

    [[nodiscard]] static std::expected<statmount, std::error_code>
    create(const std::uint64_t mount_id, const std::uint64_t mask) noexcept
    {
        constexpr std::size_t buffer_size = 64uz * 1024uz;
        constexpr std::size_t max_buffer_size = 1024uz * 1024uz;
        constexpr auto fixed_size = offsetof(struct ::statmount, str);

        try
        {
            std::vector<std::byte> buffer(buffer_size);

            struct mnt_id_req req{};
            req.size = sizeof(req);
            req.mnt_id = mount_id;
            req.param = mask;

            for (;;)
            {
                const auto result = syscall(SYS_statmount,
                                            &req,
                                            reinterpret_cast<struct ::statmount*>(buffer.data()),
                                            buffer.size(),
                                            0uz);

                if (result == -1)
                {
                    const auto ec = std::error_code(errno, std::generic_category());

                    if (ec != std::errc::value_too_large || buffer.size() >= max_buffer_size)
                    {
                        return std::unexpected(ec);
                    }

                    buffer.resize(std::min(buffer.size() * 2, max_buffer_size));

                    continue;
                }

                const auto* response = reinterpret_cast<const struct ::statmount*>(buffer.data());
                if (response->size < fixed_size || response->size > buffer.size())
                {
                    return std::unexpected(std::make_error_code(std::errc::bad_message));
                }

                return statmount(std::move(buffer));
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

    // Mount identification

    [[nodiscard]] std::uint64_t
    mount_id() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_id : 0;
    }

    [[nodiscard]] std::uint64_t
    mount_parent_id() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_parent_id : 0;
    }

    [[nodiscard]] std::uint32_t
    mount_id_old() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_id_old : 0;
    }

    [[nodiscard]] std::uint32_t
    mount_parent_id_old() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_parent_id_old : 0;
    }

    [[nodiscard]] std::uint64_t
    mount_ns_id() const noexcept
    {
        return has_mask(STATMOUNT_MNT_NS_ID) ? data().mnt_ns_id : 0;
    }

    // Superblock information

    [[nodiscard]] dev_t
    dev() const noexcept
    {
        return gnu_dev_makedev(dev_major(), dev_minor());
    }

    [[nodiscard]] std::uint32_t
    dev_major() const noexcept
    {
        return has_mask(STATMOUNT_SB_BASIC) ? data().sb_dev_major : 0;
    }

    [[nodiscard]] std::uint32_t
    dev_minor() const noexcept
    {
        return has_mask(STATMOUNT_SB_BASIC) ? data().sb_dev_minor : 0;
    }

    [[nodiscard]] std::uint64_t
    magic() const noexcept
    {
        return has_mask(STATMOUNT_SB_BASIC) ? data().sb_magic : 0;
    }

    [[nodiscard]] std::uint32_t
    sb_flags() const noexcept
    {
        return has_mask(STATMOUNT_SB_BASIC) ? data().sb_flags : 0;
    }

    // Mount attributes and propagation

    [[nodiscard]] std::uint64_t
    mount_attr() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_attr : 0;
    }

    [[nodiscard]] std::uint64_t
    mount_propagation() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_propagation : 0;
    }

    [[nodiscard]] std::uint64_t
    mount_peer_group() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_peer_group : 0;
    }

    [[nodiscard]] std::uint64_t
    mount_master() const noexcept
    {
        return has_mask(STATMOUNT_MNT_BASIC) ? data().mnt_master : 0;
    }

    [[nodiscard]] std::uint64_t
    propagate_from() const noexcept
    {
        return has_mask(STATMOUNT_PROPAGATE_FROM) ? data().propagate_from : 0;
    }

    // Filesystem

    [[nodiscard]] std::string_view
    root() const noexcept
    {
        return has_mask(STATMOUNT_MNT_ROOT) ? string_at(data().mnt_root) : std::string_view{};
    }

    [[nodiscard]] std::string_view
    mount_point() const noexcept
    {
        return has_mask(STATMOUNT_MNT_POINT) ? string_at(data().mnt_point) : std::string_view{};
    }

    [[nodiscard]] std::string_view
    fs_type() const noexcept
    {
        return has_mask(STATMOUNT_FS_TYPE) ? string_at(data().fs_type) : std::string_view{};
    }

    [[nodiscard]] std::string_view
    fs_subtype() const noexcept
    {
        return has_mask(STATMOUNT_FS_SUBTYPE) ? string_at(data().fs_subtype) : std::string_view{};
    }

    [[nodiscard]] std::string_view
    source() const noexcept
    {
        return has_mask(STATMOUNT_SB_SOURCE) ? string_at(data().sb_source) : std::string_view{};
    }

    [[nodiscard]] std::string_view
    options() const noexcept
    {
        return has_mask(STATMOUNT_MNT_OPTS) ? string_at(data().mnt_opts) : std::string_view{};
    }

  private:
    explicit statmount(std::vector<std::byte>&& buffer) noexcept : buffer_(std::move(buffer)) {}

    [[nodiscard]] std::uint64_t
    mask() const noexcept
    {
        return data().mask;
    }

    [[nodiscard]] bool
    has_mask(const std::uint64_t requested) const noexcept
    {
        return (mask() & requested) == requested;
    }

    [[nodiscard]] const struct ::statmount&
    data() const noexcept
    {
        return *reinterpret_cast<const struct ::statmount*>(buffer_.data());
    }

    // kernel flexible string
    [[nodiscard]] std::string_view
    string_at(const std::uint32_t offset) const noexcept
    {
        constexpr auto strings_offset = offsetof(struct ::statmount, str);
        const auto returned_size = data().size;
        if (returned_size < strings_offset || returned_size > buffer_.size())
        {
            return {};
        }

        const auto strings_size = returned_size - strings_offset;
        if (offset >= strings_size)
        {
            return {};
        }

        const auto* first = reinterpret_cast<const char*>(buffer_.data()) + strings_offset + offset;
        const auto remaining = strings_size - offset;
        const auto* last = static_cast<const char*>(std::memchr(first, '\0', remaining));
        if (last == nullptr)
        {
            return {};
        }
        return {first, static_cast<std::size_t>(last - first)};
    }

    std::vector<std::byte> buffer_;
};
} // namespace ztd
