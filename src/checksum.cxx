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

#include <openssl/evp.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/checksum.hxx"

using openssl_hash_function_ptr = const EVP_MD* (*)();

static constexpr std::array<openssl_hash_function_ptr, 12> function_ptr_table{
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

ztd::checksum::~checksum() noexcept
{
    EVP_MD_CTX_free(this->ctx);
}

ztd::checksum::checksum(type checksum_type)
{
    EVP_DigestInit(this->ctx, function_ptr_table[static_cast<i32>(checksum_type)]());
}

void
ztd::checksum::reset() const noexcept
{
    EVP_MD_CTX_reset(this->ctx);
}

void
ztd::checksum::update(const std::string_view data) const noexcept
{
    EVP_DigestUpdate(this->ctx, data.data(), data.size());
}

const std::string
ztd::checksum::get_string() const noexcept
{
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    EVP_DigestFinal_ex(this->ctx, md_value, &md_len);

    char* hex_str = OPENSSL_buf2hexstr(md_value, md_len);
    std::string result(hex_str);
    OPENSSL_free(hex_str);
    return result;
}

const std::string
ztd::checksum::compute_checksum(type checksum_type, const std::string_view str) const noexcept
{
    EVP_DigestInit(this->ctx, function_ptr_table[static_cast<i32>(checksum_type)]());
    this->update(str);
    return this->get_string();
}

const std::string
ztd::compute_checksum(checksum::type type, const std::string_view str) noexcept
{
    const auto check = ztd::checksum();
    return check.compute_checksum(type, str);
}
