/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include <format>

#include <array>
#include <unordered_map>
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

namespace detail
{
// clang-format off
const std::unordered_map<ztd::filesize_type, std::array<std::string, 2>> unit_labels{
    {ztd::filesize_type::byte,       {"B",  "B"  }},
    {ztd::filesize_type::kilobyte,   {"KB", "KiB"}},
    {ztd::filesize_type::megabyte,   {"MB", "MiB"}},
    {ztd::filesize_type::gigabyte,   {"GB", "GiB"}},
    {ztd::filesize_type::terrabyte,  {"TB", "TiB"}},
    {ztd::filesize_type::petabyte,   {"PB", "PiB"}},
    {ztd::filesize_type::exabyte,    {"EB", "EiB"}},
    {ztd::filesize_type::zettabyte,  {"ZB", "ZiB"}},
    {ztd::filesize_type::yottabyte,  {"YB", "YiB"}},
    {ztd::filesize_type::ronnabyte,  {"RB", "RiB"}},
    {ztd::filesize_type::quettabyte, {"QB", "QiB"}},
};
// clang-format on

constexpr u64 SI = 0;
constexpr u64 IEC = 1;

static constexpr f64 base_unit_size_iec{1024.0};
static constexpr f64 base_unit_size_si{1000.0};
} // namespace detail

struct FileSize
{
  public:
    FileSize() = delete;

    /**
     * @brief FileSize
     *
     * @param[in] size_in_bytes file size in bytes
     */
    FileSize(u64 size_in_bytes)
    {
        if (size_in_bytes == 0)
        {
            this->unit_type = ztd::filesize_type::byte;
            this->unit_label = detail::unit_labels.at(this->unit_type)[detail::IEC];
            return;
        }

        f64 size = static_cast<f64>(size_in_bytes);

        usize size_idx = 0;
        while (size >= detail::base_unit_size_iec)
        {
            size /= detail::base_unit_size_iec;
            size_idx += 1;
        }
        this->unit_type = ztd::filesize_type(size_idx);
        this->unit_label = detail::unit_labels.at(this->unit_type)[detail::IEC];
        this->unit_size = size;
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
    [[nodiscard]] const std::string
    get_formated_size(u32 precision = 1) const noexcept
    {
        // do not show decimals for bytes
        if (this->is_byte())
        {
            precision = 0;
        }
        return std::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
    }

    /**
     * @brief Get Filesize Parts
     *
     * - Get raw filesize and unit label
     *
     * @return The filesize and filesize label
     */
    [[nodiscard]] const std::tuple<f64, std::string>
    get_filesize_parts() const noexcept
    {
        return {this->unit_size, this->unit_label.data()};
    }

    [[nodiscard]] bool
    is_byte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::byte);
    }

    [[nodiscard]] bool
    is_kilobyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::kilobyte);
    }

    [[nodiscard]] bool
    is_megabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::megabyte);
    }

    [[nodiscard]] bool
    is_gigabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::gigabyte);
    }

    [[nodiscard]] bool
    is_terrabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::terrabyte);
    }

    [[nodiscard]] bool
    is_petabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::petabyte);
    }

    [[nodiscard]] bool
    is_exabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::exabyte);
    }

    [[nodiscard]] bool
    is_zettabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::zettabyte);
    }

    [[nodiscard]] bool
    is_yottabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::yottabyte);
    }

    [[nodiscard]] bool
    is_ronnabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::ronnabyte);
    }

    [[nodiscard]] bool
    is_quettabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::quettabyte);
    }

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
    f64 unit_size{0};
    std::string unit_label;
    filesize_type unit_type;
};

struct FileSizeSI
{
  public:
    FileSizeSI() = delete;

    /**
     * @brief FileSizeSI
     *
     * @param[in] size_in_bytes file size in bytes
     */
    FileSizeSI(u64 size_in_bytes)
    {
        if (size_in_bytes == 0)
        {
            this->unit_type = ztd::filesize_type::byte;
            this->unit_label = detail::unit_labels.at(this->unit_type)[detail::SI];
            return;
        }

        f64 size = static_cast<f64>(size_in_bytes);

        usize size_idx = 0;
        while (size >= detail::base_unit_size_si)
        {
            size /= detail::base_unit_size_si;
            size_idx += 1;
        }
        this->unit_type = ztd::filesize_type(size_idx);
        this->unit_label = detail::unit_labels.at(this->unit_type)[detail::SI];
        this->unit_size = size;
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
    [[nodiscard]] const std::string
    get_formated_size(u32 precision = 1) const noexcept
    {
        // do not show decimals for bytes
        if (this->is_byte())
        {
            precision = 0;
        }
        return std::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
    }

    /**
     * @brief Get Filesize Parts
     *
     * - Get raw filesize and unit label
     *
     * @return The filesize and filesize label
     */
    [[nodiscard]] const std::tuple<f64, std::string>
    get_filesize_parts() const noexcept
    {
        return {this->unit_size, this->unit_label.data()};
    }

    [[nodiscard]] bool
    is_byte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::byte);
    }

    [[nodiscard]] bool
    is_kilobyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::kilobyte);
    }

    [[nodiscard]] bool
    is_megabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::megabyte);
    }

    [[nodiscard]] bool
    is_gigabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::gigabyte);
    }

    [[nodiscard]] bool
    is_terrabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::terrabyte);
    }

    [[nodiscard]] bool
    is_petabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::petabyte);
    }

    [[nodiscard]] bool
    is_exabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::exabyte);
    }

    [[nodiscard]] bool
    is_zettabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::zettabyte);
    }

    [[nodiscard]] bool
    is_yottabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::yottabyte);
    }

    [[nodiscard]] bool
    is_ronnabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::ronnabyte);
    }

    [[nodiscard]] bool
    is_quettabyte() const noexcept
    {
        return (this->unit_type == ztd::filesize_type::quettabyte);
    }

  private:
    f64 unit_size{0};
    std::string unit_label;
    filesize_type unit_type;
};

enum class format_base
{
#if (ZTD_VERSION == 1)
    IEC, // 2^10 // Deprecated
    SI,  // 10^3 // Deprecated
#endif
    iec, // 2^10
    si,  // 10^3
};

/**
 * FileSize Convenience Wrapper
 */
[[nodiscard]] inline const std::string
format_filesize(u64 size_in_bytes, format_base base = format_base::iec, u32 precision = 1)
{
    if (base == format_base::iec
#if (ZTD_VERSION == 1)
        || base == format_base::IEC
#endif
    )
    {
        return FileSize(size_in_bytes).get_formated_size(precision);
    }
    else // format_base::si || format_base::SI
    {
        return FileSizeSI(size_in_bytes).get_formated_size(precision);
    }
}
} // namespace ztd
