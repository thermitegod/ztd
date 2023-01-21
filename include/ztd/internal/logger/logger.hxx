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

#include <string>
#include <string_view>

#include <memory>

#include <utility>

#include <cassert>

#include <fmt/format.h>

#if !defined(SPDLOG_FMT_EXTERNAL)
#define SPDLOG_FMT_EXTERNAL
#endif
#include <spdlog/spdlog.h>
#undef SPDLOG_FMT_EXTERNAL

namespace ztd
{
    class LoggerManager
    {
      public:
        LoggerManager() = default;
        ~LoggerManager() = default;

        void initialize(spdlog::level::level_enum level = spdlog::level::trace);
        void initialize(std::string_view log_file, spdlog::level::level_enum level = spdlog::level::trace);
        static void shutdown();

      public:
        static inline const std::string domain{"ztd"};
    };

    using log_manager_t = std::shared_ptr<LoggerManager>;
    const extern log_manager_t Logger;
} // namespace ztd

namespace ztd::logger
{
    template<typename... Args> using format_string_t = fmt::format_string<Args...>;

    template<typename... Args>
    void
    trace(format_string_t<Args...> fmt, Args&&... args)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->trace(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    debug(format_string_t<Args...> fmt, Args&&... args)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->debug(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    info(format_string_t<Args...> fmt, Args&&... args)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    warn(format_string_t<Args...> fmt, Args&&... args)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    error(format_string_t<Args...> fmt, Args&&... args)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    critical(format_string_t<Args...> fmt, Args&&... args)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->critical(fmt, std::forward<Args>(args)...);
    }

    template<typename T>
    void
    trace(const T& msg)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->trace(msg);
    }

    template<typename T>
    void
    debug(const T& msg)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->debug(msg);
    }

    template<typename T>
    void
    info(const T& msg)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->info(msg);
    }

    template<typename T>
    void
    warn(const T& msg)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->warn(msg);
    }

    template<typename T>
    void
    error(const T& msg)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->error(msg);
    }

    template<typename T>
    void
    critical(const T& msg)
    {
        assert(spdlog::get(ztd::Logger->domain) != nullptr);
        spdlog::get(ztd::Logger->domain)->critical(msg);
    }
} // namespace ztd::logger

// Logging Macros

#if !defined(ZTD_DISABLE_GLOBAL_LOG_MACROS)

#define LOG_TRACE(...)    ztd::logger::trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ztd::logger::debug(__VA_ARGS__)
#define LOG_INFO(...)     ztd::logger::info(__VA_ARGS__)
#define LOG_WARN(...)     ztd::logger::warn(__VA_ARGS__)
#define LOG_ERROR(...)    ztd::logger::error(__VA_ARGS__)
#define LOG_CRITICAL(...) ztd::logger::critical(__VA_ARGS__)

#endif
