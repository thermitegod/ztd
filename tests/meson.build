project(
  'test_suite', ['c', 'cpp'],
  version : '1.0.0',
  license : 'GPL3',
  default_options : [
    'cpp_std=c++20',
    'warning_level=3',
    'optimization=2',
  ],
  meson_version : '>= 0.60.0'
)

result = [ 'Passed options:' ]

c = meson.get_compiler('c')
c_id = c.get_id()

cpp = meson.get_compiler('cpp')
cpp_id = cpp.get_id()

incdir = include_directories('../include')

builddir = meson.current_build_dir()
sourcedir = meson.current_source_dir()
package = meson.project_name()
version = meson.project_version()

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
  [ '-Wno-double-promotion' ], # remove test?
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

add_global_arguments(cflags_opt, language: ['c', 'cpp'])
add_global_link_arguments(ldflags_opt, language: ['c', 'cpp'])

gtest_dep = dependency('gtest')

fmt_dep = dependency('fmt')
spdlog_dep = dependency('spdlog')

# libztd subproject
libztd_proj = subproject('libztd')
libztd_dep = libztd_proj.get_variable('libztd_dep')

# Test Suite

sources = [
  'src/main.cxx',

  'src/base/test_array_templates.cxx',
  'src/base/test_c_utils.cxx',
  'src/base/test_program.cxx',
  'src/base/test_python_builtin.cxx',
  'src/base/test_string_python.cxx',
  'src/base/test_string_random.cxx',
  'src/base/test_string_utils.cxx',
  'src/base/test_timer.cxx',
  'src/base/test_vector_templates.cxx',

  # FILES
  'src/files/test_filesize_IEC.cxx',
  'src/files/test_filesize_SI.cxx',

  # LOGGER
  'src/logger/test_logger.cxx',

  # SHELL
  'src/shell/test_execute.cxx',
  'src/shell/test_utils.cxx',

  # SORT
  'src/sort/test_alphanumeric.cxx',
  'src/sort/test_compare.cxx',
  'src/sort/test_random.cxx',

  # SYS
  'src/sys/test_strdup.cxx',
]

target_name = 'test_suite'
target_type = 'executable'

test_suite = build_target(
  target_name,
  sources,
  target_type: target_type,
  include_directories: incdir,
  install : false,
  # link_with : libztd,
  dependencies: [
    gtest_dep,

    libztd_dep,

    fmt_dep,
    spdlog_dep,
  ],
  cpp_pch: 'pch/cxx_pch.hxx',
)

test('ZTD Test Suite', test_suite)
