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

#ifndef ZTD_MAIN_HEADER
#error "Only <ztd.hxx> can be included directly"
#endif

#pragma once

#include <string>

#include <cstring>
#include <cstdio>
#include <cstdlib>

namespace ztd
{
    /**
     * @brief Null Check
     *
     * - Checks if the char* is NULL and if it is return an empty std::string.
     * Setting a std::string to NULL is UB and, nobody likes segfaults
     *
     * @param[in] __str The char* to be checked for NULL
     *
     * @return an empty std::string if char* is NULL
     */
    static inline std::string
    null_check(const char* __str) noexcept
    {
        if (!__str)
            return "";

        return __str;
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __str string to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(const char* __str) noexcept
    {
        if (!__str)
            return nullptr;
        return strndup(__str, std::strlen(__str));
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __str string to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(const std::string& __str) noexcept
    {
        return strndup(__str.c_str(), __str.size());
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __str string to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(const std::string* __str) noexcept
    {
        return strndup(__str->c_str(), __str->size());
    }

    namespace
    {
        template<typename T>
        static inline char*
        _private_strdup(const T __val) noexcept
        {
            const std::string new_string = std::to_string(__val);
            return strndup(new_string.c_str(), new_string.size());
        }
    } // namespace

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(int __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(unsigned int __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(long __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(unsigned long __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(long long __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(unsigned long long __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(float __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(double __val) noexcept
    {
        return _private_strdup(__val);
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[in] __val value to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(long double __val) noexcept
    {
        return _private_strdup(__val);
    }
} // namespace ztd
