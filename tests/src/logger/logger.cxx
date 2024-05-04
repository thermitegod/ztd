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

#include <string>

#include <format>

#include <memory>

#include "ztd/ztd.hxx"
#include "ztd/ztd_logger.hxx"

struct A
{
    int a;
};

int
main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    ztd::logger::initialize();
    // ztd::logger::initialize(spdlog::level::trace, "/tmp/test.log");

    const std::string msg1 = "test string";
    const std::string msg2 = "format test string";

    // info
    ztd::logger::info(msg1);
    ztd::logger::info("{}", msg2);

    // warn
    ztd::logger::warn(msg1);
    ztd::logger::warn("{}", msg2);

    // error
    ztd::logger::error(msg1);
    ztd::logger::error("{}", msg2);

    // critical
    ztd::logger::critical(msg1);
    ztd::logger::critical("{}", msg2);

    // debug
    ztd::logger::debug(msg1);
    ztd::logger::debug("{}", msg2);

    // trace
    ztd::logger::trace(msg1);
    ztd::logger::trace("{}", msg2);

    // pointers
    ztd::logger::info("==========================");

    A* raw_a = new A(1);
    std::shared_ptr<A> shared_a = std::make_shared<A>(1);
    std::unique_ptr<A> unique_a = std::make_unique<A>(1);

    ztd::logger::info("raw pointer:    {}", ztd::logger::utils::ptr(raw_a));
    ztd::logger::info("shared pointer: {}", ztd::logger::utils::ptr(shared_a));
    ztd::logger::info("unique pointer: {}", ztd::logger::utils::ptr(unique_a));

    delete raw_a;
}
