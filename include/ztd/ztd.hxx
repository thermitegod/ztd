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

// header order matters

#if !defined(ZTD_VERSION)
#warning "ZTD_VERSION is not set, using version '1'"
#define ZTD_VERSION 1 // Original API
#endif

#if (ZTD_VERSION > 2)
#error "Current max API version is '2'"
#endif

#include "./internal/types.hxx"

#include "./internal/c_utils.hxx"
#include "./internal/checksum.hxx"
#include "./internal/filesize.hxx"
#include "./internal/fuse.hxx"
#include "./internal/random.hxx"
#include "./internal/smart_cache.hxx"
#include "./internal/string_base64.hxx"
#include "./internal/string_python.hxx"
#include "./internal/string_random.hxx"
#include "./internal/timer.hxx"

#include "./internal/vector_templates.hxx"

#include "./internal/shell/execute.hxx"
#include "./internal/shell/utils.hxx"

#include "./internal/sort/alphanumeric.hxx"
#include "./internal/sort/compare.hxx"
#include "./internal/sort/random.hxx"

#include "./internal/sys/chmod.hxx"
#include "./internal/sys/chown.hxx"
#include "./internal/sys/fnmatch.hxx"
#include "./internal/sys/group.hxx"
#include "./internal/sys/kill.hxx"
#include "./internal/sys/passwd.hxx"
#include "./internal/sys/stat.hxx"
#include "./internal/sys/statvfs.hxx"
#include "./internal/sys/statx.hxx"
#include "./internal/sys/strdup.hxx"
#include "./internal/sys/utime.hxx"

#include "./internal/linux/generic.hxx"

#if (ZTD_VERSION == 1)
#include "./internal/python_builtin.hxx"
#include "./internal/string_utils.hxx"

#include "./internal/array_templates.hxx"
#endif
