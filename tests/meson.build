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

cross = meson.is_cross_build()
sh = find_program('sh')

builddir = meson.current_build_dir()
sourcedir = meson.current_source_dir()
package = meson.project_name()
version = meson.project_version()

ldflags_add = []
cflags_add = []

ldflags_opt = []
cflags_opt = []

cflags_opt += [
  [ '-ggdb' ],

  # enabled by warning_level=3
  #[ '-Wall' ],
  #[ '-Wextra' ],
  #[ '-Werror' ],

  # Not enabled by Wall
  #[ '-Weffc++' ],
  [ '-pedantic' ],
  [ '-pedantic-errors' ],
  # [ '-Wfatal-errors' ],
  #[ '-Waggregate-return' ],
  #[ '-Wcast-qual' ],
  [ '-Wchar-subscripts' ],
  [ '-Wcomment' ],
  #[ '-Wconversion' ],
  [ '-Wdisabled-optimization' ],
  #[ '-Wdouble-promotion' ],
  [ '-Wfloat-equal' ],
  [ '-Wformat' ],
  [ '-Wformat=2' ],
  [ '-Wformat-nonliteral' ],
  [ '-Wformat-security' ],
  [ '-Wformat-y2k' ],
  [ '-Wimplicit-fallthrough' ],
  [ '-Wimport' ],
  #[ '-Wint-conversion' ],
  [ '-Winit-self' ],
  #[ '-Winline' ],
  #[ '-Wlong-long' ],
  #[ '-Wmissing-braces' ],
  [ '-Wmissing-field-initializers' ],
  [ '-Wmissing-format-attribute' ],
  [ '-Wmissing-include-dirs' ],
  [ '-Wmissing-noreturn' ],
  [ '-Wparentheses' ],
  [ '-Wpointer-arith' ],
  #[ '-Wredundant-decls' ],
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
  #[ '-Wstrict-overflow=5' ],
  [ '-Wstring-compare' ],
  [ '-Walloca' ],
  [ '-Wdate-time' ],

  # Disabled Warnings
  [ '-Wno-format-nonliteral' ],
  [ '-Wno-unused-parameter' ],

  # TODO - fix these warnings
  [ '-Wno-deprecated-declarations' ],

  # Sanitizer
  #[ '-fsanitize=undefined,address' ],
]

# GCC/Clang only warning flags
if cpp_id == 'gcc'
  cflags_opt+=[
    [ '-Wno-system-headers' ],

    [ '-Wformat-overflow=2' ],
    [ '-Wformat-truncation' ],
    #[ '-Wsuggest-attribute=pure' ],
    #[ '-Wsuggest-attribute=const' ],
    #[ '-Wsuggest-attribute=noreturn' ],
    #[ '-Wsuggest-attribute=malloc' ],
    #[ '-Wsuggest-attribute=format' ],
    #[ '-Wsuggest-attribute=cold' ],
    #[ '-Wmissing-format-attribute' ],
    [ '-Warray-bounds=2' ],
    [ '-Warray-compare' ],
    [ '-Wzero-length-bounds' ],
    [ '-Wattribute-alias=2' ],
    [ '-Wduplicated-branches' ],
    [ '-Wduplicated-cond' ],
    [ '-Wtrampolines' ],
    [ '-Walloc-zero' ],
    [ '-Wstringop-overflow=4' ],
    #[ '-Wno-type-limits' ],
    #[ '-Wno-strict-aliasing' ],
  ]
elif cpp_id == 'clang'
  cflags_opt+=[
    # Disabled Warnings
    #[ '-Wno-unreachable-code-loop-increment' ],
    #[ '-Wno-unused-macros' ],
  ]
endif

ldflags_opt += [
  [ '-Wl,-O2' ],
  [ '-Wl,--as-needed' ],
]

add_global_arguments(cflags_opt, language: ['c', 'cpp'])
add_global_link_arguments(ldflags_opt, language: ['c', 'cpp'])

dep_gtest = dependency('gtest')

dep_fmt = dependency('fmt')
dep_spdlog = dependency('spdlog')

sources = [
  'src/main.cxx',

  'src/base/test-array-templates.cxx',
  'src/base/test-c-interface.cxx',
  'src/base/test-string-python.cxx',
  'src/base/test-string-random.cxx',
  'src/base/test-string-utils.cxx',
  'src/base/test-timer.cxx',
  'src/base/test-vector-templates.cxx',

  # ENV
  'src/env/test-env.cxx',

  # FILES
  'src/files/test-filesize-IEC.cxx',
  'src/files/test-filesize-SI.cxx',

  # LOGGER
  'src/logger/test-logger.cxx',

  # SHELL
  'src/shell/test-execute.cxx',
  'src/shell/test-utils.cxx',
]

target_name = 'test_suite'
target_type = 'executable'

test_suite = build_target(
  target_name,
  sources,
  target_type: target_type,
  install : false,
  dependencies: [
    dep_gtest,

    dep_fmt,
    dep_spdlog,
  ],
  cpp_pch: 'pch/cxx_pch.hxx',
)
