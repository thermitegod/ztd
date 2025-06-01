/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <algorithm>
#include <format>
#include <limits>
#include <numeric>
#include <optional>
#include <ranges>
#include <tuple>
#include <type_traits>
#include <utility>

#include "../panic.hxx"
#include "../random.hxx"
#include "../utils.hxx"
#include "integer_traits.hxx"

#if defined(MIN)
#undef MIN
#endif

#if defined(MAX)
#undef MAX
#endif

namespace ztd
{
// clang-format off
template<typename T> constexpr bool is_integer_v          = std::is_integral_v<T> && !std::is_same_v<T, bool> && !std::is_same_v<T, char>;
template<typename T> constexpr bool is_signed_integer_v   = is_integer_v<T> && std::is_signed_v<T>;
template<typename T> constexpr bool is_unsigned_integer_v = is_integer_v<T> && std::is_unsigned_v<T>;

template<typename T, typename U> constexpr bool is_integer_conversion_safe_v =
    (sizeof(T) <= sizeof(U) && is_signed_integer_v<T> == is_signed_integer_v<U>) ||
    (sizeof(T) < sizeof(U) && is_unsigned_integer_v<T> && is_signed_integer_v<U>);
// clang-format on

template<typename Tag> class integer final
{
  public:
    using tag = Tag;
    using integer_type = typename detail::integer_traits<Tag>::integer_type;
    using sign_conversion_tag = typename detail::integer_traits<Tag>::sign_conversion_tag;
    static_assert(is_integer_v<integer_type>);

    template<typename T> friend class integer;

    constexpr integer() noexcept : value_(0) {}

    template<typename T>
    constexpr integer(const T rhs) noexcept
        requires(std::is_same_v<T, bool>)
    = delete("help: cannot construct an integer from a bool");

    template<typename T>
    // constexpr explicit integer(const T rhs)
    constexpr integer(const T rhs) noexcept
        requires(is_integer_v<T>)
        : value_(rhs)
    {
    }

    /**
     * @brief create
     * @return an integer, side effects determined by default math mode.
     */
    template<typename T>
    [[nodiscard]] static constexpr integer<Tag>
    create(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return integer<Tag>::strict_create(rhs);
        }
        else
        {
            return integer<Tag>::unchecked_create(rhs);
        }
    }

    /**
     * @brief create
     *
     *  - Extract a numeric value from a string, the string must only
     *    be a numeric and can not be a mix of letters, numbers, or control
     *    characters.
     *
     * @param[in] str The string to extract a numeric value from
     *
     * @return The numeric value from str, or std::nullopt.
     */
    [[nodiscard]] static constexpr std::optional<integer<Tag>>
    create(const std::string_view str) noexcept
    {
        auto e = ztd::from_string<integer_type>(str);
        if (!e)
        {
            return std::nullopt;
        }
        return integer<Tag>(e.value());
    }

    /**
     * @brief checked_create
     *
     *  - Create an integer with bounds checking. If the integral
     *    value will not fit in this type return std::nullopt.
     *
     * @param[in] v Integral to create from
     *
     * @return The integer, std::nullopt
     */
    template<typename T>
    [[nodiscard]] static constexpr std::optional<integer<Tag>>
    checked_create(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        if constexpr (!is_integer_conversion_safe_v<T, integer_type>)
        {
            if constexpr (std::is_signed_v<integer_type>)
            {
                if (std::cmp_less(rhs, std::numeric_limits<integer_type>::min()))
                {
                    return std::nullopt;
                }
            }
            else if constexpr (std::is_unsigned_v<integer_type>)
            {
                if (std::cmp_less(rhs, 0))
                {
                    return std::nullopt;
                }
            }
            if (std::cmp_greater(rhs, std::numeric_limits<integer_type>::max()))
            {
                return std::nullopt;
            }
        }
        return integer<Tag>(static_cast<integer_type>(rhs));
    }

    /**
     * @brief strict_create
     *
     *  - Create an integer with bounds checking. If the integral
     *    value will not fit in this type then panic.
     *
     * @param[in] v Integral to create from
     *
     * @return The integer
     */
    template<typename T>
    [[nodiscard]] static constexpr integer<Tag>
    strict_create(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::checked_create(rhs);
        if (!x)
        {
            ztd::panic("create failed for: {}", rhs);
        }
        return x.value();
    }

    /**
     * @brief unchecked_create - Create an integer without bounds checking it first.
     * @param[in] v Integral to create from
     * @return The integer
     */
    template<typename T>
    [[nodiscard]] static constexpr integer<Tag>
    unchecked_create(const T v) noexcept
        requires(is_integer_v<T>)
    {
        return integer<Tag>(static_cast<integer_type>(v));
    }

    /**
     * @brief saturating_create
     *
     *  - Create an integer, saturating the value if it will
     *    not fit in this type.
     *
     * @param[in] v Integral to create from
     *
     * @return The integer
     */
    template<typename T>
    [[nodiscard]] static constexpr integer<Tag>
    saturating_create(const T v) noexcept
        requires(is_integer_v<T>)
    {
        return integer<Tag>(std::saturate_cast<integer_type>(v));
    }

