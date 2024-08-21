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

#include <filesystem>

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace ztd::logger
{
namespace detail
{
static constexpr auto domain{"ztd"};
} // namespace detail

[[deprecated]] inline void
initialize(const spdlog::level::level_enum level = spdlog::level::trace,
           const std::filesystem::path& logfile = "") noexcept
{
    const auto format{"[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] [thread %t] %v"};

    std::vector<spdlog::sink_ptr> sinks;

    const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(level);
    console_sink->set_pattern(format);
    sinks.push_back(console_sink);

    if (!logfile.empty())
    {
        const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile, true);
        file_sink->set_level(level);
        file_sink->set_pattern(format);
        sinks.push_back(file_sink);
    }

    const auto logger = std::make_shared<spdlog::logger>(detail::domain, sinks.cbegin(), sinks.cend());
    logger->set_level(level);
    logger->flush_on(level);

    spdlog::register_logger(logger);

    std::atexit(spdlog::shutdown);
}

namespace utils
{
template<typename T>
[[deprecated]] const void*
ptr(T p) noexcept
{
    static_assert(std::is_pointer_v<T>);
    return (void*)p;
}
template<typename T>
[[deprecated]] const void*
ptr(const std::unique_ptr<T>& p) noexcept
{
    return (void*)p.get();
}
template<typename T>
[[deprecated]] const void*
ptr(const std::shared_ptr<T>& p) noexcept
{
    return (void*)p.get();
}
} // namespace utils

template<typename... Args>
[[deprecated]] void
trace(spdlog::format_string_t<Args...> fmt, Args&&... args) noexcept
{
    spdlog::get(detail::domain)->trace(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
[[deprecated]] void
debug(spdlog::format_string_t<Args...> fmt, Args&&... args) noexcept
{
    spdlog::get(detail::domain)->debug(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
[[deprecated]] void
info(spdlog::format_string_t<Args...> fmt, Args&&... args) noexcept
{
    spdlog::get(detail::domain)->info(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
[[deprecated]] void
warn(spdlog::format_string_t<Args...> fmt, Args&&... args) noexcept
{
    spdlog::get(detail::domain)->warn(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
[[deprecated]] void
error(spdlog::format_string_t<Args...> fmt, Args&&... args) noexcept
{
    spdlog::get(detail::domain)->error(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
[[deprecated]] void
critical(spdlog::format_string_t<Args...> fmt, Args&&... args) noexcept
{
    spdlog::get(detail::domain)->critical(fmt, std::forward<Args>(args)...);
}

template<typename T>
[[deprecated]] void
trace(const T& msg) noexcept
{
    spdlog::get(detail::domain)->trace(msg);
}

template<typename T>
[[deprecated]] void
debug(const T& msg) noexcept
{
    spdlog::get(detail::domain)->debug(msg);
}

template<typename T>
[[deprecated]] void
info(const T& msg) noexcept
{
    spdlog::get(detail::domain)->info(msg);
}

template<typename T>
[[deprecated]] void
warn(const T& msg) noexcept
{
    spdlog::get(detail::domain)->warn(msg);
}

template<typename T>
[[deprecated]] void
error(const T& msg) noexcept
{
    spdlog::get(detail::domain)->error(msg);
}

template<typename T>
[[deprecated]] void
critical(const T& msg) noexcept
{
    spdlog::get(detail::domain)->critical(msg);
}
} // namespace ztd::logger
