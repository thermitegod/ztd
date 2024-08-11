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
#include <string_view>

#include <array>

#include <magic_enum.hpp>

#include <openssl/evp.h>

#include "types.hxx"

namespace ztd
{
/**
 * Computes the checksum for data.
 * This is a generic API for computing checksums for a sequence of arbitrary bytes,
 * using various hashing algorithms like MD5, SHA-1 and SHA-256.
 */
struct checksum
{
  public:
    checksum() = default;

    checksum(const checksum& other) = default;
    checksum& operator=(const checksum& other) = default;

    checksum(checksum&& other) noexcept = default;
    checksum& operator=(checksum&& other) noexcept = default;

    ~checksum() noexcept { EVP_MD_CTX_free(this->ctx_); }

    enum class type
    {
        md5,

        sha1,
        sha224,
        sha256,
        sha384,
        sha512,

        sha3_224,
        sha3_256,
        sha3_384,
        sha3_512,

        blake2s256,
        blake2b512,
    };

    /**
     * Creates a new Checksum, using the checksum algorithm checksum_type.
     *
     * @param[in] checksum_type Checksum type, one of defined above.
     */
    explicit checksum(type checksum_type)
    {
        EVP_DigestInit(this->ctx_, this->function_ptr_table_[magic_enum::enum_integer(checksum_type)]());
    }

    /**
     * Resets the state of the checksum back to its initial state.
     */
    void
    reset() const noexcept
    {
        EVP_MD_CTX_reset(this->ctx_);
    }

    /**
     * Feeds data into an existing Checksum.
     *
     * @param[in] data Buffer used to compute the checksum
     */
    void
    update(const std::string_view data) const noexcept
    {
        EVP_DigestUpdate(this->ctx_, data.data(), data.size());
    }

    /**
     * Gets the digest as a hexadecimal string.
     *
     * @return The hexadecimal representation of the checksum.
     */
    [[nodiscard]] const std::string
    get_string() const noexcept
    {
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        EVP_DigestFinal_ex(this->ctx_, md_value, &md_len);

        // OPENSSL_buf2hexstr will format the hash as "A6:04:9E:B0"
        // char* hex_str = OPENSSL_buf2hexstr(md_value, md_len);
        // std::string result(hex_str);
        // OPENSSL_free(hex_str);
        // return ztd::replace(ztd::lower(result), ":", "");

        return this->unsigned_char_to_hex_string(md_value, md_len);
    }

    /**
     * Computes the checksum of a string.
     *
     * @param[in] checksum_type A Type
     * @param[in] str The string to compute the checksum of.
     *
     * @return The checksum as a hexadecimal string.
     */
    [[nodiscard]] const std::string
    compute_checksum(type checksum_type, const std::string_view str) const noexcept
    {
        EVP_DigestInit(this->ctx_, this->function_ptr_table_[magic_enum::enum_integer(checksum_type)]());
        this->update(str);
        return this->get_string();
    }

  private:
    EVP_MD_CTX* ctx_{EVP_MD_CTX_new()};

    using openssl_hash_function_ptr = const EVP_MD* (*)();
    static constexpr std::array<openssl_hash_function_ptr, 12> function_ptr_table_{
        EVP_md5,
        EVP_sha1,
        EVP_sha224,
        EVP_sha256,
        EVP_sha384,
        EVP_sha512,
        EVP_sha3_224,
        EVP_sha3_256,
        EVP_sha3_384,
        EVP_sha3_512,
        EVP_blake2s256,
        EVP_blake2b512,
    };

    /**
     * This function must be as fast as possible.
     */
    static const std::string
    unsigned_char_to_hex_string(const unsigned char* data, usize length)
    {
        static constexpr std::array<char, 256 * 2> hex_chars = []()
        {
            std::array<char, 256 * 2> chars{};
            for (i32 i = 0; i < 256; ++i)
            {
                chars[2 * i] = "0123456789abcdef"[i >> 4];
                chars[2 * i + 1] = "0123456789abcdef"[i & 0x0f];
            }
            return chars;
        }();

        std::string hex_string(length * 2, ' ');
        for (usize i = 0; i < length; ++i)
        {
            hex_string[2 * i] = hex_chars[data[i] * 2];
            hex_string[2 * i + 1] = hex_chars[data[i] * 2 + 1];
        }
        return hex_string;
    }
};

/**
 * Computes the checksum of a string.
 *
 * @param[in] checksum_type A Type
 * @param[in] str The string to compute the checksum of.
 *
 * @return The checksum as a hexadecimal string.
 */
[[nodiscard]] inline const std::string
compute_checksum(checksum::type type, const std::string_view str) noexcept
{
    const auto check = ztd::checksum();
    return check.compute_checksum(type, str);
}
} // namespace ztd
