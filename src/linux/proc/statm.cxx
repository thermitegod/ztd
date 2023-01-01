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

#include <string>
#include <string_view>

#include <filesystem>

#include <fstream>
#include <sstream>

#include <sys/types.h>

#include <fmt/format.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_utils.hxx"
#include "ztd/internal/string_python.hxx"

#include "ztd/internal/linux/proc/statm.hxx"

constexpr u8 idx_size = 0;
constexpr u8 idx_resident = 1;
constexpr u8 idx_shared = 2;
constexpr u8 idx_text = 3;
constexpr u8 idx_lib = 4;
constexpr u8 idx_data = 5;
constexpr u8 idx_dt = 6;

ztd::proc::statm::statm()
{
    this->populate("/proc/self/statm");
}

ztd::proc::statm::statm(pid_t pid)
{
    const std::string path = fmt::format("/proc/{}/statm", pid);

    this->populate(path);
}

ztd::proc::statm::statm(const std::filesystem::path& path)
{
    this->populate(path);
}

void
ztd::proc::statm::populate(const std::filesystem::path& path) noexcept
{
    std::ifstream file(path);
    if (file.is_open())
    {
        std::stringstream stream;
        stream << file.rdbuf();

        const std::string raw_stat = stream.str();

        const auto stat_data = ztd::split(raw_stat, " ");

        this->m_size = std::stoul(stat_data.at(idx_size));
        this->m_resident = std::stoul(stat_data.at(idx_resident));
        this->m_shared = std::stoul(stat_data.at(idx_shared));
        this->m_text = std::stoul(stat_data.at(idx_text));
        this->m_lib = std::stoul(stat_data.at(idx_lib));
        this->m_data = std::stoul(stat_data.at(idx_data));
        this->m_dt = std::stoul(stat_data.at(idx_dt));
    }
}

/**
 * proc/<PID>/statm entries
 */

u64
ztd::proc::statm::size() const noexcept
{
    return this->m_size;
}
u64
ztd::proc::statm::resident() const noexcept
{
    return this->m_resident;
}
u64
ztd::proc::statm::shared() const noexcept
{
    return this->m_shared;
}
u64
ztd::proc::statm::text() const noexcept
{
    return this->m_text;
}
u64
ztd::proc::statm::lib() const noexcept
{
    return this->m_lib;
}
u64
ztd::proc::statm::data() const noexcept
{
    return this->m_data;
}
u64
ztd::proc::statm::dt() const noexcept
{
    return this->m_dt;
}
