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

#include <algorithm>
#include <ranges>

#include <cstring>

#include <array>
#include <span>
#include <vector>

#include <cmath>

#include <fmt/format.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_python.hxx"

/**
 * https://docs.python.org/3/library/stdtypes.html#string-methods
 *
 * Implemented
 * ===========
 * capitalize    - Full
 * center        - Full
 * count         - Full
 * endswith      - Full
 * expandtabs    - Partial
 *                 - no special handling for '\n'
 * isalnum       - Full
 * isalpha       - Full
 * isascii       - Full
 * isdecimal     - Full
 * isdigit       - Partial
 *                 - Only supports base10
 * islower       - Full
 * isnumeric     - Partial
 *                 - Only supports base10
 * isspace       - Full
 * istitle       - Full
 * isupper       - Full
 * join          - Full
 * ljust         - Full
 * lower         - Full
 * lstrip        - Full
 * partition     - Full
 *                 - Note, for empty 'sep', Python throws ValueError, We return {"str", "", ""}
 * removeprefix  - Full
 * removesuffix  - Full
 * replace       - Full
 *                 - WONTFIX, a empty 'str_find' does not cause 'str_replace' to be
 *                   inserted between every character in 'str', Just returns the
 *                   original string. Python Example below.
 *                      >>> a = ' z '
 *                      >>> a.replace('', 'a')
 *                      'a aza a'
 * rjust         - Full
 * rpartition    - Full
 *                 - Note, for empty 'sep', Python throws ValueError, We return {"", "", "str"}
 * rsplit        - Full
 * rstrip        - Full
 * split         - Full
 * splitlines    - Disabled
 * startswith    - Full
 * strip         - Full
 * swapcase      - Full
 * title         - Full
 * upper         - Full
 * zfill         - Full
 *
 * Not implemented
 * ===============
 * casefold      - Maybe
 * encode        - No
 * find          - No use std::string::find
 * format        - No
 * format_map    - No
 * index         - No use std::string::find
 * isidentifier  - No
 * isprintable   - No
 * maketrans     - No
 * rfind         - No use std::string::rfind
 * rindex        - No use std::string::rfind
 * translate     - No
 */

const std::vector<std::string>
ztd::split(const std::string_view str, const std::string_view sep, i32 maxsplit) noexcept
{
    if (str.empty())
    {
        return {str.data()};
    }

    if (sep.empty() || maxsplit == 0)
    {
        return {str.data()};
    }

    i32 split_counter = 0;
    std::string split_string = str.data();
    std::vector<std::string> result;

    while (!split_string.empty())
    {
        const usize index = split_string.find(sep);
        if (index == std::string_view::npos)
        {
            result.emplace_back(split_string);
            break;
        }

        result.emplace_back(split_string.substr(0, index));
        split_string = split_string.substr(index + sep.size());
        if (split_string.empty())
        {
            result.emplace_back(split_string);
        }

        // Limit total number of splits
        split_counter += 1;
        if (split_counter == maxsplit)
        {
            result.emplace_back(split_string);
            break;
        }
    }
    return result;
}

const std::vector<std::string>
ztd::rsplit(const std::string_view str, const std::string_view sep, i32 maxsplit) noexcept
{
    if (str.empty())
    {
        return {str.data()};
    }

    if (sep.empty() || maxsplit == 0)
    {
        return {str.data()};
    }

    i32 split_counter = 0;
    std::string split_string = str.data();
    std::vector<std::string> result;

    while (!split_string.empty())
    {
        const usize index = split_string.rfind(sep);
        if (index == std::string_view::npos)
        {
            result.emplace_back(split_string);
            break;
        }

        result.emplace_back(split_string.substr(index + sep.size()));
        split_string = split_string.substr(0, index);
        if (split_string.empty())
        {
            result.emplace_back(split_string);
        }

        // Limit total number of splits
        split_counter += 1;
        if (split_counter == maxsplit)
        {
            result.emplace_back(split_string);
            break;
        }
    }

    std::ranges::reverse(result);

    return result;
}

const std::string
ztd::join(const std::span<const std::string> span, const std::string_view sep) noexcept
{
    std::string str;
    for (const std::string_view part : span)
    {
        str = fmt::format("{}{}{}", str, part, sep);
    }
    return str.substr(0, str.size() - sep.size());
}

const std::string
ztd::join(const std::span<const std::string_view> span, const std::string_view sep) noexcept
{
    std::string str;
    for (const std::string_view part : span)
    {
        str = fmt::format("{}{}{}", str, part, sep);
    }
    return str.substr(0, str.size() - sep.size());
}

