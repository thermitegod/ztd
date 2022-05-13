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

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include "../../../src/ztd.hxx"
#include "../../../src/ztd-shell.hxx"

TEST_CASE("::Execute ls stdout")
{
    const std::string command = "ls -d /tmp";

    ztd::Execute cmd(command);

    INFO(cmd.standard_output);
    INFO(cmd.standard_error);

    REQUIRE(ztd::same(ztd::trim(cmd.standard_output), "/tmp"));

    REQUIRE(ztd::same(ztd::trim(cmd.standard_error), ""));
}

TEST_CASE("::Execute ls stderr")
{
    const std::string command = "ls does_not_exist";

    ztd::Execute cmd(command);

    INFO(cmd.standard_output);
    INFO(cmd.standard_error);

    REQUIRE(ztd::same(ztd::trim(cmd.standard_output), ""));

    REQUIRE(ztd::same(ztd::trim(cmd.standard_error),
                      "ls: cannot access 'does_not_exist': No such file or directory"));
}
