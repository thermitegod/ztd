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

// header order matters

#include "./internal/types.hxx"

#include "./internal/string-python.hxx"
#include "./internal/string-random.hxx"
#include "./internal/string-utils.hxx"

#include "./internal/c-interface.hxx"

#include "./internal/array-templates.hxx"
#include "./internal/vector-templates.hxx"

#include "./internal/timer.hxx"

#include "./internal/files/filesize-IEC.hxx"
#include "./internal/files/filesize-SI.hxx"

#include "./internal/sys/chmod.hxx"
#include "./internal/sys/chown.hxx"
#include "./internal/sys/utime.hxx"
#include "./internal/sys/fnmatch.hxx"
#include "./internal/sys/stat.hxx"
#include "./internal/sys/statvfs.hxx"
