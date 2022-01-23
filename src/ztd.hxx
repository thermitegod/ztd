/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>

#include <vector>

namespace ztd
{
    /// std::string functions ///

    std::string lower(const std::string& str);
    std::string upper(const std::string& str);

    bool contains(const std::string& haystack, const std::string& needle);
    bool contains(const std::string& haystack, const char needle);

    bool contains_any(const std::string& haystack, const std::vector<std::string>& needles);

    bool same(const std::string& str1, const std::string& str2);
    bool not_same(const std::string& str1, const std::string& str2);

    bool isame(const std::string& str1, const std::string& str2);
    bool not_isame(const std::string& str1, const std::string& str2);

    bool prefix(const std::string& str, const std::string& prefix);
    bool suffix(const std::string& str, const std::string& suffix);

    std::string replace(const std::string& str, const std::string& str_find,
                        const std::string& str_replace);
    std::string replace_first(const std::string& str, const std::string& str_find,
                              const std::string& str_replace);
    std::string replace_last(const std::string& str, const std::string& str_find,
                             const std::string& str_replace);
    std::string replace_multiple(const std::string& str, const std::vector<std::string>& vec_find,
                                 const std::string& str_replace);

    std::string ltrim(const std::string& str);
    std::string rtrim(const std::string& str);
    std::string trim(const std::string& str);

    /// std::string to/from std::vector ///

    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    std::string join(const std::vector<std::string>& tokens, const std::string& delimiter);

    /// Filesystem  ///

    std::string build_path(const std::string& p1);
    std::string build_path(const std::string& p1, const std::string& p2);
    std::string build_path(const std::string& p1, const std::string& p2, const std::string& p3);
    std::string build_path(const std::string& p1, const std::string& p2, const std::string& p3,
                           const std::string& p4);
    std::string build_path(const std::string& p1, const std::string& p2, const std::string& p3,
                           const std::string& p4, const std::string& p5);
    std::string build_path(const std::string& p1, const std::string& p2, const std::string& p3,
                           const std::string& p4, const std::string& p5, const std::string& p6);

    /// Lazy functions ///

    bool not_empty(const std::string& str);
    void clear(std::string& str);

    /// C Interface ///

    std::string null_check(const char* str);
    const char* empty_null(const std::string& str);

} // namespace ztd
