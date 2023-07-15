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

#include <format>

#include <filesystem>

const std::filesystem::path
get_test_data_path(std::string_view relative_test_data)
{
    auto base = std::filesystem::current_path();
    while (base.has_parent_path())
    {
        const auto real_test_data = base / relative_test_data;
        if (std::filesystem::exists(real_test_data))
        {
            return real_test_data.string();
        }
        base = base.parent_path();
    }
    throw std::runtime_error(std::format("Missing test data: {}", relative_test_data));
}
