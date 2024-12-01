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

#if __has_include(<magic_enum/magic_enum.hpp>)
// >=magic_enum-0.9.7
#include <magic_enum/magic_enum.hpp>
#else
// <=magic_enum-0.9.6
#include <magic_enum.hpp>
#endif

#include "types.hxx"

namespace ztd
{
enum class base : std::uint8_t
{
    iec,
    si,
};

template<base S> class byte
{
  public:
    byte() = default;

    template<typename T>
    constexpr byte(const T& rhs)
        requires(std::is_unsigned_v<T>)
        : value_(rhs)
    {
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

    template<typename T>
    constexpr byte
    operator*(const T& other) const
        requires(std::is_unsigned_v<T>)
    {
        return this->value_ * other;
    }

    template<typename T>
    constexpr byte
    operator/(const T& other) const
        requires(std::is_unsigned_v<T>)
    {
        return this->value_ / other;
    }

    template<typename T>
    constexpr byte
    operator%(const T& other) const
        requires(std::is_unsigned_v<T>)
    {
        return this->value_ % other;
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

    template<typename T>
    constexpr byte&
    operator*=(const T& rhs)
        requires(std::is_unsigned_v<T>)
    {
        this->value_ = this->value_ * rhs;
        this->calculate();
        return *this;
    }

    template<typename T>
    constexpr byte&
    operator/=(const T& rhs)
        requires(std::is_unsigned_v<T>)
    {
        this->value_ = this->value_ / rhs;
        this->calculate();
        return *this;
    }

    template<typename T>
    constexpr byte&
    operator%=(const T& rhs)
        requires(std::is_unsigned_v<T>)
    {
        this->value_ = this->value_ % rhs;
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

    [[nodiscard]] bool
    is_kibibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::k;
    }

    [[nodiscard]] bool
    is_mebibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::m;
    }

    [[nodiscard]] bool
    is_gibibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::g;
    }

    [[nodiscard]] bool
    is_tebibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::t;
    }

    [[nodiscard]] bool
    is_pebibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::p;
    }

    [[nodiscard]] bool
    is_exbibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::e;
    }

    [[nodiscard]] bool
    is_zebibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::z;
    }

    [[nodiscard]] bool
    is_yobibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::y;
    }

    [[nodiscard]] bool
    is_robibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::r;
    }

    [[nodiscard]] bool
    is_qubibyte() const noexcept
        requires(S == base::iec)
    {
        return this->unit_type_ == unit::q;
    }

    // SI names //

    [[nodiscard]] bool
    is_kilobyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::k;
    }

    [[nodiscard]] bool
    is_megabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::m;
    }

    [[nodiscard]] bool
    is_gigabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::g;
    }

    [[nodiscard]] bool
    is_terrabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::t;
    }

    [[nodiscard]] bool
    is_petabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::p;
    }

    [[nodiscard]] bool
    is_exabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::e;
    }

    [[nodiscard]] bool
    is_zettabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::z;
    }

    [[nodiscard]] bool
    is_yottabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::y;
    }

    [[nodiscard]] bool
    is_ronnabyte() const noexcept
        requires(S == base::si)
    {
        return this->unit_type_ == unit::r;
    }

    [[nodiscard]] bool
    is_quettabyte() const noexcept
        requires(S == base::si)
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

        constexpr auto labels = []() -> std::array<std::string_view, 11>
        {
            if constexpr (S == base::iec)
            {
                return {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB", "RiB", "QiB"};
            }
            else if constexpr (S == base::si)
            {
                return {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB", "RB", "QB"};
            }
        }();

        return std::format("{:.{}f} {}",
                           this->unit_size_,
                           precision,
                           labels.at(magic_enum::enum_integer(this->unit_type_)));
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

    float unit_size_{0.0};
    unit unit_type_ = unit::b;

    void
    calculate() noexcept
    {
        constexpr auto base = []() -> std::uint32_t
        {
            if constexpr (S == base::iec)
            {
                return 1024;
            }
            else if constexpr (S == base::si)
            {
                return 1000;
            }
        }();

        auto size = this->value_;

        std::uint8_t idx = 0;
        std::uint64_t rem = 0;

        while (size >= base)
        {
            rem = size % base;
            size /= base;
            ++idx;
        }

        this->unit_type_ = magic_enum::enum_cast<unit>(idx).value();
        this->unit_size_ = (float)size + ((float)rem / (float)base);
    }
};

using byte_iec = byte<base::iec>;
using byte_si = byte<base::si>;

/**
 * Convenience Wrapper
 */
[[nodiscard]] inline std::string
format_filesize(const u64 size_in_bytes, const base b = base::iec, const u32 precision = 1) noexcept
{
    if (b == base::iec)
    {
        const byte_iec size = size_in_bytes;
        return size.format(precision);
    }
    else
    {
        const byte_si size = size_in_bytes;
        return size.format(precision);
    }
}

namespace byte_iec_literals
{
// clang-format off
constexpr byte_iec operator"" _B(unsigned long long v)   { return v; }
constexpr byte_iec operator"" _KiB(unsigned long long v) { return v * 1024; }
constexpr byte_iec operator"" _MiB(unsigned long long v) { return v * 1024 * 1024; }
constexpr byte_iec operator"" _GiB(unsigned long long v) { return v * 1024 * 1024 * 1024; }
constexpr byte_iec operator"" _TiB(unsigned long long v) { return v * 1024 * 1024 * 1024 * 1024; }
constexpr byte_iec operator"" _PiB(unsigned long long v) { return v * 1024 * 1024 * 1024 * 1024 * 1024; }
constexpr byte_iec operator"" _EiB(unsigned long long v) { return v * 1024 * 1024 * 1024 * 1024 * 1024 * 1024; }
// constexpr byte_iec operator"" _ZiB(unsigned long long v) { return v * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024; }
// constexpr byte_iec operator"" _YiB(unsigned long long v) { return v * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024; }
// constexpr byte_iec operator"" _RiB(unsigned long long v) { return v * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024; }
// constexpr byte_iec operator"" _QiB(unsigned long long v) { return v * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024; }
// clang-format on
} // namespace byte_iec_literals

namespace byte_si_literals
{
// clang-format off
constexpr byte_si operator"" _B(unsigned long long v)  { return v; }
constexpr byte_si operator"" _kB(unsigned long long v) { return v * 1000; }
constexpr byte_si operator"" _MB(unsigned long long v) { return v * 1000 * 1000; }
constexpr byte_si operator"" _GB(unsigned long long v) { return v * 1000 * 1000 * 1000; }
constexpr byte_si operator"" _TB(unsigned long long v) { return v * 1000 * 1000 * 1000 * 1000; }
constexpr byte_si operator"" _PB(unsigned long long v) { return v * 1000 * 1000 * 1000 * 1000 * 1000; }
constexpr byte_si operator"" _EB(unsigned long long v) { return v * 1000 * 1000 * 1000 * 1000 * 1000 * 1000; }
// constexpr byte_si operator"" _ZB(unsigned long long v) { return v * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000; }
// constexpr byte_si operator"" _YB(unsigned long long v) { return v * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000; }
// constexpr byte_si operator"" _RB(unsigned long long v) { return v * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000; }
// constexpr byte_si operator"" _QB(unsigned long long v) { return v * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000; }
// clang-format on
} // namespace byte_si_literals

} // namespace ztd
