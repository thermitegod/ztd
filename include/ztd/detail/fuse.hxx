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

namespace ztd
{
// A one time changeable bool
class fuse final
{
  public:
    // no implicit conversion to bool
    constexpr fuse(auto init_value) = delete;
    constexpr fuse& operator=(auto new_value) = delete;

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
    bool value_;
    bool changed_;
};
} // namespace ztd
