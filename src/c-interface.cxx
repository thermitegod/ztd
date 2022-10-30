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

#include <type_traits>

#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "ztd/internal/types.hxx"

#include "ztd/internal/c-interface.hxx"

const std::string
ztd::null_check(const char* str) noexcept
{
    if (!str)
        return std::string("");
    return str;
}

char*
ztd::strdup(const char* str) noexcept
{
    if (!str)
        return nullptr;
    return strndup(str, std::strlen(str));
}

char*
ztd::strdup(const std::string* str) noexcept
{
    if (!str)
        return nullptr;
    return strndup(str->c_str(), str->size());
}

char*
ztd::strdup(const std::string& str) noexcept
{
    return strndup(str.c_str(), str.size());
}