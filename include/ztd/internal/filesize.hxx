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

#pragma once

#include <string>
#include <string_view>

#include <array>

#include "types.hxx"

namespace ztd
{
    class FileSize
    {
      public:
        FileSize() = delete;

        /**
         * @brief FileSize
         *
         * @param[in] size_in_bytes file size in bytes
         */
        FileSize(u64 size_in_bytes);

        /**
         * @brief Get Formated Size
         *
         * - Get the filesize in a formated string with unit size
         *
         * @param[in] precision the total number of decimal places to include
         *
         * @return The filesize in a std::string
         */
        [[nodiscard]] const std::string get_formated_size(u32 precision = 1) const noexcept;

        /**
         * @brief Get Filesize Parts
         *
         * - Get raw filesize and unit label
         *
         * @return The filesize and filesize label
         */
        [[nodiscard]] const std::pair<ztd::f64, const std::string> get_filesize_parts() const noexcept;

      private:
        ztd::f64 unit_size{0};
        std::string_view unit_label;

        bool is_unit_size_byte{true};
    };

    class FileSizeSI
    {
      public:
        FileSizeSI() = delete;

        /**
         * @brief FileSizeSI
         *
         * @param[in] size_in_bytes file size in bytes
         */
        FileSizeSI(u64 size_in_bytes);

        /**
         * @brief Get Formated Size
         *
         * - Get the filesize in a formated string with unit size
         *
         * @param[in] precision the total number of decimal places to include
         *
         * @return The filesize in a std::string
         */
        [[nodiscard]] const std::string get_formated_size(u32 precision = 1) const noexcept;

        /**
         * @brief Get Filesize Parts
         *
         * - Get raw filesize and unit label
         *
         * @return The filesize and filesize label
         */
        [[nodiscard]] const std::pair<ztd::f64, const std::string> get_filesize_parts() const noexcept;

      private:
        ztd::f64 unit_size{0};
        std::string_view unit_label;

        bool is_unit_size_byte{true};
    };
} // namespace ztd