    /**
     * @brief random - get a random value between (min, max)
     * @param[in] min min random value
     * @param[in] max max random value
     * @return a random value
     */
    [[nodiscard]] static constexpr integer<Tag>
    random(const integer<Tag> min = integer<Tag>::MIN(),
           const integer<Tag> max = integer<Tag>::MAX()) noexcept
    {
        return integer<Tag>(ztd::random(min.value_, max.value_));
    }

    // conversions operators

    explicit operator bool() = delete("help: use either '!= 0' or '== 0'");

    constexpr operator uint8_t() = delete("help: implicit conversion is not supported");
    constexpr operator uint16_t() = delete("help: implicit conversion is not supported");
    constexpr operator uint32_t() = delete("help: implicit conversion is not supported");
    constexpr operator uint64_t() = delete("help: implicit conversion is not supported");

    constexpr operator int8_t() = delete("help: implicit conversion is not supported");
    constexpr operator int16_t() = delete("help: implicit conversion is not supported");
    constexpr operator int32_t() = delete("help: implicit conversion is not supported");
    constexpr operator int64_t() = delete("help: implicit conversion is not supported");

    constexpr operator float() = delete("help: implicit conversion is not supported");
    constexpr operator double() = delete("help: implicit conversion is not supported");

    // assignment operators

    constexpr integer<Tag>&
    operator=(const bool rhs) = delete("help: cannot assign a bool to an integer");

    template<typename T>
    constexpr integer<Tag>&
    operator=(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        this->value_ = rhs;
        return *this;
    }

    // unary operators

