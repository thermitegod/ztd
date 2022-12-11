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

#include <string_view>

#include <vector>

#include <memory>

#include "ztd/internal/logger/logger.hxx"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// https://spdlog.docsforge.com/v1.x/3.custom-formatting

inline constexpr std::string_view LOG_FORMAT{"[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] [thread %t] %v"};

const ztd::log_manager_t ztd::Logger = std::make_shared<ztd::LoggerManager>();

void
ztd::LoggerManager::initialize(spdlog::level::level_enum level)
{
    const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(level);
    console_sink->set_pattern(LOG_FORMAT.data());

    const std::vector<spdlog::sink_ptr> sinks{console_sink};

    const auto logger = std::make_shared<spdlog::logger>(this->domain, sinks.cbegin(), sinks.cend());
    logger->set_level(level);
    logger->flush_on(level);

    spdlog::register_logger(logger);
}

void
ztd::LoggerManager::initialize(std::string_view log_file, spdlog::level::level_enum level)
{
    const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(level);
    console_sink->set_pattern(LOG_FORMAT.data());

    const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file.data(), true);
    file_sink->set_level(level);
    file_sink->set_pattern(LOG_FORMAT.data());

    const std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

    const auto logger = std::make_shared<spdlog::logger>(this->domain, sinks.cbegin(), sinks.cend());
    logger->set_level(level);
    logger->flush_on(level);

    spdlog::register_logger(logger);
}

void
ztd::LoggerManager::shutdown()
{
    spdlog::shutdown();
}
