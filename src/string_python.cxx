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

#include <string>
#include <string_view>

#include <algorithm>
#include <ranges>

#include <cstring>

#include <array>
#include <vector>

#include <cmath>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_python.hxx"

/**
 * https://docs.python.org/3/library/stdtypes.html#string-methods
 *
 * Implemented
 * ===========
 * capitalize
 * center
 * count
 * endswith
 * expandtabs
 * isalnum
 * isalpha
 * isdecimal
 * isdigit
 * islower
 * isnumeric
 * isspace
 * istitle
 * isupper
 * join
 * ljust
 * lower
 * lstrip
 * partition
 * removeprefix
 * removesuffix
 * replace
 * rjust
 * rpartition
 * rsplit
 * rstrip
 * split
 * startswith
 * strip
 * swapcase
 * title
 * upper
 * zfill
 *
 * Not implemented
 * ===============
 * casefold - ?
 * encode - NO
 * find - NO - std::string::find
 * format - NO
 * format_map - NO
 * index - NO
 * isascii - ?
 * isidentifier - NO
 * isprintable - NO
 * maketrans - NO
 * rfind - NO - std::string::rfind
 * rindex - NO
 * splitlines - ?
 * translate - NO
 */

const std::vector<std::string>
ztd::split(std::string_view str, std::string_view sep, i32 maxsplit) noexcept
{
    if (str.empty())
        return {std::string("")};

    if (sep.empty() || maxsplit == 0)
        return {str.data()};

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
        if (split_string.size() == 0)
            result.emplace_back(split_string);

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
ztd::rsplit(std::string_view str, std::string_view sep, i32 maxsplit) noexcept
{
    if (str.empty())
        return {std::string("")};

    if (sep.empty() || maxsplit == 0)
        return {str.data()};

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
        if (split_string.size() == 0)
            result.emplace_back(split_string);

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
ztd::join(const std::vector<std::string>& iterable, std::string_view sep) noexcept
{
    std::string str;
    for (auto it = iterable.cbegin(); it != iterable.cend(); ++it)
    {
        if (it != iterable.cbegin())
            str.append(sep.data());
        str.append(*it);
    }
    return str;
}

const std::string
ztd::join(const std::vector<std::string_view>& iterable, std::string_view sep) noexcept
{
    std::string str;
    for (auto it = iterable.cbegin(); it != iterable.cend(); ++it)
    {
        if (it != iterable.cbegin())
            str.append(sep.data());
        str.append(*it);
    }
    return str;
}

const std::string
ztd::lower(std::string_view str) noexcept
{
    std::string lower = str.data();
    std::ranges::transform(lower.cbegin(), lower.cend(), lower.begin(), ::tolower);
    return lower;
}

const std::string
ztd::upper(std::string_view str) noexcept
{
    std::string upper = str.data();
    std::ranges::transform(upper.cbegin(), upper.cend(), upper.begin(), ::toupper);
    return upper;
}

const std::string
ztd::replace(std::string_view str, std::string_view str_find, std::string_view str_replace, i32 count) noexcept
{
    if (str.empty() || count == 0)
        return str.data();

    usize start_pos = str.find(str_find);
    if (start_pos == std::string_view::npos)
        return str.data();

    i32 counter = 0;
    std::string rep = str.data();

    while ((start_pos = rep.find(str_find, start_pos)) != std::string_view::npos)
    {
        rep.replace(start_pos, str_find.size(), str_replace);
        // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
        start_pos += str_replace.size();

        counter += 1;
        if (counter == count)
            break;
    }
    return rep;
}

const std::string
ztd::capitalize(std::string_view str) noexcept
{
    if (str.empty())
        return str.data();

    std::string cap = lower(str);
    cap[0] = std::toupper(cap[0]);
    return cap;
}

const std::string
ztd::center(std::string_view str, u32 width, char fillchar) noexcept
{
    if (str.size() >= width)
        return str.data();

    const u64 w = width - str.size();

    u64 offset_r = 0;
    if (w % 2 != 0)
        offset_r = 1;

    const u64 pad_l = static_cast<u64>(std::floor(w / 2));
    const u64 pad_r = static_cast<u64>(std::floor(w / 2)) + offset_r;

    std::string center_str;
    center_str.append(pad_l, fillchar);
    center_str.append(str);
    center_str.append(pad_r, fillchar);
    return center_str;
}

u64
ztd::count(std::string_view str, std::string_view find, usize start, usize end) noexcept
{
    u64 count = 0;

    if (str.empty())
        return count;

    if (start >= end)
        return count;

    usize start_pos = str.find(find);
    if (start_pos == std::string_view::npos)
        return count;

    const std::string_view ss{str.substr(start, end - start)};

    while ((start_pos = ss.find(find, start_pos)) != std::string_view::npos)
    {
        start_pos += find.size();
        count += 1;
    }
    return count;
}

bool
ztd::endswith(std::string_view str, std::string_view suffix, usize start, usize end) noexcept
{
    if (start >= end)
        return false;

    const usize start_pos = str.find(suffix);
    if (start_pos == std::string_view::npos)
        return false;

    const std::string_view ss{str.substr(start, end - start)};

    return (ss.compare(ss.size() - suffix.size(), suffix.size(), suffix) == 0);
}

bool
ztd::endswith(std::string_view str, const std::vector<std::string>& suffixes, usize start, usize end) noexcept
{
    if (start >= end)
        return false;

    for (std::string_view suffix : suffixes)
    {
        if (endswith(str, suffix, start, end))
            return true;
    }
    return false;
}

bool
ztd::endswith(std::string_view str, const std::vector<std::string_view>& suffixes, usize start, usize end) noexcept
{
    if (start >= end)
        return false;

    for (std::string_view suffix : suffixes)
    {
        if (endswith(str, suffix, start, end))
            return true;
    }
    return false;
}

bool
ztd::startswith(std::string_view str, std::string_view prefix, usize start, usize end) noexcept
{
    if (start >= end)
        return false;

    const usize start_pos = str.find(prefix);
    if (start_pos == std::string_view::npos)
        return false;

    const std::string_view ss{str.substr(start, end - start)};

    return (ss.compare(0, prefix.size(), prefix) == 0);
}

bool
ztd::startswith(std::string_view str, const std::vector<std::string>& prefixes, usize start, usize end) noexcept
{
    if (start >= end)
        return false;

    for (std::string_view prefix : prefixes)
    {
        if (startswith(str, prefix, start, end))
            return true;
    }
    return false;
}

bool
ztd::startswith(std::string_view str, const std::vector<std::string_view>& prefixes, usize start, usize end) noexcept
{
    if (start >= end)
        return false;

    for (std::string_view prefix : prefixes)
    {
        if (startswith(str, prefix, start, end))
            return true;
    }
    return false;
}

const std::string
ztd::expandtabs(std::string_view str, u32 tabsize) noexcept
{
    std::string expanded;

    const auto columns = split(str, "\t");

    // need to track columns to avoid adding
    // extra whitespace at the end of a line
    usize columns_count = 1;

    for (std::string_view column : columns)
    {
        usize tab_diff = 0;
        if (column.size() < tabsize)
        {
            expanded.append(column);
            tab_diff = tabsize - column.size();
            if (columns.size() != columns_count)
                expanded.append(tab_diff, ' ');
        }
        else if (column.size() > tabsize)
        {
            expanded.append(column);
            tab_diff = column.size() % tabsize;
            if (columns.size() != columns_count)
                expanded.append(tab_diff, ' ');
        }
        else if (column.size() == tabsize)
        {
            expanded.append(column);
            if (columns.size() != columns_count)
                expanded.append(tabsize, ' ');
        }
        ++columns_count;
    }
    return expanded;
}

bool
ztd::isalnum(std::string_view str) noexcept
{
    if (str.empty())
        return false;

    for (usize i = 0; i < str.size(); ++i)
    {
        if (!std::isalpha(str[i]) && !std::isdigit(str[i]))
            return false;
    }
    return true;
}

bool
ztd::isalpha(std::string_view str) noexcept
{
    if (str.empty())
        return false;

    for (usize i = 0; i < str.size(); ++i)
    {
        if (!std::isalpha(str[i]))
            return false;
    }
    return true;
}

bool
ztd::isdecimal(std::string_view str) noexcept
{
    if (str.empty())
        return false;

    for (usize i = 0; i < str.size(); ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

bool
ztd::islower(std::string_view str) noexcept
{
    if (str.empty())
        return false;

    for (usize i = 0; i < str.size(); ++i)
    {
        if (std::isalpha(str[i]) && !std::islower(str[i]))
            return false;
    }
    return true;
}

bool
ztd::isupper(std::string_view str) noexcept
{
    if (str.empty())
        return false;

    for (usize i = 0; i < str.size(); ++i)
    {
        if (std::isalpha(str[i]) && !std::isupper(str[i]))
            return false;
    }
    return true;
}

bool
ztd::isspace(std::string_view str) noexcept
{
    if (str.empty())
        return false;

    for (usize i = 0; i < str.size(); ++i)
    {
        if (!std::isspace(str[i]))
            return false;
    }
    return true;
}

bool
ztd::istitle(std::string_view str) noexcept
{
    if (str.empty())
        return false;

    bool in_word = false;
    u32 in_word_count = 0;

    for (usize i = 0; i < str.size(); ++i)
    {
        if (std::isalpha(str[i]))
        {
            in_word = true;

            if (in_word_count == 0)
            {
                if (!std::isupper(str[i]))
                    return false;
            }
            else
            {
                if (!std::islower(str[i]))
                    return false;
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
ztd::title(std::string_view str) noexcept
{
    if (str.empty())
        return std::string("");

    bool in_word = false;
    u32 in_word_count = 0;

    std::string title_str;
    for (usize i = 0; i < str.size(); ++i)
    {
        if (std::isalpha(str[i]))
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
ztd::swapcase(std::string_view str) noexcept
{
    if (str.empty())
        return std::string("");

    std::string swapcase_str;
    for (usize i = 0; i < str.size(); ++i)
    {
        if (std::isalpha(str[i]))
        {
            if (std::isupper(str[i]))
            {
                swapcase_str.append(lower(std::string(str.substr(i, 1))));
            }
            else if (std::islower(str[i]))
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
ztd::ljust(std::string_view str, usize width, char fillchar) noexcept
{
    if (str.size() >= width)
        return str.data();

    const u64 w = width - str.size();

    std::string ljust_str;
    ljust_str.append(str);
    ljust_str.append(w, fillchar);
    return ljust_str;
}

const std::string
ztd::rjust(std::string_view str, usize width, char fillchar) noexcept
{
    if (str.size() >= width)
        return str.data();

    const u64 w = width - str.size();

    std::string rjust_str;
    rjust_str.append(w, fillchar);
    rjust_str.append(str);
    return rjust_str;
}

const std::string
ztd::lstrip(std::string_view str, std::string_view chars) noexcept
{
    const usize start_pos = str.find_first_not_of(chars);
    if (start_pos == std::string_view::npos)
        return std::string("");
    return std::string(str.substr(start_pos));
}

const std::string
ztd::rstrip(std::string_view str, std::string_view chars) noexcept
{
    const usize end_pos = str.find_last_not_of(chars);
    if (end_pos == std::string_view::npos)
        return std::string("");
    return std::string(str.substr(0, end_pos + 1));
}

const std::string
ztd::strip(std::string_view str, std::string_view chars) noexcept
{
    return lstrip(rstrip(str, chars), chars);
}

const std::string
ztd::removeprefix(std::string_view str, std::string_view prefix) noexcept
{
    if (!startswith(str, prefix))
        return str.data();
    return std::string(str.substr(prefix.size(), str.size()));
}

const std::string
ztd::removesuffix(std::string_view str, std::string_view suffix) noexcept
{
    if (!endswith(str, suffix))
        return str.data();
    return std::string(str.substr(0, str.size() - suffix.size()));
}

const std::array<std::string, 3>
ztd::partition(std::string_view str, std::string_view sep) noexcept
{
    const usize index = str.find(sep);
    if (index == std::string_view::npos)
        return {std::string(str), std::string(""), std::string("")};

    const std::string_view begin{str.substr(0, index)};
    const std::string_view end{str.substr(index + sep.size())};

    return {std::string(begin), std::string(sep), std::string(end)};
}

const std::array<std::string, 3>
ztd::rpartition(std::string_view str, std::string_view sep) noexcept
{
    const usize index = str.rfind(sep);
    if (index == std::string_view::npos)
        return {std::string(""), std::string(""), std::string(str)};

    const std::string_view begin{str.substr(0, index)};
    const std::string_view end{str.substr(index + sep.size())};

    return {std::string(begin), std::string(sep), std::string(end)};
}

const std::string
ztd::zfill(std::string_view str, usize width) noexcept
{
    if (str.size() >= width)
        return str.data();

    const u64 w = width - str.size();

    std::string zstr;
    if (str[0] == '+')
    {
        zstr.append("+");
        zstr.append(w, '0');
        zstr.append(str, 1);
    }
    else if (str[0] == '-')
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

    return zstr;
}
