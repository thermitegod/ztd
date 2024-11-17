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

#include <array>

#include <format>

#include <algorithm>

#include <type_traits>

#include <magic_enum.hpp>

#include "types.hxx"

namespace ztd
{
namespace detail
{
enum class standard : std::uint8_t
{
    iec,
    si,
};
}

template<detail::standard S> class byte
{
  public:
    byte() { this->static_data(); }

    template<typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>> constexpr byte(const T& rhs) : value_(rhs)
    {
        this->static_data();
        this->calculate();
    }

    constexpr byte
    operator+(const byte& other) const
    {
        return this->value_ + other.value_;
    }

    constexpr byte
    operator-(const byte& other) const
    {
        return this->value_ - other.value_;
    }

    constexpr byte
    operator*(const byte& other) const
    {
        return this->value_ * other.value_;
    }

    constexpr byte
    operator/(const byte& other) const
    {
        return this->value_ / other.value_;
    }

    constexpr byte
    operator%(const byte& other) const
    {
        return this->value_ % other.value_;
    }

    constexpr byte&
    operator+=(const byte& rhs)
    {
        this->value_ = this->value_ + rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte&
    operator-=(const byte& rhs)
    {
        this->value_ = this->value_ - rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte&
    operator*=(const byte& rhs)
    {
        this->value_ = this->value_ * rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte&
    operator/=(const byte& rhs)
    {
        this->value_ = this->value_ / rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr byte&
    operator%=(const byte& rhs)
    {
        this->value_ = this->value_ % rhs.value_;
        this->calculate();
        return *this;
    }

    constexpr bool
    operator==(const byte& rhs) const noexcept
    {
        return this->value_ == rhs.value_;
    }

    constexpr std::strong_ordering
    operator<=>(const byte& rhs) const noexcept
    {
        return this->value_ <=> rhs.value_;
    }

    [[nodiscard]] constexpr byte
    min(const byte& rhs) const noexcept
    {
        return std::min(this->value_, rhs.value_);
    }

    [[nodiscard]] constexpr byte
    max(const byte& rhs) const noexcept
    {
        return std::max(this->value_, rhs.value_);
    }

    [[nodiscard]] bool
    is_byte() const noexcept
    {
        return this->unit_type_ == unit::b;
    }

    // IEC names //

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_kibibyte() const noexcept
    {
        return this->unit_type_ == unit::k;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_mebibyte() const noexcept
    {
        return this->unit_type_ == unit::m;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_gibibyte() const noexcept
    {
        return this->unit_type_ == unit::g;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_tebibyte() const noexcept
    {
        return this->unit_type_ == unit::t;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_pebibyte() const noexcept
    {
        return this->unit_type_ == unit::p;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_exbibyte() const noexcept
    {
        return this->unit_type_ == unit::e;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_zebibyte() const noexcept
    {
        return this->unit_type_ == unit::z;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_yobibyte() const noexcept
    {
        return this->unit_type_ == unit::y;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_robibyte() const noexcept
    {
        return this->unit_type_ == unit::r;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::iec, T>
    is_qubibyte() const noexcept
    {
        return this->unit_type_ == unit::q;
    }

    // SI names //

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_kilobyte() const noexcept
    {
        return this->unit_type_ == unit::k;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_megabyte() const noexcept
    {
        return this->unit_type_ == unit::m;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_gigabyte() const noexcept
    {
        return this->unit_type_ == unit::g;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_terrabyte() const noexcept
    {
        return this->unit_type_ == unit::t;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_petabyte() const noexcept
    {
        return this->unit_type_ == unit::p;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_exabyte() const noexcept
    {
        return this->unit_type_ == unit::e;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_zettabyte() const noexcept
    {
        return this->unit_type_ == unit::z;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_yottabyte() const noexcept
    {
        return this->unit_type_ == unit::y;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_ronnabyte() const noexcept
    {
        return this->unit_type_ == unit::r;
    }

    template<typename T = bool>
    [[nodiscard]] typename std::enable_if_t<S == detail::standard::si, T>
    is_quettabyte() const noexcept
    {
        return this->unit_type_ == unit::q;
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

        return std::format("{:.{}f} {}",
                           this->unit_size_,
                           precision,
                           unit_labels.at(magic_enum::enum_integer(this->unit_type_)));
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
        b, // byte
        k, // IEC kibibyte / SI kilobyte
        m, // IEC mebibyte / SI megabyte
        g, // IEC gibibyte / SI gigabyte
        t, // IEC tebibyte / SI terrabyte
        p, // IEC pebibyte / SI petabyte
        e, // IEC exbibyte / SI exabyte
        z, // IEC zebibyte / SI zettabyte
        y, // IEC yobibyte / SI yottabyte
        r, // IEC robibyte / SI ronnabyte
        q, // IEC qubibyte / SI quettabyte
    };

    std::uint64_t value_ = 0; // raw size in bytes

    std::uint32_t byte_base = 0;
    std::array<std::string_view, 11> unit_labels;
    float unit_size_{0.0};
    unit unit_type_ = unit::b;

    constexpr void
    static_data() noexcept
    {
        if constexpr (S == detail::standard::iec)
        {
            this->byte_base = 1024;
            this->unit_labels = {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB", "RiB", "QiB"};
        }
        else if constexpr (S == detail::standard::si)
        {
            this->byte_base = 1000;
            this->unit_labels = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB", "RB", "QB"};
        }
    }

    void
    calculate()
    {
        if (this->value_ == 0)
        {
            this->unit_type_ = unit::b;
            return;
        }

        auto size = this->value_;

        std::uint64_t idx = 0;
        std::uint64_t rem = 0;

        while (size >= this->byte_base)
        {
            rem = size % this->byte_base;
            size /= this->byte_base;
            ++idx;
        }

        this->unit_type_ = magic_enum::enum_cast<unit>(idx).value();
        this->unit_size_ = (float)size + ((float)rem / (float)this->byte_base);
    }
};

using byte_iec = byte<detail::standard::iec>;
using byte_si = byte<detail::standard::si>;

} // namespace ztd
