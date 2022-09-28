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

#ifndef ZTD_FILES_HEADER
#error "Only <ztd-files.hxx> can be included directly"
#endif

#pragma once

#include <string>
#include <string_view>

#include <array>

#include <fmt/format.h>

namespace ztd
{
    namespace
    {
        // std::literals::string_view_literals::operator""sv
        using namespace std::literals::string_view_literals;
    } // namespace

    class FileSizeSI
    {
      public:
        FileSizeSI(){};
        ~FileSizeSI(){};

        /**
         * @brief FileSizeSI
         *
         * @param[in] size_in_bytes file size in bytes
         */
        FileSizeSI(std::uint64_t size_in_bytes)
        {
            double size = size_in_bytes;

            std::size_t i = 0;
            for (; size >= this->base_unit_size; size /= this->base_unit_size, ++i) {}

            this->unit_size = size;

            if (i == 0)
                return;

            this->is_unit_size_byte = false;
            this->unit_label = this->unit_labels[i];
        }

        /**
         * @brief Get Formated Size
         *
         * - Get the filesize in a formated string with unit size
         *
         * @param[in] precision the total number of decimal places to include
         *
         * @return The filesize in a std::string
         */
        inline const std::string
        get_formated_size(unsigned int precision = 1) noexcept
        {
            // do not show decimals for bytes
            if (this->is_unit_size_byte)
                return get_formated_size_byte();
            return fmt::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
        }

        /**
         * @brief Get Filesize Parts
         *
         * - Get raw filesize and unit label
         *
         * @return The filesize and filesize label
         */
        inline const std::pair<double, const std::string>
        get_filesize_parts() noexcept
        {
            return {this->unit_size, this->unit_label.data()};
        }

      private:
        /**
         * @brief Byte file sizes do not need decimal places
         */
        inline const std::string
        get_formated_size_byte() noexcept
        {
            return fmt::format("{:.0f} {}", this->unit_size, this->unit_labels[0]);
        }

      private:
        static constexpr std::array<std::string_view, 9> unit_labels{
            "B"sv,
            "KB"sv,
            "MB"sv,
            "GB"sv,
            "TB"sv,
            "PB"sv,
            "EB"sv,
            "ZB"sv,
            "YB"sv,
        };

        double unit_size{0};
        std::string_view unit_label{this->unit_labels[0]};

        bool is_unit_size_byte{true};

        const double base_unit_size{1000.0};
    };
} // namespace ztd
