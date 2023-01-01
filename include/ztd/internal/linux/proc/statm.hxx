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

#pragma once

#include <string>
#include <string_view>

#include "../../types.hxx"

namespace ztd::proc
{
    class statm
    {
      public:
        statm();
        statm(pid_t pid);
        statm(const std::filesystem::path& path);

        /**
         *
         * proc/<PID>/statm entries
         *
         */

        [[nodiscard]] u64 size() const noexcept;
        [[nodiscard]] u64 resident() const noexcept;
        [[nodiscard]] u64 shared() const noexcept;
        [[nodiscard]] u64 text() const noexcept;
        [[nodiscard]] u64 lib() const noexcept;
        [[nodiscard]] u64 data() const noexcept;
        [[nodiscard]] u64 dt() const noexcept;

      private:
        void populate(const std::filesystem::path& path) noexcept;

        u64 m_size{};
        u64 m_resident{};
        u64 m_shared{};
        u64 m_text{};
        u64 m_lib{};
        u64 m_data{};
        u64 m_dt{};
    };
} // namespace ztd::proc
