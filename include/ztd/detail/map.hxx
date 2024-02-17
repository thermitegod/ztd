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

#include <array>

#include <stdexcept>

#include <algorithm>

#include "types.hxx"

// https://www.youtube.com/watch?v=INn3xa4pMfg

namespace ztd
{
template<typename KType, typename VType, usize Size> struct map
{
    std::array<std::pair<KType, VType>, Size> data;

    [[nodiscard]] constexpr VType
    at(const KType key) const
    {
        const auto it = std::ranges::find_if(this->data, [&key](const auto& v) { return v.first == key; });
        if (it != this->data.cend())
        {
            return it->second;
        }
        else
        {
            throw std::range_error("Not Found");
        }
    }

    auto
    begin() const noexcept
    {
        return this->data.cbegin();
    }

    auto
    cbegin() const noexcept
    {
        return this->data.cbegin();
    }

    auto
    end() const noexcept
    {
        return this->data.cbegin();
    }

    auto
    cend() const noexcept
    {
        return this->data.cbegin();
    }
};
} // namespace ztd
