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

#ifndef ZTD_LOGGER_HEADER
#error "Only <ztd-logger.hxx> can be included directly"
#endif

#pragma once

#include <string>

#include <exception>

#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ztd
{
    class LoggerException: virtual public std::exception
    {
    protected:
        std::string error_message;

    public:
        explicit LoggerException(const std::string& msg) : error_message(msg)
        {
        }

        virtual ~LoggerException() throw()
        {
        }

        virtual const char*
        what() const throw()
        {
            return error_message.c_str();
        }
    };

    namespace
    {
        template<typename T> using Ref = std::shared_ptr<T>;
        template<typename T, typename... Args>
        constexpr Ref<T>
        CreateRef(Args&&... args)
        {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
    } // namespace

    class Logger
    {
      public:
        static inline void
        Init(const std::string& domain)
        {
            if (m_init)
                throw LoggerException("Can only call ztd::Logger::Init once");
            m_init = true;

            spdlog::set_pattern("[%H:%M:%S.%e] [%^%L%$] [thread %t] %v");
            s_ZTDLogger = spdlog::stdout_color_mt(domain);
            s_ZTDLogger->set_level(spdlog::level::trace);
            s_ZTDLogger->flush_on(spdlog::level::trace);
        }

        static inline Ref<spdlog::logger>&
        ZTDLogger() noexcept
        {
            return s_ZTDLogger;
        }

      private:
        static inline bool m_init{false};
        static inline Ref<spdlog::logger> s_ZTDLogger;
    };
} // namespace ztd

// Logging Macros
#define LOG_TRACE(...)    ::ztd::Logger::ZTDLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::ztd::Logger::ZTDLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::ztd::Logger::ZTDLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::ztd::Logger::ZTDLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::ztd::Logger::ZTDLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::ztd::Logger::ZTDLogger()->critical(__VA_ARGS__)
