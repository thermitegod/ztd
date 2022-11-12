/**
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

#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include <spdlog/spdlog.h>

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
        static inline std::string domain;
    };

    using log_manager_t = std::shared_ptr<LoggerManager>;
    extern log_manager_t Logger;
} // namespace ztd

// Logging Macros

// clang-format off

// #define LOG_TRACE(...)    if (spdlog::get(ztd::Logger->domain) != nullptr) {spdlog::get(ztd::Logger->domain)->trace(__VA_ARGS__);}
// #define LOG_DEBUG(...)    if (spdlog::get(ztd::Logger->domain) != nullptr) {spdlog::get(ztd::Logger->domain)->debug(__VA_ARGS__);}
// #define LOG_INFO(...)     if (spdlog::get(ztd::Logger->domain) != nullptr) {spdlog::get(ztd::Logger->domain)->info(__VA_ARGS__);}
// #define LOG_WARN(...)     if (spdlog::get(ztd::Logger->domain) != nullptr) {spdlog::get(ztd::Logger->domain)->warn(__VA_ARGS__);}
// #define LOG_ERROR(...)    if (spdlog::get(ztd::Logger->domain) != nullptr) {spdlog::get(ztd::Logger->domain)->error(__VA_ARGS__);}
// #define LOG_CRITICAL(...) if (spdlog::get(ztd::Logger->domain) != nullptr) {spdlog::get(ztd::Logger->domain)->critical(__VA_ARGS__);}

#define LOG_TRACE(...)    spdlog::get(ztd::Logger->domain)->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    spdlog::get(ztd::Logger->domain)->debug(__VA_ARGS__)
#define LOG_INFO(...)     spdlog::get(ztd::Logger->domain)->info(__VA_ARGS__)
#define LOG_WARN(...)     spdlog::get(ztd::Logger->domain)->warn(__VA_ARGS__)
#define LOG_ERROR(...)    spdlog::get(ztd::Logger->domain)->error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::get(ztd::Logger->domain)->critical(__VA_ARGS__)

// clang-format on
