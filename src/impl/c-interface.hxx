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
     * @param[in] str The char* to be checked for NULL
     *
     * @return an empty std::string if char* is NULL
     */
    static inline const std::string
    null_check(const char* str) noexcept
    {
        if (!str)
            return std::string("");
        return str;
    }

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
    static inline char*
    strdup(const char* str) noexcept
    {
        if (!str)
            return nullptr;
        return strndup(str, std::strlen(str));
    }

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
    static inline char*
    strdup(const std::string& str) noexcept
    {
        return strndup(str.c_str(), str.size());
    }

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
    static inline char*
    strdup(const std::string* str) noexcept
    {
        return strndup(str->c_str(), str->size());
    }

    namespace
    {
        template<typename T>
        static inline char*
        _private_strdup(const T& val) noexcept
        {
            const std::string str = std::to_string(val);
            return strndup(str.c_str(), str.size());
        }
    } // namespace

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
    static inline char*
    strdup(int val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(unsigned int val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(long val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(unsigned long val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(long long val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(unsigned long long val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(float val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(double val) noexcept
    {
        return _private_strdup(val);
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
    static inline char*
    strdup(long double val) noexcept
    {
        return _private_strdup(val);
    }

#if 0
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
    template<typename NumType>
    static inline char*
    strdup(NumType val) noexcept
    {
        static_assert(std::is_arithmetic<NumType>::value, "NumType must be a numeric type");
        const std::string str = std::to_string(val);
        return strndup(str.c_str(), str.size());
    }
#endif
} // namespace ztd
