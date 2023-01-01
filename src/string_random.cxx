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

#include <cstdlib>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_random.hxx"

inline constexpr std::string_view chars_alphanum{"0123456789"
                                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                 "abcdefghijklmnopqrstuvwxyz"};

static const std::string
private_rand_str(usize len, u32 char_num) noexcept
{
    std::string str;
    str.reserve(len);

    while (str.size() < len)
    {
        str += chars_alphanum.at(std::rand() % char_num);
    }

    return str;
}

const std::string
ztd::randhex(usize len) noexcept
{
    return private_rand_str(len, 16);
}

const std::string
ztd::randstr(usize len) noexcept
{
    return private_rand_str(len, chars_alphanum.size());
}
