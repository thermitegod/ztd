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

#include <tuple>

#include "types.hxx"

namespace ztd
{
    enum class filesize_type
    {
        byte,
        kilobyte,
        megabyte,
        gigabyte,
        terrabyte,
        petabyte,
        exabyte,
        zettabyte,
        yottabyte,
        ronnabyte,
        quettabyte,
    };

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
        [[nodiscard]] const std::tuple<ztd::f64, std::string> get_filesize_parts() const noexcept;

        [[nodiscard]] bool is_byte() const noexcept;
        [[nodiscard]] bool is_kilobyte() const noexcept;
        [[nodiscard]] bool is_megabyte() const noexcept;
        [[nodiscard]] bool is_gigabyte() const noexcept;
        [[nodiscard]] bool is_terrabyte() const noexcept;
        [[nodiscard]] bool is_petabyte() const noexcept;
        [[nodiscard]] bool is_exabyte() const noexcept;
        [[nodiscard]] bool is_zettabyte() const noexcept;
        [[nodiscard]] bool is_yottabyte() const noexcept;
        [[nodiscard]] bool is_ronnabyte() const noexcept;
        [[nodiscard]] bool is_quettabyte() const noexcept;

        // TODO: these should be function pointers
        // clang-format off
        [[nodiscard]] bool is_kibibyte() const noexcept { return this->is_kilobyte();  };
        [[nodiscard]] bool is_mebibyte() const noexcept { return this->is_megabyte();  };
        [[nodiscard]] bool is_gibibyte() const noexcept { return this->is_gigabyte();  };
        [[nodiscard]] bool is_tebibyte() const noexcept { return this->is_terrabyte(); };
        [[nodiscard]] bool is_pebibyte() const noexcept { return this->is_petabyte();  };
        [[nodiscard]] bool is_exbibyte() const noexcept { return this->is_exabyte();   };
        [[nodiscard]] bool is_zebibyte() const noexcept { return this->is_zettabyte(); };
        [[nodiscard]] bool is_yobibyte() const noexcept { return this->is_yottabyte(); };
        [[nodiscard]] bool is_robibyte() const noexcept { return this->is_ronnabyte(); };
        [[nodiscard]] bool is_qubibyte() const noexcept { return this->is_quettabyte(); };
        // clang-format on

      private:
        ztd::f64 unit_size{0};
        std::string unit_label;
        filesize_type unit_type;
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
        [[nodiscard]] const std::tuple<ztd::f64, std::string> get_filesize_parts() const noexcept;

        [[nodiscard]] bool is_byte() const noexcept;
        [[nodiscard]] bool is_kilobyte() const noexcept;
        [[nodiscard]] bool is_megabyte() const noexcept;
        [[nodiscard]] bool is_gigabyte() const noexcept;
        [[nodiscard]] bool is_terrabyte() const noexcept;
        [[nodiscard]] bool is_petabyte() const noexcept;
        [[nodiscard]] bool is_exabyte() const noexcept;
        [[nodiscard]] bool is_zettabyte() const noexcept;
        [[nodiscard]] bool is_yottabyte() const noexcept;
        [[nodiscard]] bool is_ronnabyte() const noexcept;
        [[nodiscard]] bool is_quettabyte() const noexcept;

      private:
        ztd::f64 unit_size{0};
        std::string unit_label;
        filesize_type unit_type;
    };

    enum class format_base
    {
        IEC, // 2^10 // Deprecated
        SI,  // 10^3 // Deprecated

        iec, // 2^10
        si,  // 10^3
    };

    /**
     * FileSize Convenience Wrapper
     */
    [[nodiscard]] const std::string format_filesize(u64 size_in_bytes, format_base base = format_base::iec,
                                                    u32 precision = 1);
} // namespace ztd
