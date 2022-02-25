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

#ifndef ZTD_MAIN_HEADER
#error "Only <ztd.hxx> can be included directly"
#endif

#pragma once

#include <string>

namespace ztd
{
    /**
     *
     * Filesystem Paths
     *
     * Cannot use variadic functions when the args are std::string.
     * This is not the ideal solution, but it works.
     *
     */

    namespace
    {
        /**
         * @brief Remove double '//' from path
         *
         * @param[out] __path to clean
         *
         * @return modify in place the provided path
         */
        static inline void
        build_path_clean(std::string& __path) noexcept
        {
            while (contains(__path, "//"))
            {
                __path = replace(__path, "//", "/");
            }
        }

        /**
         * @brief Check path length is less than PATH_MAX
         *
         * @param[out] __path to check, throw std::logic_error if longer than PATH_MAX
         */
        static inline void
        build_path_check_max(std::string& __path)
        {
            if (__path.size() > PATH_MAX)
                throw std::logic_error("path length is longer than PATH_MAX");
        }
    } // namespace

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1) noexcept
    {
        std::string path;

        path.append(__p1);

        build_path_clean(path);
        build_path_check_max(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2);

        build_path_clean(path);
        build_path_check_max(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3);

        build_path_clean(path);
        build_path_check_max(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3,
               const std::string& __p4) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3 + "/");
        path.append(__p4);

        build_path_clean(path);
        build_path_check_max(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3,
               const std::string& __p4, const std::string& __p5) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3 + "/");
        path.append(__p4 + "/");
        path.append(__p5);

        build_path_clean(path);
        build_path_check_max(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3,
               const std::string& __p4, const std::string& __p5, const std::string& __p6) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3 + "/");
        path.append(__p4 + "/");
        path.append(__p5 + "/");
        path.append(__p6);

        build_path_clean(path);
        build_path_check_max(path);

        return path;
    }
} // namespace ztd
