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

#include <string>
#include <string_view>

#include <array>
#include <map>

#include <fmt/format.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/filesize.hxx"

// clang-format off
const std::map<ztd::filesize_type, std::array<std::string, 2>> unit_labels{
    {ztd::filesize_type::byte,      {"B",  "B"  }},
    {ztd::filesize_type::kilobyte,  {"KB", "KiB"}},
    {ztd::filesize_type::megabyte,  {"MB", "MiB"}},
    {ztd::filesize_type::gigabyte,  {"GB", "GiB"}},
    {ztd::filesize_type::terrabyte, {"TB", "TiB"}},
    {ztd::filesize_type::petabyte,  {"PB", "PiB"}},
    {ztd::filesize_type::exabyte,   {"EB", "EiB"}},
    {ztd::filesize_type::zettabyte, {"ZB", "ZiB"}},
    {ztd::filesize_type::yottabyte, {"YB", "YiB"}},
};
// clang-format on

constexpr u64 SI = 0;
constexpr u64 IEC = 1;

/**
 * Filesize IEC
 */

static constexpr ztd::f64 base_unit_size_iec{1024.0};

ztd::FileSize::FileSize(u64 size_in_bytes)
{
    f64 size = static_cast<f64>(size_in_bytes);

    usize size_idx = 0;
    while (size >= base_unit_size_iec)
    {
        size /= base_unit_size_iec;
        size_idx += 1;
    }

    this->unit_size = size;
    this->unit_type = ztd::filesize_type(size_idx);
    this->unit_label = unit_labels.at(this->unit_type)[IEC];
}

const std::string
ztd::FileSize::get_formated_size(u32 precision) const noexcept
{
    // do not show decimals for bytes
    if (this->is_byte())
    {
        precision = 0;
    }
    return fmt::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
}

const std::pair<f64, const std::string>
ztd::FileSize::get_filesize_parts() const noexcept
{
    return {this->unit_size, this->unit_label.data()};
}

bool
ztd::FileSize::is_byte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::byte);
}

bool
ztd::FileSize::is_kilobyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::kilobyte);
}

bool
ztd::FileSize::is_megabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::megabyte);
}

bool
ztd::FileSize::is_gigabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::gigabyte);
}

bool
ztd::FileSize::is_terrabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::terrabyte);
}

bool
ztd::FileSize::is_petabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::petabyte);
}

bool
ztd::FileSize::is_exabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::exabyte);
}

bool
ztd::FileSize::is_zettabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::zettabyte);
}

bool
ztd::FileSize::is_yottabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::yottabyte);
}

/**
 * Filesize SI
 */

static constexpr ztd::f64 base_unit_size_si{1000.0};

ztd::FileSizeSI::FileSizeSI(u64 size_in_bytes)
{
    f64 size = static_cast<f64>(size_in_bytes);

    usize size_idx = 0;
    while (size >= base_unit_size_si)
    {
        size /= base_unit_size_si;
        size_idx += 1;
    }

    this->unit_size = size;
    this->unit_type = ztd::filesize_type(size_idx);
    this->unit_label = unit_labels.at(this->unit_type)[SI];
}

const std::string
ztd::FileSizeSI::get_formated_size(u32 precision) const noexcept
{
    // do not show decimals for bytes
    if (this->is_byte())
    {
        precision = 0;
    }
    return fmt::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
}

const std::pair<f64, const std::string>
ztd::FileSizeSI::get_filesize_parts() const noexcept
{
    return {this->unit_size, this->unit_label.data()};
}

bool
ztd::FileSizeSI::is_byte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::byte);
}

bool
ztd::FileSizeSI::is_kilobyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::kilobyte);
}

bool
ztd::FileSizeSI::is_megabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::megabyte);
}

bool
ztd::FileSizeSI::is_gigabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::gigabyte);
}

bool
ztd::FileSizeSI::is_terrabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::terrabyte);
}

bool
ztd::FileSizeSI::is_petabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::petabyte);
}

bool
ztd::FileSizeSI::is_exabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::exabyte);
}

bool
ztd::FileSizeSI::is_zettabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::zettabyte);
}

bool
ztd::FileSizeSI::is_yottabyte() const noexcept
{
    return (this->unit_type == ztd::filesize_type::yottabyte);
}
