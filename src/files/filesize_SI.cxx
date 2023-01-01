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

#include <fmt/format.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/files/filesize_SI.hxx"

inline constexpr std::array<std::string_view, 9> unit_labels_si{
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
    this->is_unit_size_byte = (size_idx == 0);
    this->unit_label = unit_labels_si.at(size_idx);
}

const std::string
ztd::FileSizeSI::get_formated_size(u32 precision) const noexcept
{
    // do not show decimals for bytes
    if (this->is_unit_size_byte)
        precision = 0;
    return fmt::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
}

const std::pair<f64, const std::string>
ztd::FileSizeSI::get_filesize_parts() const noexcept
{
    return {this->unit_size, this->unit_label.data()};
}
