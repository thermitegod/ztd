/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
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

// header order matters
#include "ztd-string.hxx"
#include "ztd-filesystem.hxx" // depends on ztd-string.hxx
#include "ztd-lazy.hxx"
#include "ztd-c-interface.hxx"
#include "ztd-vector.hxx"
#include "ztd-vector-templates.hxx"
#include "ztd-timer.hxx"

#undef ZTD_MAIN_HEADER
