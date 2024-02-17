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

#pragma once

// header order matters

#if !defined(ZTD_VERSION)
#warning ZTD_VERSION is not set, using version '1'
#define ZTD_VERSION 1 // Original API
#endif

#if (ZTD_VERSION > 2)
#error Current max API version is '2'
#endif

#include "./detail/types.hxx"

#include "./detail/checksum.hxx"
#include "./detail/filesize.hxx"
#include "./detail/fuse.hxx"
#include "./detail/map.hxx"
#include "./detail/random.hxx"
#include "./detail/smart_cache.hxx"
#include "./detail/string_base64.hxx"
#include "./detail/string_python.hxx"
#include "./detail/string_random.hxx"
#include "./detail/vector_templates.hxx"

#if (ZTD_VERSION == 1)
#include "./detail/deprecated/array_templates.hxx"
#include "./detail/deprecated/checksum.hxx" // implemented using ztd::checksum, need to include both
#include "./detail/deprecated/c_utils.hxx"
#include "./detail/deprecated/python_builtin.hxx"
#include "./detail/deprecated/string_utils.hxx"
#include "./detail/deprecated/timer.hxx" // old version of ztd::timer
#include "./detail/deprecated/vector_templates.hxx"
#else
#include "./detail/timer.hxx" // new version of ztd::timer
#endif

#if (ZTD_VERSION == 1)
#include "./detail/deprecated/shell/execute.hxx"
#include "./detail/deprecated/shell/utils.hxx"

#include "./detail/deprecated/sort/alphanumeric.hxx"
#include "./detail/deprecated/sort/compare.hxx"
#include "./detail/deprecated/sort/random.hxx"
#endif

#include "./detail/sys/group.hxx"
#include "./detail/sys/passwd.hxx"
#if (ZTD_VERSION == 1)
#include "./detail/deprecated/sys/chmod.hxx"
#include "./detail/deprecated/sys/chown.hxx"
#include "./detail/deprecated/sys/fnmatch.hxx"
#include "./detail/deprecated/sys/kill.hxx"
#include "./detail/deprecated/sys/stat.hxx" // old version of ztd::stat/lstat
#include "./detail/deprecated/sys/statx.hxx"
#include "./detail/deprecated/sys/statvfs.hxx"
#include "./detail/deprecated/sys/strdup.hxx"
#include "./detail/deprecated/sys/utime.hxx"
#else
#include "./detail/sys/stat.hxx" // new version of ztd::stat/lstat/statx
#include "./detail/sys/statvfs.hxx"
#endif

#if (ZTD_VERSION == 1)
#include "./detail/deprecated/linux/generic.hxx"
#endif
