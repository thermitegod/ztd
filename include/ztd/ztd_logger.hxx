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

#include <filesystem>

#include <memory>

#include <utility>

#include <cassert>

#include <fmt/format.h>
#include <fmt/std.h>

#if !defined(SPDLOG_FMT_EXTERNAL)
#define SPDLOG_FMT_EXTERNAL
#endif
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#undef SPDLOG_FMT_EXTERNAL

namespace ztd
{
    namespace
    {
        class log_manager;
    }
    static inline std::shared_ptr<ztd::log_manager> Logger;
    namespace
    {
        class log_manager
        { // https://spdlog.docsforge.com/v1.x/3.custom-formatting
          public:
            static void
            initialize(spdlog::level::level_enum level = spdlog::level::trace)
            {
                ztd::Logger = std::make_shared<ztd::log_manager>();

                const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
                console_sink->set_level(level);
                console_sink->set_pattern(LOG_FORMAT.data());

                const std::vector<spdlog::sink_ptr> sinks{console_sink};

                const auto logger =
                    std::make_shared<spdlog::logger>(ztd::log_manager::domain, sinks.cbegin(), sinks.cend());
                logger->set_level(level);
                logger->flush_on(level);

                spdlog::register_logger(logger);
            }

            static void
            initialize(const std::filesystem::path& log_file, spdlog::level::level_enum level = spdlog::level::trace)
            {
                ztd::Logger = std::make_shared<ztd::log_manager>();

                const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
                console_sink->set_level(level);
                console_sink->set_pattern(LOG_FORMAT.data());

                const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file, true);
                file_sink->set_level(level);
                file_sink->set_pattern(LOG_FORMAT.data());

                const std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

                const auto logger =
                    std::make_shared<spdlog::logger>(ztd::log_manager::domain, sinks.cbegin(), sinks.cend());
                logger->set_level(level);
                logger->flush_on(level);

                spdlog::register_logger(logger);
            }

            static void
            shutdown()
            {
                spdlog::shutdown();
            }

          public:
            static inline const std::string domain{"ztd"};
            static inline const std::string_view LOG_FORMAT{"[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] [thread %t] %v"};
        };
    } // namespace
} // namespace ztd

namespace ztd::logger
{
    template<typename... Args> using format_string_t = fmt::format_string<Args...>;

    template<typename... Args>
    void
    trace(format_string_t<Args...> fmt, Args&&... args)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->trace(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    debug(format_string_t<Args...> fmt, Args&&... args)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->debug(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    info(format_string_t<Args...> fmt, Args&&... args)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    warn(format_string_t<Args...> fmt, Args&&... args)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    error(format_string_t<Args...> fmt, Args&&... args)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void
    critical(format_string_t<Args...> fmt, Args&&... args)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->critical(fmt, std::forward<Args>(args)...);
    }

    template<typename T>
    void
    trace(const T& msg)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->trace(msg);
    }

    template<typename T>
    void
    debug(const T& msg)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->debug(msg);
    }

    template<typename T>
    void
    info(const T& msg)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->info(msg);
    }

    template<typename T>
    void
    warn(const T& msg)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->warn(msg);
    }

    template<typename T>
    void
    error(const T& msg)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->error(msg);
    }

    template<typename T>
    void
    critical(const T& msg)
    {
        const auto logger = spdlog::get(ztd::log_manager::domain);
        assert(logger != nullptr);
        logger->critical(msg);
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
