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

namespace ztd
{
    class Execute
    {
      public:
        Execute() = delete;
        Execute(std::string_view command);
        ~Execute();

        [[nodiscard]] int exit_status() const noexcept;

        [[nodiscard]] const std::string standard_input() const noexcept;
        [[nodiscard]] const std::string standard_output() const noexcept;
        [[nodiscard]] const std::string standard_error() const noexcept;

      private:
        int status{0};

        std::string in{};  // standard input
        std::string out{}; // standard output
        std::string err{}; // standard error

        std::array<i32, 2> infd{0, 0};
        std::array<i32, 2> outfd{0, 0};
        std::array<i32, 2> errfd{0, 0};
    };
} // namespace ztd
