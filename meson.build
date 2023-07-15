project(
  'libztd', ['c', 'cpp'],
  version : '1.0.0',
  license : 'GPL3',
  default_options : [
    'cpp_std=c++20',
    'warning_level=3',
    'optimization=2',
    'prefix=/usr',
    'sysconfdir=/etc',
  ],
  meson_version : '>= 1.0.0'
)

build_root = meson.project_build_root()
source_root = meson.project_source_root()

incdir = include_directories('include')

package = meson.project_name()
version = meson.project_version()
prefix = get_option('prefix')
libdir = join_paths(prefix, get_option('libdir'), package)

## compiler stuff

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

# message(cc.get_id())
# message(cpp.get_id())

flags = []
link_flags = []

debug_flags = [
    '-ggdb3',

    '-pedantic',
    '-pedantic-errors',
    # '-Wfatal-errors',
]

if get_option('buildtype') == 'debug'
    flags += cpp.get_supported_arguments(debug_flags)
endif

release_flags = []

if get_option('buildtype') == 'release'
    flags += cpp.get_supported_arguments(release_flags)
endif

default_warning_flags = [
    '-Wchar-subscripts',
    '-Wcomment',
    '-Wdisabled-optimization',
    '-Wdouble-promotion',
    '-Wfloat-equal',
    '-Wformat=2',
    '-Wimplicit-fallthrough',
    '-Wimport',
    '-Winit-self',
    '-Wmissing-field-initializers',
    '-Wmissing-format-attribute',
    '-Wmissing-include-dirs',
    '-Wmissing-noreturn',
    '-Wparentheses',
    '-Wpointer-arith',
    '-Wsequence-point',
    '-Wshadow',
    '-Wsign-compare',
    '-Wstack-protector',
    '-Wstrict-aliasing',
    '-Wswitch',
    '-Wswitch-default',
    '-Wswitch-enum',
    '-Wtrigraphs',
    '-Wundef',
    '-Wuninitialized',
    '-Wunknown-pragmas',
    '-Wunreachable-code',
    '-Wunused',
    '-Wunused-function',
    '-Wunused-label',
    '-Wunused-parameter',
    '-Wunused-value',
    '-Wunused-result',
    '-Wunused-variable',
    '-Wunused-macros',
    '-Wvariadic-macros',
    '-Wvla',
    '-Wwrite-strings',
    '-Wignored-qualifiers',
    '-Wstring-compare',
    '-Walloca',
    '-Wdate-time',

    # Sanitizer
    # '-fsanitize=undefined,address',

    # Disabled Warnings
]

flags += cpp.get_supported_arguments(default_warning_flags)

if cpp.has_multi_arguments('-Wformat', '-Werror=format-security')
    flags += '-Werror=format-security'
endif

# GCC only warning flags
if cpp.get_id() == 'gcc'
    default_warning_flags_gcc = [
        '-Wformat-overflow=2',
        '-Wformat-truncation',
        '-Warray-bounds=2',
        '-Warray-compare',
        '-Wzero-length-bounds',
        '-Wattribute-alias=2',
        '-Wduplicated-branches',
        '-Wduplicated-cond',
        '-Wtrampolines',
        '-Walloc-zero',
        '-Wstringop-overflow=4',

        # Disabled Warnings
    ]

    flags += cpp.get_supported_arguments(default_warning_flags_gcc)
endif

# Clang only warning flags
if cpp.get_id() == 'clang'
    default_warning_flags_clang = [
        # Disabled Warnings
    ]

    flags += cpp.get_supported_arguments(default_warning_flags_clang)
endif

if cpp.has_link_argument('-Wl,--as-needed')
    link_flags += '-Wl,--as-needed'
endif

noexecstack = false
if cpp.has_link_argument('-Wl,-z,noexecstack')
    link_flags += '-Wl,-z,noexecstack'
    noexecstack = true
endif

if not meson.is_subproject()
  add_global_arguments(flags, language: ['c', 'cpp'])
  add_global_link_arguments(link_flags, language: ['c', 'cpp'])
endif

## dependencies

# fmt_dep = dependency('fmt', required : true)
# spdlog_dep = dependency('spdlog', required : true)
openssl_dep = dependency('openssl', required : true)

dependencies = [
  # spdlog_dep,
  # fmt_dep,
  openssl_dep,
]

## Source files

sources = files(
  'src/shell/execute.cxx',
  'src/shell/utils.cxx',

  'src/sort/alphanumeric.cxx',
  'src/sort/compare.cxx',
  'src/sort/random.cxx',

  'src/sys/chmod.cxx',
  'src/sys/chown.cxx',
  'src/sys/fnmatch.cxx',
  'src/sys/group.cxx',
  'src/sys/kill.cxx',
  'src/sys/passwd.cxx',
  'src/sys/stat.cxx',
  'src/sys/statvfs.cxx',
  'src/sys/strdup.cxx',
  'src/sys/utime.cxx',

  'src/linux/generic.cxx',

  'src/c_utils.cxx',
  'src/checksum.cxx',
  'src/filesize.cxx',
  'src/python_builtin.cxx',
  'src/random.cxx',
  'src/string_base64.cxx',
  'src/string_python.cxx',
  'src/string_random.cxx',
  'src/string_utils.cxx',
  'src/timer.cxx',
)

## subproject
if meson.is_subproject()
  target_type = 'static_library'
else
  target_type = 'shared_library'
endif

## build
target_name = 'ztd'

libztd = build_target(
  target_name,
  sources: sources,
  target_type: target_type,
  soversion : '1.0.0',
  include_directories: incdir,
  install : true,
  #install_dir : libdir,
  dependencies: dependencies,
)

## pkgconfig
if not meson.is_subproject()
  pkg = import('pkgconfig')
  pkg.generate(libztd)
endif

## install headers
install_subdir('include/ztd', install_dir : prefix + '/include')

## meson subproject
ztd_dep = declare_dependency(include_directories : incdir, link_with : libztd)
