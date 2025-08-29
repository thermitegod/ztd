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
#include <bit>
#include <concepts>
#include <format>
#include <limits>
#include <numeric>
#include <optional>
#include <ranges>
#include <tuple>
#include <type_traits>
#include <utility>

#include <cmath>

#include "../concepts.hxx"
#include "../panic.hxx"
#include "../random.hxx"
#include "../utils.hxx"
#include "integer_type.hxx"

#if defined(MIN)
#undef MIN
#endif

#if defined(MAX)
#undef MAX
#endif

namespace ztd
{
namespace detail
{
// clang-format off
template<typename T, typename U> constexpr bool is_integer_conversion_safe =
    (sizeof(T) <= sizeof(U) && is_signed_integer<T> == is_signed_integer<U>) ||
    (sizeof(T) < sizeof(U) && is_unsigned_integer<T> && is_signed_integer<U>);
// clang-format on
} // namespace detail

template<typename Tag> class integer final
{
  public:
    using tag = Tag;
    using integer_type = typename ztd::integer_type<Tag>::type;
    using sign_conversion = typename ztd::integer_type<Tag>::sign_conversion;
    static_assert(detail::is_integer<integer_type>);

    static_assert(sizeof(integer_type) ==
                  sizeof(typename ztd::integer_type<sign_conversion>::type));
    static_assert(!std::same_as<integer_type, typename ztd::integer_type<sign_conversion>::type>);

    template<typename T> friend class integer;

    constexpr integer() noexcept : value_(0) {}

    template<typename T>
    constexpr integer(const T rhs) noexcept
        requires(std::same_as<T, bool>)
    = delete ("help: cannot construct an integer from a bool");

    template<typename T>
    // constexpr explicit integer(const T rhs)
    constexpr integer(const T rhs) noexcept
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        requires(detail::is_integer<T>)
    {
        if constexpr (!detail::is_integer_conversion_safe<T, integer_type>)
        {
            if constexpr (detail::is_signed_integer<integer_type>)
            {
                if (std::cmp_less(rhs, std::numeric_limits<integer_type>::min()))
                {
                    return std::nullopt;
                }
            }
            else if constexpr (detail::is_unsigned_integer<integer_type>)
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
     * @brief strict_create - Create an integer with bounds checking. If the integral
     * value will not fit in this type then panic.
     * @param[in] v Integral to create from
     * @return The integer
     */
    template<typename T>
    [[nodiscard]] static constexpr integer<Tag>
    strict_create(const T rhs) noexcept
        requires(detail::is_integer<T>)
    {
        auto x = integer<Tag>::checked_create(rhs);
        ztd::panic_if(!x, "attempt to create integer overflows");
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
    {
        return integer<Tag>(std::saturate_cast<integer_type>(v));
    }

    /**
     * @brief random - get a random value between (min, max)
     * @return a random value
     */
    [[nodiscard]] static constexpr integer<Tag>
    random() noexcept
    {
        static std::uniform_int_distribution<integer_type> dist(
            std::numeric_limits<integer_type>::min(),
            std::numeric_limits<integer_type>::max());

        return integer<Tag>(dist(detail::rng()));
    }

    /**
     * @brief random - get a random value between (min, max)
     * @param[in] min min random value
     * @param[in] max max random value
     * @return a random value
     */
    [[nodiscard]] static constexpr integer<Tag>
    random(const integer<Tag> min, const integer<Tag> max) noexcept
    {
        return integer<Tag>(ztd::random(min.value_, max.value_));
    }

    // conversions operators

    explicit operator bool() = delete ("help: use either '!= 0' or '== 0'");

    constexpr operator uint8_t() = delete ("help: implicit conversion is not supported");
    constexpr operator uint16_t() = delete ("help: implicit conversion is not supported");
    constexpr operator uint32_t() = delete ("help: implicit conversion is not supported");
    constexpr operator uint64_t() = delete ("help: implicit conversion is not supported");

    constexpr operator int8_t() = delete ("help: implicit conversion is not supported");
    constexpr operator int16_t() = delete ("help: implicit conversion is not supported");
    constexpr operator int32_t() = delete ("help: implicit conversion is not supported");
    constexpr operator int64_t() = delete ("help: implicit conversion is not supported");

    constexpr operator float() = delete ("help: implicit conversion is not supported");
    constexpr operator double() = delete ("help: implicit conversion is not supported");

    // assignment operators

    constexpr integer<Tag>&
    operator=(const bool rhs) = delete ("help: cannot assign a bool to an integer");

    template<typename T>
    constexpr integer<Tag>&
    operator=(const T rhs) noexcept
        requires(detail::is_integer<T>)
    {
        this->value_ = rhs;
        return *this;
    }

    // unary operators

    constexpr integer<Tag>
    operator+() const noexcept
        requires(detail::is_signed_integer<integer_type>)
    {
        return *this;
    }

    constexpr integer<Tag>
    operator-() const noexcept
        requires(detail::is_signed_integer<integer_type>)
    {
        return this->neg();
    }

    // increment/decrement operators

    constexpr integer<Tag>& operator++() = delete ("help: use '+= 1' instead");
    constexpr integer<Tag> operator++(int) = delete ("help: use '+= 1' instead");
    constexpr integer<Tag>& operator--() = delete ("help: use '-= 1' instead");
    constexpr integer<Tag> operator--(int) = delete ("help: use '-= 1' instead");

    // arithmetic operators

    [[nodiscard]] constexpr integer<Tag>
    operator+(const integer<Tag> rhs) const noexcept
    {
        return this->add(rhs);
    }

    template<typename T>
    [[nodiscard]] constexpr integer<Tag>
    operator+(const T rhs) const noexcept
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_integer<T>)
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
        requires(detail::is_signed_integer<integer_type>)
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
    add(const integer<sign_conversion> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
    sub(const integer<sign_conversion> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
        {
            return this->strict_div(rhs);
        }
        else
        {
            return this->wrapping_div(rhs);
        }
    }

    /**
     * @brief div_down - integer division
     * NOTE - this has the same behaviour as div(), use when you want to explicitly
     * set the rounding mode.
     * @return self / rhs, rounded towards zero. side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_down(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
        {
            return this->strict_div_down(rhs);
        }
        else
        {
            return this->wrapping_div_down(rhs);
        }
    }

    /**
     * @brief div_up - integer division
     * @return self / rhs, rounded away from zero. side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_up(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
        {
            return this->strict_div_up(rhs);
        }
        else
        {
            return this->wrapping_div_up(rhs);
        }
    }

    /**
     * @brief div_floor - integer division
     * @return self / rhs, rounded towards negative infinity. side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_floor(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
        {
            return this->strict_div_floor(rhs);
        }
        else
        {
            return this->wrapping_div_floor(rhs);
        }
    }

    /**
     * @brief div_ceil - integer division
     * @return self / rhs, rounded towards positive infinity. side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_ceil(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
        {
            return this->strict_div_ceil(rhs);
        }
        else
        {
            return this->wrapping_div_ceil(rhs);
        }
    }

    /**
     * @brief div_euclid - euclidean division
     * @return self / rhs, rounded towards the nearest integer. Exact ties are
     * rounded towards positive infinity. side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    div_euclid(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
        {
            return this->strict_div_euclid(rhs);
        }
        else
        {
            return this->wrapping_div_euclid(rhs);
        }
    }

    /**
     * @brief rem - integer remainder
     * @return self % rhs, side effects determined by default math mode.
     */
    [[nodiscard]] constexpr integer<Tag>
    rem(const integer<Tag> rhs) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
    pow(const integer<detail::u32> exp) const noexcept
    {
        if constexpr (std::same_as<detail::default_math, detail::math_strict>)
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
        requires(detail::is_signed_integer<integer_type>)
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
    checked_add(const integer<sign_conversion> rhs) const noexcept
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
    checked_sub(const integer<sign_conversion> rhs) const noexcept
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
     * @brief checked_div_down - Checked integer division
     * NOTE - this has the same behaviour as div(), use when you want to explicitly
     * set the rounding mode.
     * @return self / rhs, rounded towards zero, or std::nullopt if a overflow,
     * underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_div_down(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_div
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_div_down(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_div_up - Checked integer division
     * @return self / rhs, rounded away from zero, or std::nullopt if a
     * overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_div_up(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_div
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_div_up(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_div_floor - Checked integer division
     * @return self / rhs, rounded towards negative infinity, or std::nullopt
     * if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_div_floor(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_div
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_div_floor(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_div_ceil - Checked integer division
     * @return self / rhs, rounded towards positive infinity, or std::nullopt
     * if a overflow, underflow, or other error occured.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_div_ceil(const integer<Tag> rhs) const noexcept
    {
        if (rhs == 0)
        {
            // Have to have this check because overflowing_div
            // will panic on division by zero.
            return std::nullopt;
        }

        auto [result, overflow] = this->overflowing_div_ceil(rhs);
        if (overflow)
        {
            return std::nullopt;
        }
        return result;
    }

    /**
     * @brief checked_div_euclid - Checked euclidean division
     * @return self / rhs, rounded towards the nearest integer. Exact ties are
     * rounded towards positive infinity, or std::nullopt if a overflow, underflow,
     * or other error occured.
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
    checked_pow(const integer<detail::u32> exp) const noexcept
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
        requires(detail::is_signed_integer<integer_type>)
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
    [[nodiscard]] constexpr integer<Tag> saturating_add(const integer<sign_conversion> rhs)
        const noexcept = delete ("TODO std::add_sat requires both args are the same type");

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
    [[nodiscard]] constexpr integer<Tag> saturating_sub(const integer<sign_conversion> rhs)
        const noexcept = delete ("TODO std::sub_sat requires both args are the same type");

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
        panic_if(rhs == 0, panic_type::div_zero);
        return integer<Tag>(std::div_sat(this->value_, rhs.value_));
    }

    /**
     * @brief saturating_div_down - Saturating integer division
     * NOTE - this has the same behaviour as div(), use when you want to explicitly
     * set the rounding mode.
     * @return self / rhs, rounded towards zero, instead of overflowing will return
     * a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_div_down(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_down(rhs);
        if (overflow)
        {
            return integer<Tag>::MAX();
        }
        return result;
    }

    /**
     * @brief saturating_div_up - Saturating integer division
     * @return self / rhs, rounded away from zero, instead of overflowing will
     * return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_div_up(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_up(rhs);
        if (overflow)
        {
            return integer<Tag>::MAX();
        }
        return result;
    }

    /**
     * @brief saturating_div_floor - Saturating integer division
     * @return self / rhs, rounded towards negative infinity, instead of overflowing
     * will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_div_floor(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_floor(rhs);
        if (overflow)
        {
            return integer<Tag>::MAX();
        }
        return result;
    }

    /**
     * @brief saturating_div_ceil - Saturating integer division
     * @return self / rhs, rounded towards positive infinity, instead of overflowing
     * will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_div_ceil(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_ceil(rhs);
        if (overflow)
        {
            return integer<Tag>::MAX();
        }
        return result;
    }

    /**
     * @brief saturating_div_euclid - Saturating euclidean division
     * @return self / rhs, rounded towards the nearest integer. Exact ties are
     * rounded towards positive infinity, instead of overflowing will return a
     * saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_div_euclid(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_euclid(rhs);
        if (overflow)
        {
            return integer<Tag>::MAX();
        }
        return result;
    }

    /**
     * @brief saturating_neg - Saturating integer negation
     * @return -self, instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_neg() const noexcept
        requires(detail::is_signed_integer<integer_type>)
    {
        return this->saturating_mul(integer<Tag>(integer_type(-1)));
    }

    /**
     * @brief saturating_pow - Strict integer exponentiation.
     * @return self.pow(exp), instead of overflowing will return a saturated value.
     */
    [[nodiscard]] constexpr integer<Tag>
    saturating_pow(const integer<detail::u32> exp) const noexcept
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
        requires(detail::is_signed_integer<integer_type>)
    {
        auto x = this->checked_abs();
        panic_if(!x, panic_type::neg);
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
        panic_if(overflow, panic_type::add);
        return result;
    }

    /**
     * @brief strict_add - Strict integer addition
     * @return self + rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_add(const integer<sign_conversion> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_add(rhs);
        panic_if(overflow, panic_type::add);
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
        panic_if(overflow, panic_type::sub);
        return result;
    }

    /**
     * @brief strict_sub - Strict integer subtraction
     * @return self - rhs, will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_sub(const integer<sign_conversion> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_sub(rhs);
        panic_if(overflow, panic_type::sub);
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
        panic_if(overflow, panic_type::mul);
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
        panic_if(overflow, panic_type::div);
        return result;
    }

    /**
     * @brief strict_div_down - Strict integer division
     * NOTE - this has the same behaviour as div(), use when you want to explicitly
     * set the rounding mode.
     * @return self / rhs, rounded towards zero. Will panic on any overflow,
     * underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_div_down(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_down(rhs);
        panic_if(overflow, panic_type::div);
        return result;
    }

    /**
     * @brief strict_div_up - Strict integer division
     * @return self / rhs, rounded away from zero. Will panic on any
     * overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_div_up(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_up(rhs);
        panic_if(overflow, panic_type::div);
        return result;
    }

    /**
     * @brief strict_div_floor - Strict integer division
     * @return self / rhs, rounded towards negative infinity. Will panic on
     * any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_div_floor(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_floor(rhs);
        panic_if(overflow, panic_type::div);
        return result;
    }

    /**
     * @brief strict_div_ceil - Strict integer division
     * @return self / rhs, rounded towards positive infinity. Will panic on
     * any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_div_ceil(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_ceil(rhs);
        panic_if(overflow, panic_type::div);
        return result;
    }

    /**
     * @brief strict_div_euclid - Strict euclidean division
     * @return self / rhs, rounded towards the nearest integer. Exact ties are
     * rounded towards positive infinity. Will panic on any overflow, underflow,
     * or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_div_euclid(const integer<Tag> rhs) const noexcept
    {
        auto [result, overflow] = this->overflowing_div_euclid(rhs);
        panic_if(overflow, panic_type::div);
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
        panic_if(overflow, panic_type::rem);
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
        panic_if(overflow, panic_type::rem);
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
        panic_if(overflow, panic_type::neg);
        return result;
    }

    /**
     * @brief strict_pow - Strict integer exponentiation.
     * @return self.pow(exp), will panic on any overflow, underflow, or any other error that occured.
     */
    [[nodiscard]] constexpr integer<Tag>
    strict_pow(const integer<detail::u32> exp) const noexcept
    {
        auto [result, overflow] = this->overflowing_pow(exp);
        panic_if(overflow, panic_type::mul);
        return result;
    }

    /**
     * @brief overflowing_abs - Wrapping (modular) absolute value
     * @return self.abs(), If an overflow would occur the minimum value will be returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_abs() const noexcept
        requires(detail::is_signed_integer<integer_type>)
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
    overflowing_add(const integer<sign_conversion> rhs) const noexcept
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
    overflowing_sub(const integer<sign_conversion> rhs) const noexcept
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
        panic_if(rhs == 0, panic_type::div_zero);

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }
        }
        return {integer<Tag>(integer_type(this->value_ / rhs.value_)), false};
    }

    /**
     * @brief overflowing_div_down - Wrapping (modular) division
     * NOTE - this has the same behaviour as div(), use when you want to explicitly
     * set the rounding mode.
     * @return self / rhs, rounded towards zero. If an overflow would occur then
     * MIN is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_div_down(const integer<Tag> rhs) const noexcept
    {
        return this->overflowing_div(rhs);
    }

    /**
     * @brief overflowing_div_up - Wrapping (modular) division
     * @return self / rhs, rounded away from zero. If an overflow would occur then
     * MIN is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_div_up(const integer<Tag> rhs) const noexcept
    {
        panic_if(rhs == 0, panic_type::div_zero);

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }
        }

        auto d = this->value_ / rhs.value_;
        auto r = this->value_ % rhs.value_;

        auto quotient_sign = this->signum() * rhs.signum();
        auto result = d + ((r != 0) * quotient_sign.value_);

        return {integer<Tag>(integer_type(result)), false};
    }

    /**
     * @brief overflowing_div_floor - Wrapping (modular) division
     * @return self / rhs, rounded towards negative infinity. If an overflow would
     * occur then MIN is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_div_floor(const integer<Tag> rhs) const noexcept
    {
        panic_if(rhs == 0, panic_type::div_zero);

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }
        }

        auto d = this->value_ / rhs.value_;
        auto r = this->value_ % rhs.value_;

        auto quotient_negative = (*this < 0) != (rhs < 0);
        auto result = d - (r != 0 && quotient_negative);

        return {integer<Tag>(integer_type(result)), false};
    }

    /**
     * @brief overflowing_div_ceil - Wrapping (modular) division
     * @return self / rhs, rounded towards positive infinity. If an overflow would
     * occur then MIN is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_div_ceil(const integer<Tag> rhs) const noexcept
    {
        panic_if(rhs == 0, panic_type::div_zero);

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }
        }

        auto d = this->value_ / rhs.value_;
        auto r = this->value_ % rhs.value_;

        auto quotient_positive = (*this < 0) == (rhs < 0);
        auto result = d + (r != 0 && quotient_positive);

        return {integer<Tag>(integer_type(result)), false};
    }

    /**
     * @brief overflowing_div_euclid - Wrapping euclidean division
     * @return self / rhs, rounded towards the nearest integer. Exact ties are
     * rounded towards positive infinity. If an overflow would occur then MIN is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_div_euclid(const integer<Tag> rhs) const noexcept
    {
        panic_if(rhs == 0, panic_type::div_zero);

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>::MIN(), true};
            }

            return rhs < 0 ? this->overflowing_div_ceil(rhs) : this->overflowing_div_floor(rhs);
        }
        else
        {
            return this->overflowing_div_floor(rhs);
        }
    }

    /**
     * @brief overflowing_rem - Wrapping (modular) remainder
     * @return self % rhs, If an overflow would occur then 0 is returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_rem(const integer<Tag> rhs) const noexcept
    {
        panic_if(rhs == 0, panic_type::rem_zero);

        if constexpr (detail::is_signed_integer<integer_type>)
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
        panic_if(rhs == 0, panic_type::rem_zero);

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            if (rhs == -1 && *this == integer<Tag>::MIN())
            {
                return {integer<Tag>(integer_type(0)), true};
            }

            auto r = this->rem(rhs);
            if (r < 0)
            {
                if (rhs < 0)
                {
                    return {integer<Tag>(integer_type(r.value_ - rhs.value_)), false};
                }
                else
                {
                    return {integer<Tag>(integer_type(r.value_ + rhs.value_)), false};
                }
            }
            else
            {
                return {r, false};
            }
        }
        else
        {
            return {this->rem(rhs), false};
        }
    }

    /**
     * @brief overflowing_neg - Wrapping (modular) negation
     * @return -self, If an overflow would occur the minimum value will be returned.
     */
    [[nodiscard]] constexpr std::tuple<integer<Tag>, bool>
    overflowing_neg() const noexcept
    {
        if constexpr (detail::is_signed_integer<integer_type>)
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
    overflowing_pow(const integer<detail::u32> exp) const noexcept
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
        requires(detail::is_signed_integer<integer_type>)
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
    wrapping_add(const integer<sign_conversion> rhs) const noexcept
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
    wrapping_sub(const integer<sign_conversion> rhs) const noexcept
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
     * @brief wrapping_div_down - Wrapping (modular) division
     * NOTE - this has the same behaviour as div(), use when you want to explicitly
     * set the rounding mode.
     * @return self / rhs, rounded towards zero.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_div_down(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_div_down(rhs);
        return result;
    }

    /**
     * @brief wrapping_div_up - Wrapping (modular) division
     * @return self / rhs, rounded away from zero.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_div_up(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_div_up(rhs);
        return result;
    }

    /**
     * @brief wrapping_div_floor - Wrapping (modular) division
     * @return self / rhs, rounded towards negative infinity.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_div_floor(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_div_floor(rhs);
        return result;
    }

    /**
     * @brief wrapping_div_ceil - Wrapping (modular) division
     * @return self / rhs, rounded towards positive infinity.
     */
    [[nodiscard]] constexpr integer<Tag>
    wrapping_div_ceil(const integer<Tag> rhs) const noexcept
    {
        auto [result, _] = this->overflowing_div_ceil(rhs);
        return result;
    }

    /**
     * @brief wrapping_div_euclid - Wrapping euclidean division
     * @return self / rhs, rounded towards the nearest integer. Exact ties are
     * rounded towards positive infinity.
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
    wrapping_pow(const integer<detail::u32> exp) const noexcept
    {
        auto [result, _] = this->overflowing_pow(exp);
        return result;
    }

    /**
     * @brief abs_diff
     * @return the absolute difference between self and rhs
     */
    [[nodiscard]] constexpr integer<sign_conversion>
    abs_diff(const integer<Tag> rhs) const noexcept
        requires(detail::is_signed_integer<integer_type>)
    {
        return *this > rhs ? integer<sign_conversion>(
                                 std::make_unsigned_t<integer_type>(this->value_ - rhs.value_))
                           : integer<sign_conversion>(
                                 std::make_unsigned_t<integer_type>(rhs.value_ - this->value_));
    }

    /**
     * @brief abs_diff
     * @return the absolute difference between self and rhs
     */
    [[nodiscard]] constexpr integer<Tag>
    abs_diff(const integer<Tag> rhs) const noexcept
        requires(detail::is_unsigned_integer<integer_type>)
    {
        return *this > rhs ? *this - rhs : rhs - *this;
    }

    /**
     * @brief unsigned_abs
     * @return the absolute value of self without any wrapping or panicking.
     */
    [[nodiscard]] constexpr integer<sign_conversion>
    unsigned_abs() const noexcept
        requires(detail::is_signed_integer<integer_type>)
    {
        using unsigned_integer_type = typename ztd::integer_type<sign_conversion>::type;

        return static_cast<unsigned_integer_type>(*this < 0 ? -this->value_ : this->value_);
    }

    /**
     * @brief count_ones
     * @return the number of ones in the binary representation of self.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    count_ones() const noexcept
    {
        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            using unsigned_integer_type = typename ztd::integer_type<sign_conversion>::type;

            return integer<detail::u32>(static_cast<integer_type_u32>(
                std::popcount(static_cast<unsigned_integer_type>(this->value_))));
        }
        else
        {
            return integer<detail::u32>(static_cast<integer_type_u32>(std::popcount(this->value_)));
        }
    }

    /**
     * @brief count_zeros
     * @return the number of zeros in the binary representation of self.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    count_zeros() const noexcept
    {
        return this->count_ones().abs_diff(integer<Tag>::BITS());
    }

    /**
     * @brief leading_ones
     * @return the number of leading ones in the binary representation of self.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    leading_ones() const noexcept
    {
        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            return integer<detail::u32>(static_cast<integer_type_u32>(
                std::countl_one(static_cast<std::make_unsigned_t<integer_type>>(this->value_))));
        }
        else
        {
            return integer<detail::u32>(
                static_cast<integer_type_u32>(std::countl_one(this->value_)));
        }
    }

    /**
     * @brief leading_zeros
     * @return the number of leading zeros in the binary representation of self.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    leading_zeros() const noexcept
    {
        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            return integer<detail::u32>(static_cast<integer_type_u32>(
                std::countl_zero(static_cast<std::make_unsigned_t<integer_type>>(this->value_))));
        }
        else
        {
            return integer<detail::u32>(
                static_cast<integer_type_u32>(std::countl_zero(this->value_)));
        }
    }

    /**
     * @brief trailing_ones
     * @return the number of trailing ones in the binary representation of self.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    trailing_ones() const noexcept
    {
        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            return integer<detail::u32>(static_cast<integer_type_u32>(
                std::countr_one(static_cast<std::make_unsigned_t<integer_type>>(this->value_))));
        }
        else
        {
            return integer<detail::u32>(
                static_cast<integer_type_u32>(std::countr_one(this->value_)));
        }
    }

    /**
     * @brief trailing_zeros
     * @return the number of trailing zeros in the binary representation of self.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    trailing_zeros() const noexcept
    {
        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            return integer<detail::u32>(static_cast<integer_type_u32>(
                std::countr_zero(static_cast<std::make_unsigned_t<integer_type>>(this->value_))));
        }
        else
        {
            return integer<detail::u32>(
                static_cast<integer_type_u32>(std::countr_zero(this->value_)));
        }
    }

    /**
     * @brief rotate_right
     * @return the bits shifted to the right by a specified amount, n, wrapping
     * the truncated bits to the end of the resulting integer.
     */
    [[nodiscard]] constexpr integer<Tag>
    rotate_right(const integer<detail::i32> n) const noexcept
    { // TODO - tests
        if constexpr (detail::is_signed_integer<integer_type>)
        {
            return integer<Tag>(static_cast<integer_type>(
                std::rotr(static_cast<std::make_unsigned_t<integer_type>>(this->value_),
                          n.value_)));
        }
        else
        {
            return integer<Tag>(std::rotr(this->value_, n.value_));
        }
    }

    /**
     * @brief rotate_left
     * @return the bits shifted to the left by a specified amount, n, wrapping
     * the truncated bits to the end of the resulting integer.
     */
    [[nodiscard]] constexpr integer<Tag>
    rotate_left(const integer<detail::i32> n) const noexcept
    { // TODO - tests
        if constexpr (detail::is_signed_integer<integer_type>)
        {
            return integer<Tag>(static_cast<integer_type>(
                std::rotl(static_cast<std::make_unsigned_t<integer_type>>(this->value_),
                          n.value_)));
        }
        else
        {
            return integer<Tag>(std::rotl(this->value_, n.value_));
        }
    }

    /**
     * @brief swap_bytes
     * @return reverses the byte order of the integer.
     */
    [[nodiscard]] constexpr integer<Tag>
    swap_bytes() const noexcept
    { // TODO - tests
        return integer<Tag>(std::byteswap(this->value_));
    }

    /**
     * @brief is_power_of_two
     * @return true if self == 2^k for some k
     */
    [[nodiscard]] constexpr bool
    is_power_of_two() const noexcept
        requires(detail::is_unsigned_integer<integer_type>)
    {
        return std::has_single_bit(this->value_);
    }

    /**
     * @brief next_power_of_two
     * @return the smallest power of two greater than or equal to self.
     */
    [[nodiscard]] constexpr integer<Tag>
    next_power_of_two() const noexcept
        requires(detail::is_unsigned_integer<integer_type>)
    {
        auto x = this->checked_next_power_of_two();
        if (!x)
        {
            if constexpr (std::same_as<detail::default_math, detail::math_strict>)
            {
                ztd::panic("next power of two overflow");
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
        requires(detail::is_unsigned_integer<integer_type>)
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
        requires(detail::is_unsigned_integer<integer_type>)
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
    [[nodiscard]] constexpr integer<sign_conversion>
    cast_unsigned() const noexcept
        requires(detail::is_signed_integer<integer_type>)
    {
        return integer<sign_conversion>{
            static_cast<std::make_unsigned_t<integer_type>>(this->value_)};
    }

    /**
     * @brief cast_signed
     * @return self casted to a signed integer of the same size
     */
    [[nodiscard]] constexpr integer<sign_conversion>
    cast_signed() const
        requires(detail::is_unsigned_integer<integer_type>)
    {
        return integer<sign_conversion>{
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
    {
        if (this->is_positive())
        {
            return integer<Tag>(integer_type(1));
        }
        else if (this->is_negative())
        {
            return integer<Tag>(integer_type(-1));
        }
        else if (this->is_zero())
        {
            return integer<Tag>(integer_type(0));
        }
        std::unreachable();
    }

    /**
     * @brief is_positive
     * @return is the current value positive
     */
    [[nodiscard]] constexpr bool
    is_positive() const noexcept
    {
        return *this > 0;
    }

    /**
     * @brief is_negative
     * @return is the current value negative
     */
    [[nodiscard]] constexpr bool
    is_negative() const noexcept
    {
        return *this < 0;
    }

    /**
     * @brief is_zero
     * @return is the current value zero
     */
    [[nodiscard]] constexpr bool
    is_zero() const noexcept
    {
        return *this == 0;
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
     * @brief ilog
     * @return the logarithm of the number with respect to an arbitrary base, rounded down.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    ilog(const integer<Tag>& base) const
    {
        ztd::panic_if(*this <= 0, "argument of integer logarithm must be positive");
        ztd::panic_if(base < 2, "base of integer logarithm must be at least 2");

        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;
        return integer<detail::u32>(static_cast<integer_type_u32>(
            std::log<integer_type>(this->value_) / std::log<integer_type>(base.value_)));
    }

    /**
     * @brief ilog2
     * @return the base 2 logarithm of the number, rounded down.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    ilog2() const
    {
        ztd::panic_if(*this <= 0, "argument of integer logarithm must be positive");

        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;
        return integer<detail::u32>(
            static_cast<integer_type_u32>(std::log2<integer_type>(this->value_)));
    }

    /**
     * @brief ilog10
     * @return the base 10 logarithm of the number, rounded down.
     */
    [[nodiscard]] constexpr integer<detail::u32>
    ilog10() const
    {
        ztd::panic_if(*this <= 0, "argument of integer logarithm must be positive");

        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;
        return integer<detail::u32>(
            static_cast<integer_type_u32>(std::log10<integer_type>(this->value_)));
    }

    /**
     * @brief checked_ilog
     * @return the logarithm of the number with respect to an arbitrary base, rounded down.
     */
    [[nodiscard]] constexpr std::optional<integer<detail::u32>>
    checked_ilog(const integer<Tag>& base) const noexcept
    {
        if (*this <= 0 || base < 2)
        {
            return std::nullopt;
        }
        return this->ilog(base);
    }

    /**
     * @brief checked_ilog2
     * @return the base 2 logarithm of the number, rounded down.
     */
    [[nodiscard]] constexpr std::optional<integer<detail::u32>>
    checked_ilog2() const noexcept
    {
        if (*this <= 0)
        {
            return std::nullopt;
        }
        return this->ilog2();
    }

    /**
     * @brief checked_ilog10
     * @return the base 10 logarithm of the number, rounded down.
     */
    [[nodiscard]] constexpr std::optional<integer<detail::u32>>
    checked_ilog10() const noexcept
    {
        if (*this <= 0)
        {
            return std::nullopt;
        }
        return this->ilog10();
    }

    /**
     * @brief isqrt
     * @return the square root of the number, rounded down.
     */
    [[nodiscard]] constexpr integer<Tag>
    isqrt() const noexcept
    {
        ztd::panic_if(*this < 0, "argument of integer square root cannot be negative");

        return integer<Tag>(static_cast<integer_type>(std::sqrt<integer_type>(this->value_)));
    }

    /**
     * @brief checked_isqrt
     * @return the square root of the number, rounded down, or std::nullopt if self is negative.
     */
    [[nodiscard]] constexpr std::optional<integer<Tag>>
    checked_isqrt() const noexcept
        requires(detail::is_signed_integer<integer_type>)
    {
        if (*this < 0)
        {
            return std::nullopt;
        }
        return this->isqrt();
    }

    /**
     * @brief is_multiple_of
     * @return true if self is an integer multiple of rhs, and false otherwise.
     */
    [[nodiscard]] constexpr bool
    is_multiple_of(const integer<Tag> rhs) const noexcept
        requires(detail::is_unsigned_integer<integer_type>)
    {
        if (rhs == 0)
        {
            return *this == 0;
        }
        return this->rem(rhs) == 0;
    }

    /**
     * @brief next_multiple_of
     * @return the smallest value greater than or equal to self that is
     * a multiple of rhs.
     */
    [[nodiscard]] constexpr integer<Tag>
    next_multiple_of(const integer<Tag> rhs) const noexcept
    {
        ztd::panic_if(rhs == 0, "argument of next multiple cannot be zero");

        auto x = this->checked_next_multiple_of(rhs);
        if (!x)
        {
            if constexpr (std::same_as<detail::default_math, detail::math_strict>)
            {
                ztd::panic("next multiple overflow");
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

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            if (this->signum() != rhs.signum())
            {
                return integer<Tag>(integer_type(0));
            }
        }

        auto q = this->checked_div_ceil(rhs);
        if (!q)
        {
            return std::nullopt;
        }
        return (*q).checked_mul(rhs);
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
    [[nodiscard]] static constexpr integer<detail::u32>
    BITS() noexcept
    {
        using integer_type_u32 = typename ztd::integer_type<detail::u32>::type;

        if constexpr (detail::is_signed_integer<integer_type>)
        {
            return integer<detail::u32>(
                integer_type_u32(std::numeric_limits<integer_type>::digits + 1));
        }
        else
        {
            return integer<detail::u32>(
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
    enum class panic_type : std::uint8_t
    {
        add,
        sub,
        mul,
        div,
        div_zero,
        rem,
        rem_zero,
        neg,
        shr,
        shl,
    };

    static constexpr void
    panic_if(const bool cond, const panic_type t) noexcept
    {
        if (!cond) [[likely]]
        {
            return;
        }

        switch (t)
        {
            case panic_type::add:
                ztd::panic("attempt to add with overflow");
            case panic_type::sub:
                ztd::panic("attempt to subtract with overflow");
            case panic_type::mul:
                ztd::panic("attempt to multiply with overflow");
            case panic_type::div:
                ztd::panic("attempt to divide with overflow");
            case panic_type::div_zero:
                ztd::panic("attempt to divide by zero");
            case panic_type::rem:
                ztd::panic("attempt to calculate the remainder with overflow");
            case panic_type::rem_zero:
                ztd::panic("attempt to calculate the remainder with a divisor of zero");
            case panic_type::neg:
                ztd::panic("attempt to negate with overflow");
            case panic_type::shr:
                ztd::panic("attempt to shift right with overflow");
            case panic_type::shl:
                ztd::panic("attempt to shift left with overflow");
        }
        std::unreachable();
    }

    integer_type value_{0};
};

// arithmetic operators

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator+(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.add(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator-(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.sub(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator*(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.mul(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator/(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.div(rhs);
}

template<typename T, typename Tag>
[[nodiscard]] constexpr integer<Tag>
operator%(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    auto x = integer<Tag>::create(lhs);
    return x.rem(rhs);
}

// comparison operators

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator==(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    return std::cmp_equal(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator!=(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    return std::cmp_not_equal(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator<(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    return std::cmp_less(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator<=(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    return std::cmp_less_equal(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator>(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    return std::cmp_greater(lhs, rhs.data());
}

template<typename T, typename Tag>
[[nodiscard]] constexpr bool
operator>=(const T lhs, const integer<Tag> rhs) noexcept
    requires(detail::is_integer<T>)
{
    return std::cmp_greater_equal(lhs, rhs.data());
}
} // namespace ztd
