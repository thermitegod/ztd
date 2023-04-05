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

#include <openssl/evp.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/checksum.hxx"

using openssl_hash_function_ptr = const EVP_MD* (*)();

static const std::map<ztd::Checksum::Type, openssl_hash_function_ptr> HashTable{
    {ztd::Checksum::Type::MD5, EVP_md5},
    {ztd::Checksum::Type::SHA1, EVP_sha1},
    {ztd::Checksum::Type::SHA224, EVP_sha224},
    {ztd::Checksum::Type::SHA256, EVP_sha256},
    {ztd::Checksum::Type::SHA384, EVP_sha384},
    {ztd::Checksum::Type::SHA512, EVP_sha512},
    {ztd::Checksum::Type::SHA3_224, EVP_sha3_224},
    {ztd::Checksum::Type::SHA3_256, EVP_sha3_256},
    {ztd::Checksum::Type::SHA3_384, EVP_sha3_384},
    {ztd::Checksum::Type::SHA3_512, EVP_sha3_512},
    {ztd::Checksum::Type::BLAKE2S256, EVP_blake2s256},
    {ztd::Checksum::Type::BLAKE2B512, EVP_blake2b512},
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

ztd::Checksum::~Checksum() noexcept
{
    EVP_MD_CTX_free(this->ctx);
}

ztd::Checksum::Checksum(Type checksum_type)
{
    EVP_DigestInit(this->ctx, HashTable.at(checksum_type)());
}

void
ztd::Checksum::reset()
{
    EVP_MD_CTX_reset(this->ctx);
}

void
ztd::Checksum::update(std::string_view data)
{
    EVP_DigestUpdate(this->ctx, data.data(), data.size());
}

const std::string
ztd::Checksum::get_string() const
{
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    EVP_DigestFinal_ex(this->ctx, md_value, &md_len);

    return unsigned_char_to_hex_string(md_value, md_len);
}

const std::string
ztd::Checksum::compute_checksum(Type checksum_type, std::string_view str)
{
    EVP_DigestInit(this->ctx, HashTable.at(checksum_type)());
    this->update(str);
    return this->get_string();
}
