project(
  'test_suite', ['c', 'cpp'],
  version : '1.0.0',
  license : 'GPL3',
  default_options : [
    'cpp_std=c++23',
    'warning_level=3',
    'optimization=2',
  ],
  meson_version : '>= 1.0.0'
)

build_root = meson.project_build_root()
source_root = meson.project_source_root()

incdir = include_directories(['../include', 'src'])

package = meson.project_name()
version = meson.project_version()

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

  '-fno-omit-frame-pointer',
  '-mno-omit-leaf-frame-pointer',

  '-fasynchronous-unwind-tables',

  # '-Wfatal-errors',
  # '-ftime-trace',
  # '-fsave-optimization-record',
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

  # Disabled Warnings
  '-Wno-double-promotion',

  # Ignore deprecation warnings
  '-Wno-deprecated-declarations',
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

add_global_arguments(flags, language: ['c', 'cpp'])
add_global_link_arguments(link_flags, language: ['c', 'cpp'])

## dependencies

# ztd subproject
ztd_proj = subproject('ztd')
ztd_dep = ztd_proj.get_variable('ztd_dep')

gtest_dep = dependency('gtest')

spdlog_dep = dependency('spdlog', required : true)

dependencies = [
  gtest_dep,
  spdlog_dep,
  ztd_dep,
]

## preprocessor

preprocessor = [
  '-DZTD_VERSION=3',
  '-DTEST_DATA_PATH="@0@"'.format(join_paths(meson.current_source_dir(), 'test_data')),
]

if get_option('buildtype') == 'debug'
  preprocessor += '-D_GLIBCXX_DEBUG'
endif

foreach a : preprocessor
  add_project_arguments(a, language : ['c', 'cpp'])
endforeach

## Source files

sources = files(
  'src/main.cxx',
  'src/utils.cxx',

  # BASE
  'src/base/test_checksum.cxx',
  'src/base/test_filesize.cxx',
  'src/base/test_fuse.cxx',
  'src/base/test_map.cxx',
  'src/base/test_random.cxx',
  'src/base/test_smart_cache.cxx',
  'src/base/test_string_base64.cxx',
  'src/base/test_string_python.cxx',
  'src/base/test_string_random.cxx',
  'src/base/test_timer.cxx',
  'src/base/test_types.cxx',
  'src/base/test_vector_templates.cxx',

  # SYS
  'src/sys/test_group.cxx',
  'src/sys/test_passwd.cxx',
  # 'src/sys/test_stat.cxx',
)

## Build

# Main Test Suite

test_suite = build_target(
  'test_suite',
  sources: sources,
  target_type: 'executable',
  include_directories: incdir,
  install : false,
  dependencies: dependencies,
)

test('ZTD Test Suite', test_suite)

# Logger Test Suite

sources = files(
  'src/logger/logger.cxx',
)

test_suite = build_target(
  'test_suite_logger',
  sources: sources,
  target_type: 'executable',
  include_directories: incdir,
  install : false,
  dependencies: dependencies,
)
