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

namespace ztd
{
    class fuse
    {
      public:
        // no implicit conversion to bool
        constexpr fuse(auto init_value) = delete;
        constexpr fuse& operator=(auto new_value) = delete;

        constexpr fuse(bool init_value = false) : value(init_value), changed(false){};

        constexpr
        operator bool() const noexcept
        {
            return this->value;
        }

        constexpr fuse&
        operator=(bool new_value)
        {
            if (!this->changed)
            {
                this->value = new_value;
                this->changed = true;
            }
            return *this;
        }

        [[nodiscard]] constexpr bool
        is_blown() const noexcept
        {
            return this->changed;
        }

      private:
        bool value;
        bool changed;
    };
} // namespace ztd
