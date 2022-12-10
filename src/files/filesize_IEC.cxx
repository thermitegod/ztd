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

#include <string>
#include <string_view>

#include <fmt/format.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/files/filesize_IEC.hxx"

inline constexpr std::array<std::string_view, 9> unit_labels_iec{
    "B",
    "KiB",
    "MiB",
    "GiB",
    "TiB",
    "PiB",
    "EiB",
    "ZiB",
    "YiB",
};

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
    this->is_unit_size_byte = (size_idx == 0);
    this->unit_label = unit_labels_iec.at(size_idx);
}

const std::string
ztd::FileSize::get_formated_size(u32 precision) const noexcept
{
    // do not show decimals for bytes
    if (this->is_unit_size_byte)
        precision = 0;
    return fmt::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
}

const std::pair<f64, const std::string>
ztd::FileSize::get_filesize_parts() const noexcept
{
    return {this->unit_size, this->unit_label.data()};
}
