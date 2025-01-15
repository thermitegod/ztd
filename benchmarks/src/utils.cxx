/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include <array>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

const std::string
create_repeat_string(std::string_view input, std::size_t num)
{
    std::string s;
    s.reserve(input.size() * num);
    while (num--)
    {
        s.append(input);
    }
    return s;
}

const std::vector<std::string>
create_repeat_vector(std::string_view input, std::size_t num)
{
    std::vector<std::string> v;
    while (num--)
    {
        v.push_back(input.data());
    }
    return v;
}
