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

sh = find_program('sh')
sed = find_program('sed')
echo = find_program('echo')
python = find_program('python3')

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

test_flags = [
  # '-Weffc++',
  '-pedantic',
  '-pedantic-errors',
  # '-Wfatal-errors',
  # '-Waggregate-return',
  # '-Wcast-qual',
  '-Wchar-subscripts',
  '-Wcomment',
  # '-Wconversion',
  '-Wdisabled-optimization',
  '-Wdouble-promotion',
  '-Wfloat-equal',
  '-Wformat',
  '-Wformat=2',
  '-Wformat-nonliteral',
  '-Wformat-security',
  '-Wformat-y2k',
  '-Wimplicit-fallthrough',
  '-Wimport',
  # '-Wint-conversion',
  '-Winit-self',
  # '-Winline',
  # '-Wlong-long',
  # '-Wmissing-braces',
  '-Wmissing-field-initializers',
  '-Wmissing-format-attribute',
  '-Wmissing-include-dirs',
  '-Wmissing-noreturn',
  '-Wparentheses',
  '-Wpointer-arith',
  # '-Wredundant-decls',
  '-Wsequence-point',
  '-Wshadow',
  '-Wsign-compare',
  '-Wstack-protector',
  '-Wstrict-aliasing',
  '-Wstrict-aliasing=2',
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
  # '-Wstrict-overflow=5',
  '-Wstring-compare',
  '-Walloca',
  '-Wdate-time',

  # Disabled Warnings
  '-Wno-format-nonliteral',
  '-Wno-unused-parameter',

  # TODO - fix these warnings
  '-Wno-deprecated-declarations',

  # Sanitizer
  # '-fsanitize=undefined,address',
]

flags += cpp.get_supported_arguments(test_flags)

if cpp.has_multi_arguments('-Wformat', '-Werror=format-security')
    flags += '-Werror=format-security'
endif

# GCC only warning flags
if cpp.get_id() == 'gcc'
  test_flags_gcc = [
    '-Wno-system-headers',

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
    '-Wno-restrict',
    '-Wno-catch-value',
    '-Wno-cast-function-type',
    '-Wno-unused-macros',

    '-Wno-type-limits',
    '-Wno-strict-aliasing',
  ]

  flags += cpp.get_supported_arguments(test_flags_gcc)
endif

# Clang only warning flags
if cpp.get_id() == 'clang'
  test_flags_clang = [
    # Disabled Warnings
    '-Wno-unreachable-code-loop-increment',
    '-Wno-unused-macros',
  ]

  flags += cpp.get_supported_arguments(test_flags_clang)
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

fmt_dep = dependency('fmt', required : true)
spdlog_dep = dependency('spdlog', required : true)
openssl_dep = dependency('openssl', required : true)

dependencies = [
  spdlog_dep,
  fmt_dep,
  openssl_dep,
]

## Source files

sources = files(
  'src/logger/logger.cxx',

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
  sources,
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
libztd_dep = declare_dependency(include_directories : incdir, link_with : libztd)
