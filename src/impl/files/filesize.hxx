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

    class FileSize
    {
      public:
        FileSize(){};
        ~FileSize(){};

        /**
         * @brief FileSize
         *
         * @param[in] size_in_bytes file size in bytes
         */
        FileSize(std::uint64_t size_in_bytes)
        {
            double unit_size = size_in_bytes;
            double base_unit_size = m_base_unit_size;

            std::size_t i = 0;
            for (; unit_size >= base_unit_size; unit_size /= base_unit_size, ++i) {}

            m_unit_size = unit_size;

            if (i == 0)
                return;

            m_is_unit_size_byte = false;
            m_unit_label = m_unit_labels[i];
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
            if (m_is_unit_size_byte)
                return get_formated_size_byte();

            return fmt::format("{:.{}f} {}", m_unit_size, precision, m_unit_label);
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
            return {m_unit_size, m_unit_label};
        }

      private:
        /**
         * @brief Byte file sizes do not need decimal places
         */
        inline const std::string
        get_formated_size_byte() noexcept
        {
            return fmt::format("{:.0f} {}", m_unit_size, m_unit_labels[0]);
        }

        static constexpr std::array<std::string_view, 9> m_unit_labels{
            "B"sv,
            "KiB"sv,
            "MiB"sv,
            "GiB"sv,
            "TiB"sv,
            "PiB"sv,
            "EiB"sv,
            "ZiB"sv,
            "YiB"sv,
        };

        double m_unit_size{0};
        std::string m_unit_label{m_unit_labels[0]};

        bool m_is_unit_size_byte{true};

        const double m_base_unit_size{1024.0};
    };
} // namespace ztd
