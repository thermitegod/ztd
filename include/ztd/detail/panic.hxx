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

#include <format>
#include <print>

#include <cstdlib>

namespace ztd
{
/**
 * @brief abort program execution.
 */
[[noreturn]] constexpr void
panic() noexcept
{
    std::abort();
}

/**
 * @brief print panic message and abort program execution.
 */
template<typename... Args>
[[noreturn]] constexpr void
panic(std::format_string<Args...> fmt, Args&&... args) noexcept
{
    std::print(stderr, "panic: ");
    std::println(stderr, fmt, std::forward<Args>(args)...);
    std::abort();
}

/**
 * @brief if condition is met, abort program execution.
 */
constexpr void
panic_if(bool cond) noexcept
{
    if (cond) [[unlikely]]
    {
        std::abort();
    }
}

/**
 * @brief if condition is met, print panic message and abort program execution.
 */
template<typename... Args>
constexpr void
panic_if(bool cond, std::format_string<Args...> fmt, Args&&... args) noexcept
{
    if (cond) [[unlikely]]
    {
        std::print(stderr, "panic: ");
        std::println(stderr, fmt, std::forward<Args>(args)...);
        std::abort();
    }
}
} // namespace ztd
