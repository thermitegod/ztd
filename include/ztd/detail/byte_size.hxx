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

#include <format>

#include <algorithm>

#include <type_traits>

#include <magic_enum.hpp>

#include "map.hxx"
#include "types.hxx"

namespace ztd
{
class byte_iec
{
  public:
    byte_iec() = default;

    template<typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    constexpr byte_iec(const T& rhs) : value_(rhs)
    {
        this->calculate();
    }

    constexpr byte_iec
    operator+(const byte_iec& other) const
    {
        return this->value_ + other.value_;
    }

    constexpr byte_iec
    operator-(const byte_iec& other) const
    {
        return this->value_ - other.value_;
    }

    constexpr byte_iec
    operator*(const byte_iec& other) const
    {
        return this->value_ * other.value_;
    }

    constexpr byte_iec
    operator/(const byte_iec& other) const
    {
        return this->value_ / other.value_;
    }

    constexpr byte_iec
    operator%(const byte_iec& other) const
    {
        return this->value_ % other.value_;
    }

    constexpr byte_iec&
    operator+=(const byte_iec& rhs)
    {
        this->value_ = this->value_ + rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_iec&
    operator-=(const byte_iec& rhs)
    {
        this->value_ = this->value_ - rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_iec&
    operator*=(const byte_iec& rhs)
    {
        this->value_ = this->value_ * rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_iec&
    operator/=(const byte_iec& rhs)
    {
        this->value_ = this->value_ / rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_iec&
    operator%=(const byte_iec& rhs)
    {
        this->value_ = this->value_ % rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr bool
    operator==(const byte_iec& rhs) const noexcept
    {
        return this->value_ == rhs.value_;
    }

    constexpr std::strong_ordering
    operator<=>(const byte_iec& rhs) const noexcept
    {
        return this->value_ <=> rhs.value_;
    }

    [[nodiscard]] constexpr byte_iec
    min(const byte_iec& rhs) const noexcept
    {
        return std::min(this->value_, rhs.value_);
    }

    [[nodiscard]] constexpr byte_iec
    max(const byte_iec& rhs) const noexcept
    {
        return std::max(this->value_, rhs.value_);
    }

    [[nodiscard]] bool
    is_byte() const noexcept
    {
        return this->unit_type_ == unit::byte;
    }

    [[nodiscard]] bool
    is_kibibyte() const noexcept
    {
        return this->unit_type_ == unit::kibibyte;
    }

    [[nodiscard]] bool
    is_mebibyte() const noexcept
    {
        return this->unit_type_ == unit::mebibyte;
    }

    [[nodiscard]] bool
    is_gibibyte() const noexcept
    {
        return this->unit_type_ == unit::gibibyte;
    }

    [[nodiscard]] bool
    is_tebibyte() const noexcept
    {
        return this->unit_type_ == unit::tebibyte;
    }

    [[nodiscard]] bool
    is_pebibyte() const noexcept
    {
        return this->unit_type_ == unit::pebibyte;
    }

    [[nodiscard]] bool
    is_exbibyte() const noexcept
    {
        return this->unit_type_ == unit::exbibyte;
    }

    [[nodiscard]] bool
    is_zebibyte() const noexcept
    {
        return this->unit_type_ == unit::zebibyte;
    }

    [[nodiscard]] bool
    is_yobibyte() const noexcept
    {
        return this->unit_type_ == unit::yobibyte;
    }

    [[nodiscard]] bool
    is_robibyte() const noexcept
    {
        return this->unit_type_ == unit::robibyte;
    }

    [[nodiscard]] bool
    is_qubibyte() const noexcept
    {
        return this->unit_type_ == unit::qubibyte;
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
    [[nodiscard]] std::string
    format(u32 precision = 1) const noexcept
    {
        // do not show decimals for bytes
        if (this->is_byte())
        {
            precision = 0;
        }

        return std::format("{:.{}f} {}", this->unit_size_, precision, unit_labels.at(this->unit_type_));
    }

    // get the underlying c type value
    [[nodiscard]] constexpr auto
    data() const noexcept
    {
        return this->value_;
    }

  private:
    enum class unit : std::uint8_t
    {
        byte,
        kibibyte,
        mebibyte,
        gibibyte,
        tebibyte,
        pebibyte,
        exbibyte,
        zebibyte,
        yobibyte,
        robibyte,
        qubibyte,
    };

    // clang-format off
    static constexpr ztd::map<unit, std::string_view, 11> unit_labels{
        {unit::byte,     "B"  },
        {unit::kibibyte, "KiB"},
        {unit::mebibyte, "MiB"},
        {unit::gibibyte, "GiB"},
        {unit::tebibyte, "TiB"},
        {unit::pebibyte, "PiB"},
        {unit::exbibyte, "EiB"},
        {unit::zebibyte, "ZiB"},
        {unit::yobibyte, "YiB"},
        {unit::robibyte, "RiB"},
        {unit::qubibyte, "QiB"},
    };
    // clang-format on

    std::uint64_t value_ = 0; // raw size in bytes

    double unit_size_{0.0};
    unit unit_type_ = unit::byte;

    void
    calculate()
    {
        if (this->value_ == 0)
        {
            this->unit_type_ = unit::byte;
            return;
        }

        static constexpr std::uint32_t byte_base = 1024;

        auto size = this->value_;

        std::uint64_t idx = 0;
        std::uint64_t rem = 0;

        while (size >= byte_base)
        {
            rem = size % byte_base;
            size /= byte_base;
            ++idx;
        }

        this->unit_type_ = magic_enum::enum_cast<unit>(idx).value();
        this->unit_size_ = (double)size + ((double)rem / (double)byte_base);
    }
};

class byte_si
{
  public:
    byte_si() = default;

    template<typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    constexpr byte_si(const T& rhs) : value_(rhs)
    {
        this->calculate();
    }

    constexpr byte_si
    operator+(const byte_si& other) const
    {
        return this->value_ + other.value_;
    }

    constexpr byte_si
    operator-(const byte_si& other) const
    {
        return this->value_ - other.value_;
    }

    constexpr byte_si
    operator*(const byte_si& other) const
    {
        return this->value_ * other.value_;
    }

    constexpr byte_si
    operator/(const byte_si& other) const
    {
        return this->value_ / other.value_;
    }

    constexpr byte_si
    operator%(const byte_si& other) const
    {
        return this->value_ % other.value_;
    }

    constexpr byte_si&
    operator+=(const byte_si& rhs)
    {
        this->value_ = this->value_ + rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_si&
    operator-=(const byte_si& rhs)
    {
        this->value_ = this->value_ - rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_si&
    operator*=(const byte_si& rhs)
    {
        this->value_ = this->value_ * rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_si&
    operator/=(const byte_si& rhs)
    {
        this->value_ = this->value_ / rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte_si&
    operator%=(const byte_si& rhs)
    {
        this->value_ = this->value_ % rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr bool
    operator==(const byte_si& rhs) const noexcept
    {
        return this->value_ == rhs.value_;
    }

    constexpr std::strong_ordering
    operator<=>(const byte_si& rhs) const noexcept
    {
        return this->value_ <=> rhs.value_;
    }

    [[nodiscard]] constexpr byte_si
    min(const byte_si& rhs) const noexcept
    {
        return std::min(this->value_, rhs.value_);
    }

    [[nodiscard]] constexpr byte_si
    max(const byte_si& rhs) const noexcept
    {
        return std::max(this->value_, rhs.value_);
    }

    [[nodiscard]] bool
    is_byte() const noexcept
    {
        return this->unit_type_ == unit::byte;
    }

    [[nodiscard]] bool
    is_kilobyte() const noexcept
    {
        return this->unit_type_ == unit::kilobyte;
    }

    [[nodiscard]] bool
    is_megabyte() const noexcept
    {
        return this->unit_type_ == unit::megabyte;
    }

    [[nodiscard]] bool
    is_gigabyte() const noexcept
    {
        return this->unit_type_ == unit::gigabyte;
    }

    [[nodiscard]] bool
    is_terrabyte() const noexcept
    {
        return this->unit_type_ == unit::terrabyte;
    }

    [[nodiscard]] bool
    is_petabyte() const noexcept
    {
        return this->unit_type_ == unit::petabyte;
    }

    [[nodiscard]] bool
    is_exabyte() const noexcept
    {
        return this->unit_type_ == unit::exabyte;
    }

    [[nodiscard]] bool
    is_zettabyte() const noexcept
    {
        return this->unit_type_ == unit::zettabyte;
    }

    [[nodiscard]] bool
    is_yottabyte() const noexcept
    {
        return this->unit_type_ == unit::yottabyte;
    }

    [[nodiscard]] bool
    is_ronnabyte() const noexcept
    {
        return this->unit_type_ == unit::ronnabyte;
    }

    [[nodiscard]] bool
    is_quettabyte() const noexcept
    {
        return this->unit_type_ == unit::quettabyte;
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
    [[nodiscard]] std::string
    format(u32 precision = 1) const noexcept
    {
        // do not show decimals for bytes
        if (this->is_byte())
        {
            precision = 0;
        }

        return std::format("{:.{}f} {}", this->unit_size_, precision, unit_labels.at(this->unit_type_));
    }

    // get the underlying c type value
    [[nodiscard]] constexpr auto
    data() const noexcept
    {
        return this->value_;
    }

  private:
    enum class unit : std::uint8_t
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

    // clang-format off
    static constexpr ztd::map<unit, std::string_view, 11> unit_labels{
        {unit::byte,       "B" },
        {unit::kilobyte,   "KB"},
        {unit::megabyte,   "MB"},
        {unit::gigabyte,   "GB"},
        {unit::terrabyte,  "TB"},
        {unit::petabyte,   "PB"},
        {unit::exabyte,    "EB"},
        {unit::zettabyte,  "ZB"},
        {unit::yottabyte,  "YB"},
        {unit::ronnabyte,  "RB"},
        {unit::quettabyte, "QB"},
    };
    // clang-format on

    std::uint64_t value_ = 0; // raw size in bytes

    double unit_size_{0.0};
    unit unit_type_ = unit::byte;

    void
    calculate()
    {
        if (this->value_ == 0)
        {
            this->unit_type_ = unit::byte;
            return;
        }

        static constexpr std::uint32_t byte_base = 1000;

        auto size = this->value_;

        std::uint64_t idx = 0;
        std::uint64_t rem = 0;

        while (size >= byte_base)
        {
            rem = size % byte_base;
            size /= byte_base;
            ++idx;
        }

        this->unit_type_ = magic_enum::enum_cast<unit>(idx).value();
        this->unit_size_ = (double)size + ((double)rem / (double)byte_base);
    }
};
} // namespace ztd
