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

#include <string_view>

#include <memory>

#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ztd
{
    class Logger
    {
      public:
        static void Init(std::string_view domain, spdlog::level::level_enum level = spdlog::level::trace);

        static const std::shared_ptr<spdlog::logger>& ZTDLogger() noexcept;

      private:
        static inline bool m_init{false};
        static inline std::shared_ptr<spdlog::logger> s_ZTDLogger;
    };
} // namespace ztd

// Logging Macros
#define LOG_TRACE(...)    ::ztd::Logger::ZTDLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::ztd::Logger::ZTDLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::ztd::Logger::ZTDLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::ztd::Logger::ZTDLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::ztd::Logger::ZTDLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::ztd::Logger::ZTDLogger()->critical(__VA_ARGS__)
