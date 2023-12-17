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
#warning ZTD_VERSION is not set, using version '1'
#define ZTD_VERSION 1 // Original API
#endif

#if (ZTD_VERSION > 2)
#error Current max API version is '2'
#endif

#include "./impl/types.hxx"

#include "./impl/checksum.hxx"
#include "./impl/filesize.hxx"
#include "./impl/fuse.hxx"
#include "./impl/random.hxx"
#include "./impl/smart_cache.hxx"
#include "./impl/string_base64.hxx"
#include "./impl/string_python.hxx"
#include "./impl/string_random.hxx"
#include "./impl/vector_templates.hxx"

#if (ZTD_VERSION == 1)
#include "./impl/deprecated/array_templates.hxx"
#include "./impl/deprecated/checksum.hxx" // implemented using ztd::checksum, need to include both
#include "./impl/deprecated/c_utils.hxx"
#include "./impl/deprecated/python_builtin.hxx"
#include "./impl/deprecated/string_utils.hxx"
#include "./impl/deprecated/timer.hxx" // old version of ztd::timer
#include "./impl/deprecated/vector_templates.hxx"
#else
#include "./impl/timer.hxx" // new version of ztd::timer
#endif

#include "./impl/shell/execute.hxx"
#include "./impl/shell/utils.hxx"

#include "./impl/sort/alphanumeric.hxx"
#include "./impl/sort/compare.hxx"
#include "./impl/sort/random.hxx"

#include "./impl/sys/chmod.hxx"
#include "./impl/sys/chown.hxx"
#include "./impl/sys/fnmatch.hxx"
#include "./impl/sys/group.hxx"
#include "./impl/sys/kill.hxx"
#include "./impl/sys/passwd.hxx"
#if (ZTD_VERSION == 1)
#include "./impl/deprecated/sys/stat.hxx" // old version of ztd::stat/lstat
#else
#include "./impl/sys/stat.hxx" // new version of ztd::stat/lstat
#endif
#include "./impl/sys/statvfs.hxx"
#include "./impl/sys/statx.hxx"
#include "./impl/sys/strdup.hxx"
#include "./impl/sys/utime.hxx"

#include "./impl/linux/generic.hxx"