const std::string
ztd::lower(const std::string_view str) noexcept
{
    std::string lower = str.data();
    std::ranges::transform(lower.cbegin(), lower.cend(), lower.begin(), ::tolower);
    return lower;
}

const std::string
ztd::upper(const std::string_view str) noexcept
{
    std::string upper = str.data();
    std::ranges::transform(upper.cbegin(), upper.cend(), upper.begin(), ::toupper);
    return upper;
}

const std::string
ztd::replace(const std::string_view str, const std::string_view str_find, const std::string_view str_replace,
             i32 count) noexcept
{
    if (str.empty() || str_find.empty() || count == 0)
    {
        return str.data();
    }

    usize start_pos = str.find(str_find);
    if (start_pos == std::string_view::npos)
    {
        return str.data();
    }

    i32 counter = 0;
    std::string rep = str.data();

    while ((start_pos = rep.find(str_find, start_pos)) != std::string_view::npos)
    {
        rep.replace(start_pos, str_find.size(), str_replace);
        // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
        start_pos += str_replace.size();

        counter += 1;
        if (counter == count)
        {
            break;
        }
    }
    return rep;
}

const std::string
ztd::capitalize(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return str.data();
    }

    std::string cap = lower(str);
    cap[0] = std::toupper(cap[0]);
    return cap;
}

const std::string
ztd::center(const std::string_view str, u32 width, char fillchar) noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const u64 w = width - str.size();

    u64 offset_r = 0;
    if (w % 2 != 0)
    {
        offset_r = 1;
    }

    const u64 pad_l = static_cast<u64>(std::floor(w / 2));
    const u64 pad_r = static_cast<u64>(std::floor(w / 2)) + offset_r;

    std::string center_str;
    center_str.append(pad_l, fillchar);
    center_str.append(str);
    center_str.append(pad_r, fillchar);
    return center_str;
}

u64
ztd::count(const std::string_view str, const std::string_view find) noexcept
{
    u64 count = 0;

    if (str.empty())
    {
        return count;
    }

    usize start_pos = str.find(find);
    if (start_pos == std::string_view::npos)
    {
        return count;
    }

    while ((start_pos = str.find(find, start_pos)) != std::string_view::npos)
    {
        start_pos += find.size();
        count += 1;
    }
    return count;
}

u64
ztd::count(const std::string_view str, const std::string_view find, usize start, usize end) noexcept
{
    if (start >= end)
    {
        return 0;
    }

    const std::string_view ss{str.substr(start, end - start)};

    return count(ss, find);
}

bool
ztd::endswith(const std::string_view str, const std::string_view suffix) noexcept
{
    const usize start_pos = str.find(suffix);
    if (start_pos == std::string_view::npos)
    {
        return false;
    }

    return (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
}

bool
ztd::endswith(const std::string_view str, const std::string_view suffix, usize start, usize end) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const std::string_view ss{str.substr(start, end - start)};

    return endswith(ss, suffix);
}

bool
ztd::endswith(const std::string_view str, const std::span<const std::string> suffixes) noexcept
{
    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

bool
ztd::endswith(const std::string_view str, const std::span<const std::string> suffixes, usize start, usize end) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix, start, end); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

bool
ztd::endswith(const std::string_view str, const std::span<const std::string_view> suffixes) noexcept
{
    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

bool
ztd::endswith(const std::string_view str, const std::span<const std::string_view> suffixes, usize start,
              usize end) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix, start, end); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

bool
ztd::startswith(const std::string_view str, const std::string_view prefix) noexcept
{
    const usize start_pos = str.find(prefix);
    if (start_pos == std::string_view::npos)
    {
        return false;
    }

    return (str.compare(0, prefix.size(), prefix) == 0);
}

bool
ztd::startswith(const std::string_view str, const std::string_view prefix, usize start, usize end) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const std::string_view ss{str.substr(start, end - start)};

    return startswith(ss, prefix);
}

bool
ztd::startswith(const std::string_view str, const std::span<const std::string> prefixes) noexcept
{
    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
}

bool
ztd::startswith(const std::string_view str, const std::span<const std::string> prefixes, usize start,
                usize end) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix, start, end); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
}

bool
ztd::startswith(const std::string_view str, const std::span<const std::string_view> prefixes) noexcept
{
    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
}

bool
ztd::startswith(const std::string_view str, const std::span<const std::string_view> prefixes, usize start,
                usize end) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix, start, end); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
}

