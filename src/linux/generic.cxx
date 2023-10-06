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

#include <filesystem>

#include "ztd/internal/linux/generic.hxx"

const std::filesystem::path proc{"/proc"};
const std::filesystem::path proc_self{"/proc/self"};
const std::filesystem::path proc_self_exe{"/proc/self/exe"};
const std::filesystem::path proc_self_stat{"/proc/self/stat"};

const std::filesystem::path
ztd::program::exe() noexcept
{
    return std::filesystem::read_symlink(proc_self_exe);
}

const std::string
ztd::program::name() noexcept
{
    return std::filesystem::read_symlink(proc_self_exe).filename();
}
