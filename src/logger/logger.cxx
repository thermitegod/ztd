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

#include <memory>

#include "ztd/internal/logger/logger.hxx"

void
ztd::Logger::Init(std::string_view domain, spdlog::level::level_enum level)
{
    if (m_init)
        return;
    m_init = true;

    spdlog::set_pattern("[%H:%M:%S.%e] [%^%L%$] [thread %t] %v");
    s_ZTDLogger = spdlog::stdout_color_mt(domain.data());
    s_ZTDLogger->set_level(level);
    s_ZTDLogger->flush_on(level);
}

const std::shared_ptr<spdlog::logger>&
ztd::Logger::ZTDLogger() noexcept
{
    return s_ZTDLogger;
}
