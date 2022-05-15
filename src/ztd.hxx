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

#define ZTD_MAIN_HEADER

// header order matters - Main
#include "impl/string.hxx"
#include "impl/string-random.hxx"
#include "impl/c-interface.hxx"
#include "impl/array-templates.hxx"
#include "impl/vector-templates.hxx"
#include "impl/timer.hxx"

#undef ZTD_MAIN_HEADER
