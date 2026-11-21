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

#include <format>
#include <string>

#include "random.hxx"
#include "types.hxx"

namespace ztd
{
/**
 * @brief random
 * @param[in] len Length of the random string to return
 * @return Get a random hex string
 */
template<typename T>
[[nodiscard]] inline T
random(const ztd::usize len = 10_usize) noexcept
    requires(std::same_as<T, std::string>)
{
    const std::size_t n = len.data();

    auto& gen = detail::rng();

    std::string str;
    str.reserve(n);
    while (str.size() < n)
    {
        std::format_to(std::back_inserter(str), "{:08X}", static_cast<std::uint32_t>(gen()));
    }
    return str;
}

[[deprecated("help: use ztd::random<std::string>()")]] [[nodiscard]] inline std::string
random_hex(const ztd::usize len = 10_usize) noexcept
{
    return random<std::string>(len);
}

[[deprecated("help: use ztd::random<std::string>()")]] [[nodiscard]] inline std::string
randhex(const ztd::usize len = 10_usize) noexcept
{
    return random<std::string>(len);
}

[[deprecated("help: use ztd::random<std::string>()")]] [[nodiscard]] inline std::string
random_string(const ztd::usize len = 10_usize) noexcept
{
    return random<std::string>(len);
}

[[deprecated("help: use ztd::random<std::string>()")]] [[nodiscard]] inline std::string
randstr(const ztd::usize len = 10_usize) noexcept
{
    return random<std::string>(len);
}
} // namespace ztd
