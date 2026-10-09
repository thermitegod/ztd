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

#include <atomic>
#include <concepts>

namespace ztd
{
// A one time changeable bool
template<typename T = bool> class fuse final
{
    static_assert(std::same_as<T, bool> || std::same_as<T, std::atomic_bool>,
                  "ztd::fuse must be backed with either bool or std::atomic_bool");

  public:
    // no implicit conversion to bool
    constexpr fuse(auto) = delete;
    constexpr fuse& operator=(auto) = delete;

    constexpr fuse(bool init_value = false) : value_(init_value), changed_(false) {}

    constexpr
    operator bool() const noexcept
    {
        return value_;
    }

    constexpr fuse&
    operator=(bool new_value)
    {
        if (!changed_)
        {
            value_ = new_value;
            changed_ = true;
        }
        return *this;
    }

    [[nodiscard]] constexpr bool
    is_blown() const noexcept
    {
        return changed_;
    }

  private:
    T value_;
    T changed_;
};
} // namespace ztd