const std::string
ztd::expandtabs(const std::string_view str, u32 tabsize) noexcept
{
    std::string expanded;

    const auto columns = split(str, "\t");

    // need to track columns to avoid adding
    // extra whitespace at the end of a line
    usize columns_count = 1;

    for (const std::string_view column : columns)
    {
        usize tab_diff = 0;
        if (column.size() < tabsize)
        {
            expanded.append(column);
            tab_diff = tabsize - column.size();
            if (columns.size() != columns_count)
            {
                expanded.append(tab_diff, ' ');
            }
        }
        else if (column.size() > tabsize)
        {
            expanded.append(column);
            tab_diff = column.size() % tabsize;
            if (columns.size() != columns_count)
            {
                expanded.append(tab_diff, ' ');
            }
        }
        else if (column.size() == tabsize)
        {
            expanded.append(column);
            if (columns.size() != columns_count)
            {
                expanded.append(tabsize, ' ');
            }
        }
        ++columns_count;
    }
    return expanded;
}

bool
ztd::isalnum(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    const auto check = [=](const auto& c) { return !(std::isalpha(c) == 0 && std::isdigit(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
}

bool
ztd::isalpha(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    const auto check = [=](const auto& c) { return !(std::isalpha(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
}

#if 0
bool
ztd::isascii(const std::string_view str) noexcept
{
    if (str.empty())
        return true;

    for (const auto& c : str)
    {
        // unsigned char ch = static_cast<int>(str.at(i));
        const u64 ch = static_cast<u64>(c);
        if (ch > 127)
            return false;
    }
    return true;
}
#endif

bool
ztd::isdecimal(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    const auto check = [=](const auto& c) { return !(std::isdigit(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
}

bool
ztd::islower(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    const auto check = [=](const auto& c) { return !(std::isalpha(c) != 0 && std::islower(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
}

bool
ztd::isupper(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    const auto check = [=](const auto& c) { return !(std::isalpha(c) != 0 && std::isupper(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
}

bool
ztd::isspace(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    const auto check = [=](const auto& c) { return !(std::isspace(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
}

bool
ztd::istitle(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    bool in_word = false;
    u32 in_word_count = 0;

    for (const auto& c : str)
    {
        if (std::isalpha(c) != 0)
        {
            in_word = true;

            if (in_word_count == 0)
            {
                if (std::isupper(c) == 0)
                {
                    return false;
                }
            }
            else
            {
                if (std::islower(c) == 0)
                {
                    return false;
                }
            }
        }
        else
        {
            in_word = false;
        }

        if (in_word)
        {
            in_word_count += 1;
        }
        else
        {
            in_word_count = 0;
        }
    }
    return true;
}

const std::string
ztd::title(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return str.data();
    }

    bool in_word = false;
    u32 in_word_count = 0;

    std::string title_str;
    for (usize i = 0; i < str.size(); ++i)
    {
        if (std::isalpha(str.at(i)) != 0)
        {
            in_word = true;

            if (in_word_count == 0)
            {
                title_str.append(upper(std::string(str.substr(i, 1))));
            }
            else
            {
                title_str.append(lower(std::string(str.substr(i, 1))));
            }
        }
        else
        {
            in_word = false;
            title_str.append(std::string(str.substr(i, 1)));
        }

        if (in_word)
        {
            in_word_count += 1;
        }
        else
        {
            in_word_count = 0;
        }
    }
    return title_str;
}

const std::string
ztd::swapcase(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return str.data();
    }

    std::string swapcase_str;
    for (usize i = 0; i < str.size(); ++i)
    {
        if (std::isalpha(str.at(i)) != 0)
        {
            if (std::isupper(str.at(i)) != 0)
            {
                swapcase_str.append(lower(std::string(str.substr(i, 1))));
            }
            else if (std::islower(str.at(i)) != 0)
            {
                swapcase_str.append(upper(std::string(str.substr(i, 1))));
            }
            else
            {
                swapcase_str.append(std::string(str.substr(i, 1)));
            }
        }
        else
        {
            swapcase_str.append(std::string(str.substr(i, 1)));
        }
    }
    return swapcase_str;
}

const std::string
ztd::ljust(const std::string_view str, usize width, char fillchar) noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const u64 w = width - str.size();

    std::string ljust_str;
    ljust_str.append(str);
    ljust_str.append(w, fillchar);
    return ljust_str;
}

const std::string
ztd::rjust(const std::string_view str, usize width, char fillchar) noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const u64 w = width - str.size();

    std::string rjust_str;
    rjust_str.append(w, fillchar);
    rjust_str.append(str);
    return rjust_str;
}

const std::string
ztd::lstrip(const std::string_view str, const std::string_view chars) noexcept
{
    using namespace std::literals::string_literals;

    const usize start_pos = str.find_first_not_of(chars);
    if (start_pos == std::string_view::npos)
    {
        return ""s;
    }
    return std::string(str.substr(start_pos));
}

const std::string
ztd::rstrip(const std::string_view str, const std::string_view chars) noexcept
{
    using namespace std::literals::string_literals;

    const usize end_pos = str.find_last_not_of(chars);
    if (end_pos == std::string_view::npos)
    {
        return ""s;
    }
    return std::string(str.substr(0, end_pos + 1));
}

const std::string
ztd::strip(const std::string_view str, const std::string_view chars) noexcept
{
    return lstrip(rstrip(str, chars), chars);
}

const std::string
ztd::removeprefix(const std::string_view str, const std::string_view prefix) noexcept
{
    if (!startswith(str, prefix))
    {
        return str.data();
    }
    return std::string(str.substr(prefix.size(), str.size()));
}

const std::string
ztd::removesuffix(const std::string_view str, const std::string_view suffix) noexcept
{
    if (!endswith(str, suffix))
    {
        return str.data();
    }
    return std::string(str.substr(0, str.size() - suffix.size()));
}

const std::array<std::string, 3>
ztd::partition(const std::string_view str, const std::string_view sep) noexcept
{
    using namespace std::literals::string_literals;

    if (sep.empty())
    {
        return {str.data(), ""s, ""s};
    }

    const usize index = str.find(sep);
    if (index == std::string_view::npos)
    {
        return {str.data(), ""s, ""s};
    }

    const std::string_view begin{str.substr(0, index)};
    const std::string_view end{str.substr(index + sep.size())};

    return {std::string(begin), std::string(sep), std::string(end)};
}

const std::array<std::string, 3>
ztd::rpartition(const std::string_view str, const std::string_view sep) noexcept
{
    using namespace std::literals::string_literals;

    if (sep.empty())
    {
        return {""s, ""s, str.data()};
    }

    const usize index = str.rfind(sep);
    if (index == std::string_view::npos)
    {
        return {""s, ""s, str.data()};
    }

    const std::string_view begin{str.substr(0, index)};
    const std::string_view end{str.substr(index + sep.size())};

    return {std::string(begin), std::string(sep), std::string(end)};
}

#if 0
const std::vector<std::string>
ztd::splitlines(const std::string_view str, bool keepends) noexcept
{
    if (str.empty())
        return {};

    const std::vector<std::string> delimiters{
        "\r\n",   // Carriage Return + Line Feed
        "\n",     // Line Feed
        "\r",     // Carriage Return
        "\v",     // Line Tabulation
        "\x0b",   // Line Tabulation
        "\f",     // Form Feed
        "\x0c",   // Form Feed
        "\x1c",   // File Separator
        "\x1d",   // Group Separator
        "\x1e",   // Record Separator
        "\x85",   // Next Line (C1 Control Code)
        "\u2028", // Line Separator
        "\u2029", // Paragraph Separator
    };

    std::string split_string = str.data();

    std::vector<std::string> lines;

    while (!split_string.empty())
    {
        bool found = false;

        usize index = 0;
        const std::string_view delimiter;
        for (const std::string_view d : delimiters)
        {
            index = split_string.find(d);
            if (index == std::string_view::npos)
                continue;

            found = true;
            delimiter = d;
            break;
        }
        if (!found)
        {
            lines.emplace_back(split_string);
            break;
        }

        if (keepends)
        {
            lines.emplace_back(split_string.substr(0, index + delimiter.length()));
        }
        else
        {
            lines.emplace_back(split_string.substr(0, index));
        }
        split_string = split_string.substr(index + delimiter.size());
    }
    return lines;
}
#endif

const std::string
ztd::zfill(const std::string_view str, usize width) noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const u64 w = width - str.size();

    std::string zstr;
    if (str.empty())
    {
        zstr.append(w, '0');
    }
    else
    {
        if (str.at(0) == '+')
        {
            zstr.append("+");
            zstr.append(w, '0');
            zstr.append(str, 1);
        }
        else if (str.at(0) == '-')
        {
            zstr.append("-");
            zstr.append(w, '0');
            zstr.append(str, 1);
        }
        else
        {
            zstr.append(w, '0');
            zstr.append(str);
        }
    }

    return zstr;
}
