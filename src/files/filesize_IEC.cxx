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

ztd::FileSize::FileSize(u64 size_in_bytes)
{
    f64 size = static_cast<f64>(size_in_bytes);

    usize idx = 0;
    while (size >= this->base_unit_size)
    {
        size /= this->base_unit_size;
        idx += 1;
    }

    this->unit_size = size;

    if (idx == 0)
        return;

    this->is_unit_size_byte = false;
    this->unit_label = this->unit_labels[idx];
}

const std::string
ztd::FileSize::get_formated_size(u32 precision) noexcept
{
    // do not show decimals for bytes
    if (this->is_unit_size_byte)
        return get_formated_size_byte();
    return fmt::format("{:.{}f} {}", this->unit_size, precision, this->unit_label);
}

const std::pair<f64, const std::string>
ztd::FileSize::get_filesize_parts() noexcept
{
    return {this->unit_size, this->unit_label.data()};
}

const std::string
ztd::FileSize::get_formated_size_byte() noexcept
{
    return fmt::format("{:.0f} {}", this->unit_size, this->unit_labels[0]);
}
