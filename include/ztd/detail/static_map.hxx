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
#include <array>
#include <initializer_list>
#include <ranges>
#include <stdexcept>
#include <utility>

// https://www.youtube.com/watch?v=INn3xa4pMfg

namespace ztd
{
template<typename KType, typename VType, std::size_t Size> class static_map final
{
  public:
    constexpr explicit static_map(std::initializer_list<std::pair<KType, VType>> l) noexcept
        : data_{}
    {
        std::ranges::copy(l, data_.begin());
        // needs to be sorted for std::ranges::binary_search
        std::ranges::sort(data_, {}, &std::pair<KType, VType>::first);
    }

    constexpr static_map() = delete;
    constexpr static_map(const static_map&) = default;
    constexpr static_map(static_map&&) noexcept = default;
    constexpr static_map& operator=(const static_map&) = delete;
    constexpr static_map& operator=(static_map&&) noexcept = delete;
    ~static_map() = default;

    template<typename Self>
    [[nodiscard]] constexpr auto&&
    at(this Self&& self, const KType& key)
    {
        auto it = std::ranges::lower_bound(self.data_, key, {}, &std::pair<KType, VType>::first);
        if (it != std::ranges::end(self.data_) && it->first == key)
        {
            return (it->second);
        }
        throw std::out_of_range("Key not found");
    }

    [[nodiscard]] constexpr bool
    contains(const KType& key) const noexcept
    {
        return std::ranges::binary_search(data_, key, {}, &std::pair<KType, VType>::first);
    }

  private:
    std::array<std::pair<KType, VType>, Size> data_;
};

template<typename KType, typename VType, std::size_t Size>
using map [[deprecated("help: renamed to ztd::static_map")]] = static_map<KType, VType, Size>;
} // namespace ztd
