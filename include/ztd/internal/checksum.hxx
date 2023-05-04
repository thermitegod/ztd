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

#include <openssl/evp.h>

#include "ztd/internal/types.hxx"

namespace ztd
{
    /**
     * Computes the checksum for data.
     * This is a generic API for computing checksums for a sequence of arbitrary bytes,
     * using various hashing algorithms like MD5, SHA-1 and SHA-256.
     */
    class Checksum
    {
      public:
        Checksum() = default;

        Checksum(const Checksum& other) = default;
        Checksum& operator=(const Checksum& other) = default;

        Checksum(Checksum&& other) noexcept = default;
        Checksum& operator=(Checksum&& other) noexcept = default;

        ~Checksum() noexcept;

        enum class Type
        {
            MD5,

            SHA1,
            SHA224,
            SHA256,
            SHA384,
            SHA512,

            SHA3_224,
            SHA3_256,
            SHA3_384,
            SHA3_512,

            BLAKE2S256,
            BLAKE2B512,
        };

        /**
         * Creates a new Checksum, using the checksum algorithm checksum_type.
         *
         * @param[in] checksum_type Checksum type, one of defined above.
         */
        explicit Checksum(Type checksum_type);

        /**
         * Resets the state of the checksum back to its initial state.
         */
        void reset();

        /**
         * Feeds data into an existing Checksum.
         *
         * @param[in] data Buffer used to compute the checksum
         */
        void update(const std::string_view data);

        /**
         * Gets the digest as a hexadecimal string.
         *
         * @return The hexadecimal representation of the checksum.
         */
        const std::string get_string() const;

        /**
         * Computes the checksum of a string.
         *
         * @param[in] checksum_type A Type
         * @param[in] str The string to compute the checksum of.
         *
         * @return The checksum as a hexadecimal string.
         */
        const std::string compute_checksum(Type checksum_type, const std::string_view str);

      private:
        EVP_MD_CTX* ctx{EVP_MD_CTX_new()};
    };
} // namespace ztd