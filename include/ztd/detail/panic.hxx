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

#if defined(__cpp_lib_debugging)
#include <debugging>
#endif
#include <format>
#include <print>

#include <cstdlib>

namespace ztd
{
/**
 * @brief breakpoint - set a breakpoint
 */
constexpr void
breakpoint() noexcept
{
#if defined(__cpp_lib_debugging)
    std::breakpoint_if_debugging();
#elif __has_builtin(__builtin_debugtrap)
    __builtin_debugtrap();
#else
    __builtin_trap();
#endif
}

/**
 * @brief panic - print panic message, set a breakpoint, and abort program execution.
 */
template<typename... Args>
[[noreturn]] constexpr void
panic(std::format_string<Args...> fmt, Args&&... args) noexcept
{
    std::println(stderr, "panic: {}", std::format(fmt, std::forward<Args>(args)...));
    ztd::breakpoint();
    std::abort();
}
} // namespace ztd
