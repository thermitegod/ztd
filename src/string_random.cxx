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

#include <random>

#include <bits/stdc++.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_random.hxx"

inline constexpr std::string_view chars_alphanum{"0123456789"
                                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                 "abcdefghijklmnopqrstuvwxyz"};

static const std::string
random_string(usize len, u32 char_num) noexcept
{
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, INT_MAX);

    std::string str;
    while (str.size() < len)
    {
        str += chars_alphanum.at(dist(rng) % char_num);
    }

    return str;
}

const std::string
ztd::randhex(usize len) noexcept
{
    return random_string(len, 16);
}

const std::string
ztd::randstr(usize len) noexcept
{
    return random_string(len, chars_alphanum.size());
}
