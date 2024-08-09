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
#include <algorithm>
#include <initializer_list>
#include <utility>

#include <stdexcept>

#include "types.hxx"

// https://www.youtube.com/watch?v=INn3xa4pMfg

namespace ztd
{
template<typename KType, typename VType, usize Size> struct map
{
    constexpr map(const std::initializer_list<std::pair<KType, VType>> l)
    {
        std::copy(l.begin(), l.end(), data.begin());
    }

    constexpr map() = delete;
    constexpr map(const map& other) = default;
    constexpr map(map&& other) noexcept = default;
    constexpr map& operator=(const map& other) = delete;
    constexpr map& operator=(map&& other) noexcept = delete;
    ~map() = default;

    [[nodiscard]] constexpr VType&
    at(const KType& key)
    {
        auto it = std::ranges::find_if(this->data, [&key](const auto& v) { return v.first == key; });
        if (it != this->data.cend())
        {
            return it->second;
        }
        throw std::out_of_range("Key not found");
    }

    [[nodiscard]] constexpr const VType&
    at(const KType& key) const
    {
        const auto it = std::ranges::find_if(this->data, [&key](const auto& v) { return v.first == key; });
        if (it != this->data.cend())
        {
            return it->second;
        }
        throw std::out_of_range("Key not found");
    }

    [[nodiscard]] constexpr bool
    contains(const KType& key) const
    {
        return std::ranges::find_if(this->data, [&key](const auto& v) { return v.first == key; }) != this->data.cend();
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

  private:
    std::array<std::pair<KType, VType>, Size> data;
};
} // namespace ztd
