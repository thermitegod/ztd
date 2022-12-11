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
  meson_version : '>= 0.60.0'
)

result = [ 'Passed options:' ]

c = meson.get_compiler('c')
c_id = c.get_id()

cpp = meson.get_compiler('cpp')
cpp_id = cpp.get_id()

incdir = include_directories('include')

builddir = meson.current_build_dir()
sourcedir = meson.current_source_dir()
package = meson.project_name()
version = meson.project_version()
prefix = get_option('prefix')
libdir = join_paths(prefix, get_option('libdir'), package)

ldflags_add = []
cflags_add = []

ldflags_opt = []
cflags_opt = []

cflags_opt += [
  # enabled by warning_level=3
  #[ '-Wall' ],
  #[ '-Wextra' ],
  #[ '-Werror' ],

  # Not enabled by Wall
  [ '-pedantic' ],
  [ '-pedantic-errors' ],
  [ '-Wcast-qual' ],
  [ '-Wchar-subscripts' ],
  [ '-Wcomment' ],
  [ '-Wconversion' ],
  [ '-Wdisabled-optimization' ],
  [ '-Wdouble-promotion' ],
  [ '-Wfloat-equal' ],
  [ '-Wformat' ],
  [ '-Wformat=2' ],
  [ '-Wformat-nonliteral' ],
  [ '-Wformat-security' ],
  [ '-Wformat-y2k' ],
  [ '-Wimplicit-fallthrough' ],
  [ '-Wimport' ],
  [ '-Winit-self' ],
  [ '-Wmissing-field-initializers' ],
  [ '-Wmissing-format-attribute' ],
  [ '-Wmissing-include-dirs' ],
  [ '-Wmissing-noreturn' ],
  [ '-Wparentheses' ],
  [ '-Wpointer-arith' ],
  [ '-Wsequence-point' ],
  [ '-Wshadow' ],
  [ '-Wsign-compare' ],
  [ '-Wstack-protector' ],
  [ '-Wstrict-aliasing' ],
  [ '-Wstrict-aliasing=2' ],
  [ '-Wswitch' ],
  [ '-Wswitch-default' ],
  [ '-Wswitch-enum' ],
  [ '-Wtrigraphs' ],
  [ '-Wundef' ],
  [ '-Wuninitialized' ],
  [ '-Wunknown-pragmas' ],
  [ '-Wunreachable-code' ],
  [ '-Wunused' ],
  [ '-Wunused-function' ],
  [ '-Wunused-label' ],
  [ '-Wunused-parameter' ],
  [ '-Wunused-value' ],
  [ '-Wunused-result' ],
  [ '-Wunused-variable' ],
  [ '-Wunused-macros' ],
  [ '-Wvariadic-macros' ],
  [ '-Wvla' ],
  [ '-Wwrite-strings' ],
  [ '-Wignored-qualifiers' ],
  [ '-Wstrict-overflow=5' ],
  [ '-Wstring-compare' ],
  [ '-Walloca' ],
  [ '-Wdate-time' ],

  # TODO - fix
  [ '-Wno-implicit-int-conversion' ],
  [ '-Wno-shorten-64-to-32' ],
  [ '-Wno-sign-conversion' ],
]

# GCC/Clang only warning flags
if cpp_id == 'gcc'
  cflags_opt+=[
    [ '-Wno-system-headers' ],

    [ '-Wformat-overflow=2' ],
    [ '-Wformat-truncation' ],
    [ '-Warray-bounds=2' ],
    [ '-Warray-compare' ],
    [ '-Wzero-length-bounds' ],
    [ '-Wattribute-alias=2' ],
    [ '-Wduplicated-branches' ],
    [ '-Wduplicated-cond' ],
    [ '-Wtrampolines' ],
    [ '-Walloc-zero' ],
    [ '-Wstringop-overflow=4' ],

    # Disabled Warnings
    [ '-Wno-restrict' ],
    [ '-Wno-catch-value' ],
    [ '-Wno-cast-function-type' ],
    [ '-Wno-unused-macros' ],

    [ '-Wno-type-limits' ],
    [ '-Wno-strict-aliasing' ],
  ]
elif cpp_id == 'clang'
  cflags_opt+=[
    # Disabled Warnings
    [ '-Wno-unused-macros' ],
  ]
endif

ldflags_opt += [
  [ '-Wl,-O2' ],
  [ '-Wl,--as-needed' ],
]

if not meson.is_subproject()
  add_global_arguments(cflags_opt, language: ['c', 'cpp'])
  add_global_link_arguments(ldflags_opt, language: ['c', 'cpp'])
endif

dep_fmt = dependency('fmt', required : true)
dep_spdlog = dependency('spdlog', required : true)

sources = [
  'src/files/filesize_SI.cxx',
  'src/files/filesize_IEC.cxx',

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

  'src/c_utils.cxx',
  'src/program.cxx',
  'src/string_python.cxx',
  'src/string_random.cxx',
  'src/string_utils.cxx',
  'src/timer.cxx',
]

target_name = 'ztd'

if meson.is_subproject()
  target_type = 'static_library'
else
  target_type = 'shared_library'
endif

libztd = build_target(
  target_name,
  sources,
  target_type: target_type,
  soversion : '1.0.0',
  include_directories: incdir,
  install : true,
  #install_dir : libdir,
  dependencies: [
    dep_fmt,
    dep_spdlog,
  ],
)

# pkgconfig
if not meson.is_subproject()
  pkg = import('pkgconfig')
  pkg.generate(libztd)
endif

# install headers
install_subdir('include/ztd', install_dir : prefix + '/include')

# meson subproject
libztd_dep = declare_dependency(include_directories : incdir, link_with : libztd)
