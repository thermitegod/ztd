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
#include <string_view>

#include <array>

#include "../types.hxx"

namespace ztd
{
    class FileSizeSI
    {
      public:
        FileSizeSI() = default;

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
        const std::string get_formated_size(u32 precision = 1) noexcept;

        /**
         * @brief Get Filesize Parts
         *
         * - Get raw filesize and unit label
         *
         * @return The filesize and filesize label
         */
        const std::pair<f64, const std::string> get_filesize_parts() noexcept;

      private:
        /**
         * @brief Byte file sizes do not need decimal places
         */
        const std::string get_formated_size_byte() noexcept;

      private:
        static constexpr std::array<std::string_view, 9> unit_labels{
            "B",
            "KB",
            "MB",
            "GB",
            "TB",
            "PB",
            "EB",
            "ZB",
            "YB",
        };

        f64 unit_size{0};
        std::string_view unit_label{this->unit_labels[0]};

        bool is_unit_size_byte{true};

        static constexpr f64 base_unit_size{1000.0};
    };
} // namespace ztd
