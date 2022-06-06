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
#include <vector>

#include <cstdint>

#include <utility>

#include <fmt/format.h>

namespace ztd
{
    enum class FileSizePrecision
    {
        PRECISION_0,
        PRECISION_1,
        PRECISION_2,
        PRECISION_3,
    };

    namespace
    {
        class FileSizeBase
        {
          public:
            /**
             * @brief FileSizeBase
             *
             * - FileSizeBase Constructor
             */
            FileSizeBase(){};

            /**
             * @brief FileSizeBase Destructor
             */
            ~FileSizeBase(){};

            /**
             * @brief Init
             *
             * - Initialize FileSizeBase class
             *
             * @param[in] size_in_bytes file size in bytes
             * @param[in] si format filesize using base 1000, otherwise use base 1024
             *
             * @return The filesize in a std::string
             */
            inline void
            Init(std::uint64_t size_in_bytes, bool si) noexcept
            {
                double unit_size = size_in_bytes;

                double base_unit_size;
                if (si)
                    base_unit_size = m_base_unit_size_si;
                else
                    base_unit_size = m_base_unit_size;

                std::size_t i = 0;
                for (; unit_size >= base_unit_size; unit_size /= base_unit_size, ++i) {}

                m_unit_size = unit_size;

                if (i != 0)
                    m_is_unit_size_byte = false;

                if (si)
                    m_unit_label = m_unit_labels[i].second;
                else
                    m_unit_label = m_unit_labels[i].first;
            }

            /**
             * @brief Get Formated Size
             *
             * - Get the filesize in a formated string with unit size
             *
             * @param[in] precision enum value representing the total number
             * of decimal places to include
             *
             * @return The filesize in a std::string
             */
            inline const std::string
            get_formated_size(FileSizePrecision precision = FileSizePrecision::PRECISION_1) noexcept
            {
                // do not show decimals for bytes
                if (m_is_unit_size_byte)
                    return fmt::format("{:.0f} {}", m_unit_size, m_unit_labels[0].first);

                std::string format;
                switch (precision)
                {
                    case FileSizePrecision::PRECISION_0:
                        format = fmt::format("{:.0f} {}", m_unit_size, m_unit_label);
                        break;
                    case FileSizePrecision::PRECISION_1:
                        format = fmt::format("{:.1f} {}", m_unit_size, m_unit_label);
                        break;
                    case FileSizePrecision::PRECISION_2:
                        format = fmt::format("{:.2f} {}", m_unit_size, m_unit_label);
                        break;
                    case FileSizePrecision::PRECISION_3:
                        format = fmt::format("{:.3f} {}", m_unit_size, m_unit_label);
                        break;
                }
                return format;
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
             * Zettabyte and Yottabyte support is disabled because there are no
             * integer types large enough to hold their size in bytes.
             * They can be enabled when the C++ standard has uint128_t.
             */
            const std::vector<std::pair<const std::string, const std::string>> m_unit_labels{
                {"B", "B"},
                {"KiB", "KB"},
                {"MiB", "MB"},
                {"GiB", "GB"},
                {"TiB", "TB"},
                {"PiB", "PB"},
                {"EiB", "EB"},
                // {"ZiB", "ZB"},
                // {"YiB", "YB"},
            };

            double m_unit_size{0};
            std::string m_unit_label{m_unit_labels[0].first};

            bool m_is_unit_size_byte{true};

            const double m_base_unit_size{1024.0};
            const double m_base_unit_size_si{1000.0};
        };

    } // namespace

    /**
     *
     * FileSize wrapper
     *
     */

    class FileSize: public FileSizeBase
    {
      public:
        /**
         * @brief FileSize
         *
         * - FileSize Constructor
         */
        FileSize(){};

        /**
         * @brief FileSize Destructor
         */
        ~FileSize(){};

        /**
         * @brief FileSize
         *
         * - FileSize Constructor
         *
         * @param[in] size_in_bytes file size in bytes
         */
        FileSize(std::uint64_t size_in_bytes)
        {
            Init(size_in_bytes, false);
        }
    };

    /**
     *
     * FileSizeSI wrapper
     *
     */

    class FileSizeSI: public FileSizeBase
    {
      public:
        /**
         * @brief FileSizeSI
         *
         * - FileSizeSI Constructor
         */
        FileSizeSI(){};

        /**
         * @brief FileSizeSI Destructor
         */
        ~FileSizeSI(){};

        /**
         * @brief FileSizeSI
         *
         * - FileSizeSI Constructor
         *
         * @param[in] size_in_bytes file size in bytes
         */
        FileSizeSI(std::uint64_t size_in_bytes)
        {
            Init(size_in_bytes, true);
        }
    };
} // namespace ztd
