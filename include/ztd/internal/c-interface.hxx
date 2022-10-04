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

#pragma once

#include <string>

#include <type_traits>

#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "types.hxx"

namespace ztd
{
    /**
     * @brief Null Check
     *
     * - Checks if the char* is NULL and if it is return an empty std::string.
     * Setting a std::string to NULL is UB and, nobody likes segfaults
     *
     * @param[in] str The char* to be checked for NULL
     *
     * @return an empty std::string if char* is NULL
     */
    const std::string null_check(const char* str) noexcept;

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] str string to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    char* strdup(const char* str) noexcept;

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] str string to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    char* strdup(const std::string* str) noexcept;

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] str string to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    char* strdup(const std::string& str) noexcept;

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, char*>::type
    strdup(T val) noexcept
    {
        const std::string str = std::to_string(val);
        return strndup(str.c_str(), str.size());
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, char*>::type
    strdup(T val) noexcept
    {
        const std::string str = std::to_string(val);
        return strndup(str.c_str(), str.size());
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    template<typename T>
    typename std::enable_if<std::is_enum<T>::value, char*>::type
    strdup(T val) noexcept
    {
        const std::string str = std::to_string(static_cast<u32>(val));
        return strndup(str.c_str(), str.size());
    }
} // namespace ztd