    constexpr integer<Tag>
    operator+() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        return *this;
    }

    constexpr integer<Tag>
    operator-() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        return this->neg();
    }

    // increment/decrement operators

    constexpr integer<Tag>& operator++() = delete("help: use '+= 1' instead");
    constexpr integer<Tag> operator++(int) = delete("help: use '+= 1' instead");
    constexpr integer<Tag>& operator--() = delete("help: use '-= 1' instead");
    constexpr integer<Tag> operator--(int) = delete("help: use '-= 1' instead");

    // arithmetic operators

    [[nodiscard]] constexpr integer<Tag>
    operator+(const integer<Tag> rhs) const noexcept
    {
        return this->add(rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr integer<Tag>
    operator+(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        return this->add(x);
    }

    [[nodiscard]] constexpr integer<Tag>
    operator-(const integer<Tag> rhs) const noexcept
    {
        return this->sub(rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr integer<Tag>
    operator-(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        return this->sub(x);
    }

    [[nodiscard]] constexpr integer<Tag>
    operator*(const integer<Tag> rhs) const noexcept
    {
        return this->mul(rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr integer<Tag>
    operator*(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        return this->mul(x);
    }

    [[nodiscard]] constexpr integer<Tag>
    operator/(const integer<Tag> rhs) const noexcept
    {
        return this->div(rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr integer<Tag>
    operator/(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        return this->div(x);
    }

    [[nodiscard]] constexpr integer<Tag>
    operator%(const integer<Tag> rhs) const noexcept
    {
        return this->rem(rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr integer<Tag>
    operator%(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        return this->rem(x);
    }

    // assignment operators

    constexpr integer<Tag>&
    operator+=(const integer<Tag> rhs) noexcept
    {
        *this = this->add(rhs);
        return *this;
    }

    template<typename T>
    constexpr integer<Tag>
    operator+=(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        *this = this->add(x);
        return *this;
    }

    constexpr integer<Tag>&
    operator-=(const integer<Tag> rhs) noexcept
    {
        *this = this->sub(rhs);
        return *this;
    }

    template<typename T>
    constexpr integer<Tag>
    operator-=(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        *this = this->sub(x);
        return *this;
    }

    constexpr integer<Tag>&
    operator*=(const integer<Tag> rhs) noexcept
    {
        *this = this->mul(rhs);
        return *this;
    }

    template<typename T>
    constexpr integer<Tag>
    operator*=(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        *this = this->mul(x);
        return *this;
    }

    constexpr integer<Tag>&
    operator/=(const integer<Tag> rhs) noexcept
    {
        *this = this->div(rhs);
        return *this;
    }

    template<typename T>
    constexpr integer<Tag>
    operator/=(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        *this = this->div(x);
        return *this;
    }

    constexpr integer<Tag>&
    operator%=(const integer<Tag> rhs) noexcept
    {
        *this = this->rem(rhs);
        return *this;
    }

    template<typename T>
    constexpr integer<Tag>
    operator%=(const T rhs) noexcept
        requires(is_integer_v<T>)
    {
        auto x = integer<Tag>::create(rhs);
        *this = this->rem(x);
        return *this;
    }

    // comparison operators

    template<typename T>
    [[nodiscard]] constexpr bool
    operator==(const integer<T> rhs) const noexcept
    {
        return std::cmp_equal(this->value_, rhs.value_);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator==(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        return std::cmp_equal(this->value_, rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator!=(const integer<T> rhs) const noexcept
    {
        return std::cmp_not_equal(this->value_, rhs.value_);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator!=(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        return std::cmp_not_equal(this->value_, rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator<(const integer<T> rhs) const noexcept
    {
        return std::cmp_less(this->value_, rhs.value_);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator<(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        return std::cmp_less(this->value_, rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator<=(const integer<T> rhs) const noexcept
    {
        return std::cmp_less_equal(this->value_, rhs.value_);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator<=(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        return std::cmp_less_equal(this->value_, rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator>(const integer<T> rhs) const noexcept
    {
        return std::cmp_greater(this->value_, rhs.value_);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator>(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        return std::cmp_greater(this->value_, rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator>=(const integer<T> rhs) const noexcept
    {
        return std::cmp_greater_equal(this->value_, rhs.value_);
    }

    template<typename T>
    [[nodiscard]] constexpr bool
    operator>=(const T rhs) const noexcept
        requires(is_integer_v<T>)
    {
        return std::cmp_greater_equal(this->value_, rhs);
    }

    // functions

    /**
     * @brief abs - absolute value
     * @return self.abs(), side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    abs() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_abs();
        }
        else
        {
            return this->wrapping_abs();
        }
    }

    /**
     * @brief add - integer addition
     * @return self + rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    add(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_add(rhs);
        }
        else
        {
            return this->wrapping_add(rhs);
        }
    }

    /**
     * @brief add - integer addition
     * @return self + rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    add(const integer<sign_conversion_tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_add(rhs);
        }
        else
        {
            return this->wrapping_add(rhs);
        }
    }

    /**
     * @brief sub - integer subtraction
     * @return self - rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    sub(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_sub(rhs);
        }
        else
        {
            return this->wrapping_sub(rhs);
        }
    }

    /**
     * @brief sub - integer subtraction
     * @return self - rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    sub(const integer<sign_conversion_tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_sub(rhs);
        }
        else
        {
            return this->wrapping_sub(rhs);
        }
    }

    /**
     * @brief mul - integer multiplication
     * @return self * rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    mul(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_mul(rhs);
        }
        else
        {
            return this->wrapping_mul(rhs);
        }
    }

    /**
     * @brief div - integer division
     * @return self / rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    div(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_div(rhs);
        }
        else
        {
            return this->wrapping_div(rhs);
        }
    }

    /**
     * @brief div_euclid - euclidean division
     * @return self / rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_euclid(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_div_euclid(rhs);
        }
        else
        {
            return this->wrapping_div_euclid(rhs);
        }
    }

    /**
     * @brief div_ceil
     * @return self / rhs, rounding the result towards positive infinity.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_ceil(const integer<Tag> rhs) const noexcept
    {
        // auto [q, r] = this->divmod(rhs);
        auto q = this->strict_div(rhs);
        auto r = this->strict_rem(rhs);
        if ((r != 0) && ((r > 0) == (rhs > 0)))
        {
            q += integer_type(1);
        }
        return q;
    }

    /**
     * @brief div_floor
     * @return self / rhs, rounding the result towards negative infinity.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_floor(const integer<Tag> rhs) const noexcept
    {
        // auto [q, r] = this->divmod(rhs);
        auto q = this->strict_div(rhs);
        auto r = this->strict_rem(rhs);
        if ((r != 0) && (*this < 0) != (rhs < 0))
        {
            q -= integer_type(1);
        }
        return q;
    }

    /**
     * @brief rem - integer remainder
     * @return self % rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    rem(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_rem(rhs);
        }
        else
        {
            return this->wrapping_rem(rhs);
        }
    }

    /**
     * @brief rem_euclid - euclidean remainder
     * @return self % rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    rem_euclid(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_rem_euclid(rhs);
        }
        else
        {
            return this->wrapping_rem_euclid(rhs);
        }
    }

    /**
     * @brief neg - integer negation
     * @return -self, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    neg() const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_neg();
        }
        else
        {
            return this->wrapping_neg();
        }
    }

    /**
     * @brief pow - integer exponentiation.
     * @return self.pow(exp), side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    pow(const integer<detail::u32_tag> exp) const noexcept
    {
        if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
        {
            return this->strict_pow(exp);
        }
        else
        {
            return this->wrapping_pow(exp);
        }
    }

    /**
     * @brief checked_abs - Checked absolute value
     * @return self.abs(), or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_abs() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        auto [result, overflow] = this->overflowing_abs();
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_add - Checked integer addition
     * @return self + rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_add(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_add(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_add - Checked integer addition
     * @return self + rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_add(const integer<sign_conversion_tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_add(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_sub - Checked integer subtraction
     * @return self - rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_sub(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_sub(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_sub - Checked integer subtraction
     * @return self - rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_sub(const integer<sign_conversion_tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_sub(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_mul - Checked integer multiplication
     * @return self * rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_mul(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_mul(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_div - Checked integer division
     * @return self / rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_div(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_div
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_div(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_div_euclid - Checked euclidean division
     * @return self / rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_div_euclid(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_div_euclid
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_div_euclid(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_rem - Checked integer remainder
     * @return self % rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_rem(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_rem
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_rem(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_rem_euclid - Checked euclidean remainder
     * @return self % rhs, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_rem_euclid(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_rem_euclid
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_rem_euclid(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_neg - Checked integer negation
     * @return -self, or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_neg() const noexcept
    {
        auto [result, overflow] = this->overflowing_neg();
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_pow - Checked integer exponentiation.
     * @return self.pow(exp), or std::nullopt if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_pow(const integer<detail::u32_tag> exp) const noexcept
    {
        auto [result, overflow] = this->overflowing_pow(exp);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief saturating_abs - Checked absolute value
     * @return self.abs(), instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_abs() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        auto x = this->checked_abs();
        if (!x)
        {
            return integer<Tag>::MAX();
        }
        return x.value();
    }

    /**
     * @brief saturating_add - Checked integer addition
     * @return self + rhs, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_add(const integer<Tag> rhs) const noexcept
    {
        return integer<Tag>(std::add_sat(this->value_, rhs.value_));
    }

    /**
     * @brief saturating_add - Checked integer addition
     * @return self + rhs, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag> saturating_add(const integer<sign_conversion_tag> rhs)
        const noexcept = delete("TODO std::add_sat requires both args are the same type");

    /**
     * @brief saturating_sub - Checked integer subtraction
     * @return self - rhs, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_sub(const integer<Tag> rhs) const noexcept
    {
        return integer<Tag>(std::sub_sat(this->value_, rhs.value_));
    }

    /**
     * @brief saturating_sub - Checked integer subtraction
     * @return self - rhs, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag> saturating_sub(const integer<sign_conversion_tag> rhs)
        const noexcept = delete("TODO std::sub_sat requires both args are the same type");

    /**
     * @brief saturating_mul - Checked integer multiplication
     * @return self * rhs, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_mul(const integer<Tag> rhs) const noexcept
    {
        return integer<Tag>(std::mul_sat(this->value_, rhs.value_));
    }

    /**
     * @brief saturating_div - Checked integer division
     * @return self / rhs, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_div(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            ztd::panic("division by zero: {} / {}", this->value_, rhs.value_);
        }
        return integer<Tag>(std::div_sat(this->value_, rhs.value_));
    }

    /**
     * @brief saturating_neg - Saturating integer negation
     * @return -self, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_neg() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        return this->saturating_mul(integer<Tag>(integer_type(-1)));
    }

    /**
     * @brief saturating_pow - Strict integer exponentiation.
     * @return self.pow(exp), instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_pow(const integer<detail::u32_tag> exp) const noexcept
    {
        if (*this == 0)
        {
            return integer<Tag>(integer_type(0));
        }

        auto result = integer<Tag>::unchecked_create(1);
        for (const auto _ : std::views::iota(0ul, exp.value_))
        {
            result = this->saturating_mul(result);
        }
        return result;
    }

    /**
     * @brief strict_abs - Strict absolute value
     * @return self.abs(), will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_abs() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        auto x = this->checked_abs();
        if (!x)
        {
            ztd::panic("absolute value overflow: {}", this->value_);
        }
        return x.value();
    }

    /**
     * @brief strict_add - Strict integer addition
     * @return self + rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_add(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_add(rhs);
        if (overflow)
        {
            ztd::panic("addition overflow: {} + {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_add - Strict integer addition
     * @return self + rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_add(const integer<sign_conversion_tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_add(rhs);
        if (overflow)
        {
            ztd::panic("addition overflow: {} + {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_sub - Strict integer subtraction
     * @return self - rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_sub(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_sub(rhs);
        if (overflow)
        {
            ztd::panic("subtraction overflow: {} - {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_sub - Strict integer subtraction
     * @return self - rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_sub(const integer<sign_conversion_tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_sub(rhs);
        if (overflow)
        {
            ztd::panic("subtraction overflow: {} - {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_mul - Strict integer multiplication
     * @return self * rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_mul(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_mul(rhs);
        if (overflow)
        {
            ztd::panic("multiplication overflow: {} - {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_div - Strict integer division
     * @return self / rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_div(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div(rhs);
        if (overflow)
        {
            ztd::panic("division overflow: {} / {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_div_euclid - Strict euclidean division
     * @return self / rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_div_euclid(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_euclid(rhs);
        if (overflow)
        {
            ztd::panic("division overflow: {} / {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_rem - Strict integer remainder
     * @return self % rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_rem(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_rem(rhs);
        if (overflow)
        {
            ztd::panic("modulo overflow: {} / {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_rem_euclid - Strict euclidean remainder
     * @return self % rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_rem_euclid(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_rem_euclid(rhs);
        if (overflow)
        {
            ztd::panic("modulo overflow: {} / {}", this->value_, rhs.value_);
        }
        return result;
    }

    /**
     * @brief strict_neg - Strict integer negation
     * @return -self, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_neg() const noexcept
    {
        auto [result, overflow] = this->overflowing_neg();
        if (overflow)
        {
            ztd::panic("negation overflow: -({})", this->value_);
        }
        return result;
    }

    /**
     * @brief strict_pow - Strict integer exponentiation.
     * @return self.pow(exp), will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_pow(const integer<detail::u32_tag> exp) const noexcept
    {
        auto [result, overflow] = this->overflowing_pow(exp);
        if (overflow)
        {
            ztd::panic("exponent multiplication overflow: {}^{}", this->value_, exp.value_);
        }
        return result;
    }

    /**
     * @brief overflowing_abs - Wrapping (modular) absolute value
     * @return self.abs(), If an overflow would occur the minimum value will be returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_abs() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        if (*this == integer<Tag>::MIN())
        {
            return {integer<Tag>::MIN(), true};
        }
        return {*this >= integer<Tag>(integer_type(0)) ? *this : -*this, false};
    }

    /**
     * @brief overflowing_add - Wrapping (modular) addition
     * @return self + rhs, If an overflow would occurred the wrapped value is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_add(const integer<Tag> rhs) const noexcept
    {
        integer_type result;
        const bool overflow = __builtin_add_overflow(this->value_, rhs.value_, &result);
        return {integer<Tag>(result), overflow};
    }

    /**
     * @brief overflowing_add - Wrapping (modular) addition
     * @return self + rhs, If an overflow would occurred the wrapped value is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_add(const integer<sign_conversion_tag> rhs) const noexcept
    {
        integer_type result;
        const bool overflow = __builtin_add_overflow(this->value_, rhs.value_, &result);
        return {integer<Tag>(result), overflow};
    }

    /**
     * @brief overflowing_sub - Wrapping (modular) subtraction
     * @return self - rhs, If an overflow would occurred the wrapped value is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_sub(const integer<Tag> rhs) const noexcept
    {
        integer_type result;
        const bool overflow = __builtin_sub_overflow(this->value_, rhs.value_, &result);
        return {integer<Tag>(result), overflow};
    }

    /**
     * @brief overflowing_sub - Wrapping (modular) subtraction
     * @return self - rhs, If an overflow would occurred the wrapped value is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_sub(const integer<sign_conversion_tag> rhs) const noexcept
    {
        integer_type result;
        const bool overflow = __builtin_sub_overflow(this->value_, rhs.value_, &result);
        return {integer<Tag>(result), overflow};
    }

    /**
     * @brief overflowing_mul - Wrapping (modular) multiplication
     * @return self * rhs, If an overflow would occurred the wrapped value is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_mul(const integer<Tag> rhs) const noexcept
    {
        integer_type result;
        const bool overflow = __builtin_mul_overflow(this->value_, rhs.value_, &result);
        return {integer<Tag>(result), overflow};
    }

    /**
     * @brief overflowing_div - Wrapping (modular) division
     * @return self / rhs, If an overflow would occur then MIN is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_div(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            ztd::panic("division by zero: {} / {}", this->value_, rhs.value_);
        }
        if constexpr (std::is_signed_v<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }
        }
        return {integer<Tag>(integer_type(this->value_ / rhs.value_)), false};
    }

    /**
     * @brief overflowing_div_euclid - Wrapping euclidean division
     * @return self / rhs, If an overflow would occur then MIN is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_div_euclid(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            ztd::panic("division by zero: {} / {}", this->value_, rhs.value_);
        }
        if constexpr (std::is_signed_v<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }

            // euclidean division.
            auto q = this->value_ / rhs.value_;
            if (std::cmp_greater_equal(this->value_ % rhs.value_, 0))
            {
                return {integer<Tag>(integer_type(q)), false};
            }
            else if (rhs > 0)
            {
                return {integer<Tag>(integer_type(q - 1)), false};
            }
            else
            {
                return {integer<Tag>(integer_type(q + 1)), false};
            }
        }
        else
        {
            return {integer<Tag>(integer_type(this->value_ / rhs.value_)), false};
        }
    }

    /**
     * @brief overflowing_rem - Wrapping (modular) remainder
     * @return self % rhs, If an overflow would occur then 0 is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_rem(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            ztd::panic("modulo by zero: {} % {}", this->value_, rhs.value_);
        }
        if constexpr (std::is_signed_v<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>(integer_type(0)), true};
            }
        }
        return {integer<Tag>(integer_type(this->value_ % rhs.value_)), false};
    }

    /**
     * @brief overflowing_rem_euclid - Wrapping euclidean remainder
     * @return self % rhs, If an overflow would occur then 0 is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_rem_euclid(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            ztd::panic("modulo by zero: {} % {}", this->value_, rhs.value_);
        }
        if constexpr (std::is_signed_v<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>(integer_type(0)), true};
            }

            // euclidean remainder.
            auto r = this->value_ % rhs.value_;
            if (std::cmp_less(r, 0))
            {
                if (rhs < 0)
                {
                    return {integer<Tag>(integer_type(r - rhs.value_)), false};
                }
                else
                {
                    return {integer<Tag>(integer_type(r + rhs.value_)), false};
                }
            }
            else
            {
                return {integer<Tag>(integer_type(r)), false};
            }
        }
        else
        {
            return {integer<Tag>(integer_type(this->value_ % rhs.value_)), false};
        }
    }

    /**
     * @brief overflowing_neg - Wrapping (modular) negation
     * @return -self, If an overflow would occur the minimum value will be returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_neg() const noexcept
    {
        if constexpr (std::is_signed_v<integer_type>)
        {
            if (*this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }
            return this->overflowing_mul(integer<Tag>(integer_type(-1)));
        }
        else
        {
            if (*this != 0)
            {
                integer_type result;
                const bool overflow = __builtin_mul_overflow(this->value_, -1, &result);
                return {integer<Tag>(result), overflow};
            }
            return {integer<Tag>(integer_type(0)), false};
        }
    }

    /**
     * @brief overflowing_pow - Wrapping (modular) exponentiation.
     * @return self.pow(exp), If an overflow would occurred the wrapped value is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_pow(const integer<detail::u32_tag> exp) const noexcept
    {
        if (*this == 0)
        {
            return {integer<Tag>(integer_type(0)), false};
        }

        auto value = integer<Tag>::unchecked_create(1);
        bool overflow = false;
        for (const auto _ : std::views::iota(0ul, exp.value_))
        {
            auto [res_value, res_overflow] = this->overflowing_mul(value);
            value = res_value;
            overflow = overflow ? overflow : res_overflow;
        }
        return {value, overflow};
    }

    /**
     * @brief wrapping_abs - Wrapping (modular) absolute value
     * @return self.abs(), wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_abs() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        auto [result, _] = this->overflowing_abs();
        return result;
    }

    /**
     * @brief wrapping_add - Wrapping (modular) addition
     * @return self + rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_add(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_add(rhs);
        return result;
    }

    /**
     * @brief wrapping_add - Wrapping (modular) addition
     * @return self + rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_add(const integer<sign_conversion_tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_add(rhs);
        return result;
    }

    /**
     * @brief wrapping_sub - Wrapping (modular) subtraction
     * @return self - rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_sub(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_sub(rhs);
        return result;
    }

    /**
     * @brief wrapping_sub - Wrapping (modular) subtraction
     * @return self - rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_sub(const integer<sign_conversion_tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_sub(rhs);
        return result;
    }

    /**
     * @brief wrapping_mul - Wrapping (modular) multiplication
     * @return self * rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_mul(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_mul(rhs);
        return result;
    }

    /**
     * @brief wrapping_div - Wrapping (modular) division
     * @return self / rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_div(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_div(rhs);
        return result;
    }

    /**
     * @brief wrapping_div_euclid - Wrapping euclidean division
     * @return self / rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_div_euclid(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_div_euclid(rhs);
        return result;
    }

    /**
     * @brief wrapping_rem - Wrapping (modular) remainder
     * @return self % rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_rem(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_rem(rhs);
        return result;
    }

    /**
     * @brief wrapping_rem_euclid - Wrapping euclidean remainder
     * @return self % rhs, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_rem_euclid(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_rem_euclid(rhs);
        return result;
    }

    /**
     * @brief wrapping_neg - Wrapping (modular) negation
     * @return -self, wrapping around at the boundary of the type.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_neg() const noexcept
    {
        auto [result, _] = this->overflowing_neg();
        return result;
    }

    /**
     * @brief wrapping_pow - Wrapping (modular) exponentiation.
     * @return self.pow(exp), If an overflow would occurred the wrapped value is returned.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_pow(const integer<detail::u32_tag> exp) const noexcept
    {
        auto [result, _] = this->overflowing_pow(exp);
        return result;
    }

    /**
     * @brief abs_diff
     * @return the absolute difference between self and rhs
     */
    [[nodiscard]] constexpr integer<sign_conversion_tag>
    abs_diff(const integer<Tag> rhs) const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        return *this > rhs ? integer<sign_conversion_tag>(
                                 std::make_unsigned_t<integer_type>(this->value_ - rhs.value_))
                           : integer<sign_conversion_tag>(
                                 std::make_unsigned_t<integer_type>(rhs.value_ - this->value_));
    }

    /**
     * @brief abs_diff
     * @return the absolute difference between self and rhs
     */
    [[nodiscard]] constexpr integer<Tag>
    abs_diff(const integer<Tag> rhs) const noexcept
        requires(is_unsigned_integer_v<integer_type>)
    {
        return *this > rhs ? *this - rhs : rhs - *this;
    }

    /**
     * @brief unsigned_abs
     * @return the absolute value of self without any wrapping or panicking.
     */
    [[nodiscard]] constexpr integer<sign_conversion_tag>
    unsigned_abs() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        using unsigned_integer_type =
            typename detail::integer_traits<sign_conversion_tag>::integer_type;

        return static_cast<unsigned_integer_type>(*this < 0 ? -this->value_ : this->value_);
    }

    /**
     * @brief is_power_of_two
     * @return true if self == 2^k for some k
     */
    [[nodiscard]] constexpr bool
    is_power_of_two() const noexcept
        requires(is_unsigned_integer_v<integer_type>)
    {
        return *this != 0 &&
               std::cmp_equal((this->value_ & integer_type(this->value_ - integer_type(1))), 0);
    }

    /**
     * @brief next_power_of_two
     * @return the smallest power of two greater than or equal to self.
     */
    [[nodiscard]] constexpr integer<Tag>
    next_power_of_two() const noexcept
        requires(is_unsigned_integer_v<integer_type>)
    {
        auto x = this->checked_next_power_of_two();
        if (!x)
        {
            if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
            {
                ztd::panic("next_power_of_two() overflow: {}", this->value_);
            }
            else
            {
                return integer<Tag>(integer_type(0));
            }
        }
        return x.value();
    }

    /**
     * @brief checked_next_power_of_two
     * @return the smallest power of two greater than or equal to self.
     *         If the next power of two is greater than the type's maximum
     *         value, std::nullopt is returned.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_next_power_of_two() const noexcept
        requires(is_unsigned_integer_v<integer_type>)
    {
        integer<Tag> x = integer_type(2);
        for (auto idx : std::views::iota(0u, integer<Tag>::BITS().data()))
        {
            auto y = x.checked_pow(idx);
            if (!y)
            {
                return std::nullopt;
            }
            if (*this < y)
            {
                return y;
            }
        }
        // std::unreachable();
        return std::nullopt;
    }

    /**
     * @brief wrapping_next_power_of_two
     * @return the smallest power of two greater than or equal to n. If
     * the next power of two is greater than the type’s maximum value, the
     * return value is wrapped to 0.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_next_power_of_two() const noexcept
        requires(is_unsigned_integer_v<integer_type>)
    {
        auto x = this->checked_next_power_of_two();
        if (!x)
        {
            return integer<Tag>(integer_type(0));
        }
        return x.value();
    }

    /**
     * @brief as
     * @return self casted to type T
     */
    template<typename T>
    [[nodiscard]] T
    as() const noexcept
        requires requires {
            typename T::tag;
            typename T::integer_type;
        }
    {
        return integer<typename T::tag>(static_cast<T::integer_type>(this->value_));
    }

    /**
     * @brief as
     * @return self saturate casted to type T
     */
    template<typename T>
    [[nodiscard]] T
    as_saturate() const noexcept
        requires requires {
            typename T::tag;
            typename T::integer_type;
        }
    {
        return integer<typename T::tag>(std::saturate_cast<typename T::integer_type>(this->value_));
    }

    /**
     * @brief cast_unsigned
     * @return self casted to a unsigned integer of the same size
     */
    [[nodiscard]] constexpr integer<sign_conversion_tag>
    cast_unsigned() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        return integer<sign_conversion_tag>{
            static_cast<std::make_unsigned_t<integer_type>>(this->value_)};
    }

    /**
     * @brief cast_signed
     * @return self casted to a signed integer of the same size
     */
    [[nodiscard]] constexpr integer<sign_conversion_tag>
    cast_signed() const
        requires(is_unsigned_integer_v<integer_type>)
    {
        return integer<sign_conversion_tag>{
            static_cast<std::make_signed_t<integer_type>>(this->value_)};
    }

    /**
     * @brief max
     * @return the largest value between self and rhs
     */
    [[nodiscard]] constexpr integer<Tag>
    max(const integer<Tag> rhs) const noexcept
    {
        return integer<Tag>(std::max(this->value_, rhs.value_));
    }

    /**
     * @brief min
     * @return the smallest value between self and rhs
     */
    [[nodiscard]] constexpr integer<Tag>
    min(const integer<Tag> rhs) const noexcept
    {
        return integer<Tag>(std::min(this->value_, rhs.value_));
    }

    /**
     * @brief signum
     * @return a number that represents the sign of self
     *         - -1 if the number is negative
     *         - 0 if the number is zero
     *         - 1 if the number is positive
     */
    [[nodiscard]] constexpr integer<Tag>
    signum() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        if (*this > 0)
        {
            return integer<Tag>(integer_type(1));
        }
        else if (*this < 0)
        {
            return integer<Tag>(integer_type(-1));
        }
        else
        {
            return integer<Tag>(integer_type(0));
        }
    }

    /**
     * @brief is_positive
     * @return is the current value positive
     */
    [[nodiscard]] constexpr bool
    is_positive() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        return *this > 0;
    }

    /**
     * @brief is_negative
     * @return is the current value negative
     */
    [[nodiscard]] constexpr bool
    is_negative() const noexcept
        requires(is_signed_integer_v<integer_type>)
    {
        return *this < 0;
    }

    /**
     * @brief is_even
     * @return is the current value even
     */
    [[nodiscard]] constexpr bool
    is_even() const noexcept
    {
        return *this % integer<Tag>(integer_type(2)) == integer<Tag>(integer_type(0));
    }

    /**
     * @brief is_odd
     * @return is the current value odd
     */
    [[nodiscard]] constexpr bool
    is_odd() const noexcept
    {
        return !this->is_even();
    }

    /**
     * @brief divmod - Divide two numbers and return the quotient and remainder.
     * @param[in] rhs The denominator
     * @return The quotient and remainder of a division
     */
    [[nodiscard]] constexpr std::array<integer<Tag>, 2>
    divmod(const integer<Tag> rhs) const noexcept
    {
        return {*this / rhs, *this % rhs};
    }

    /**
     * @brief is_multiple_of
     * @return true if self is an integer multiple of rhs, and false otherwise.
     */
    [[nodiscard]] constexpr bool
    is_multiple_of(const integer<Tag> rhs) const noexcept
        requires(is_unsigned_integer_v<integer_type>)
    {
        if (rhs == 0)
        {
            return *this == 0;
        }
        return (this->value_ % rhs.value_) == 0;
    }

    /**
     * @brief next_multiple_of
     * @return the smallest value greater than or equal to self that is
     * a multiple of rhs.
     */
    [[nodiscard]] constexpr integer<Tag>
    next_multiple_of(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            ztd::panic("next_multiple_of() rhs can not be zero");
        }

        auto x = this->checked_next_multiple_of(rhs);
        if (!x)
        {
            if constexpr (std::is_same_v<detail::default_math_tag, detail::math_strict_tag>)
            {
                ztd::panic("next_multiple_of() overflow: {}, {}", this->value_, rhs.value_);
            }
            else
            {
                return integer<Tag>(integer_type(0));
            }
        }
        return x.value();
    }

    /**
     * @brief checked_next_multiple_of
     * @return the smallest value greater than or equal to self that is
     * a multiple of rhs. Returns std::nullopt if rhs is zero or the operation
     * would result in overflow.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_next_multiple_of(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            return std::nullopt;
        }

        if (*this == 0)
        {
            return integer<Tag>(integer_type(0));
        }

        if constexpr (std::is_signed_v<integer_type>)
        {
            if (this->signum() != rhs.signum())
            {
                return integer<Tag>(integer_type(0));
            }
        }

        // overflowing version of div_ceil
        auto [q, q_overflow] = overflowing_div(rhs);
        auto [r, r_overflow] = overflowing_rem(rhs);
        if ((q_overflow || r_overflow))
        {
            return std::nullopt;
        }
        if ((r != 0) && ((r > 0) == (rhs > 0)))
        {
            auto [a, a_overflow] = q.overflowing_add(integer<Tag>(integer_type(1)));
            if (a_overflow)
            {
                return std::nullopt;
            }
            q = a;
        }

        return q.checked_mul(rhs);
    }

    /**
     * @brief A pointer to the underlying value
     * - Useful for C APIs that want a pointer for out arguments
     * @return Pointer to the underlying c value
     */
    [[nodiscard]] integer_type*
    unwrap() noexcept
    { // TODO - tests
        return &this->value_;
    }

    /**
     * @brief Get the underlying c value
     * @return The underlying c value
     */
    [[nodiscard]] constexpr integer_type
    data() const noexcept
    {
        return this->value_;
    }

    // constants

    /**
     * @brief MAX
     * @return the largest value this type can hold
     */
    [[nodiscard]] static constexpr integer<Tag>
    MAX() noexcept
    {
        static constexpr thread_local auto max =
            integer<Tag>(std::numeric_limits<integer_type>::max());
        return max;
    }

    /**
     * @brief MIN
     * @return the smallest value this type can hold
     */
    [[nodiscard]] static constexpr integer<Tag>
    MIN() noexcept
    {
        static constexpr thread_local auto min =
            integer<Tag>(std::numeric_limits<integer_type>::min());
        return min;
    }

    /**
     * @brief BITS
     * @return the size of this integer type in bits.
     */
    [[nodiscard]] static constexpr integer<detail::u32_tag>
    BITS() noexcept
    {
        using integer_type_u32 = typename detail::integer_traits<detail::u32_tag>::integer_type;

        if constexpr (std::is_signed_v<integer_type>)
        {
            return integer<detail::u32_tag>(
                integer_type_u32(std::numeric_limits<integer_type>::digits + 1));
        }
        else
        {
            return integer<detail::u32_tag>(
                integer_type_u32(std::numeric_limits<integer_type>::digits));
        }
    }

#if defined(ZTD_TEST_SUITE)
    // needed for doctest to show values
    friend std::ostream&
    operator<<(std::ostream& os, const integer<Tag> obj)
    {
        os << std::format("{}", obj);
        return os;
    }

    friend std::ostream&
    operator<<(std::ostream& os, const std::optional<integer<Tag>> obj)
    {
        if (obj.has_value())
        {
            os << std::format("{}", obj.value());
        }
        else
        {
            os << std::string("std::nullopt");
        }
        return os;
    }
#endif

  private:
    integer_type value_{0};
};

// arithmetic operators

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator+(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.add(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator-(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.sub(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator*(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.mul(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator/(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.div(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator%(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.rem(rhs);
}

// comparison operators

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator==(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    return std::cmp_equal(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator!=(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    return std::cmp_not_equal(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator<(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    return std::cmp_less(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator<=(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    return std::cmp_less_equal(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator>(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    return std::cmp_greater(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator>=(const T lhs, const integer<Tag> rhs) noexcept
    requires(is_integer_v<T>)
{
    return std::cmp_greater_equal(lhs, rhs.data());
}
} // namespace ztd
