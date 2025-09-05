build_root = meson.project_build_root()
source_root = meson.project_source_root()

incdir = include_directories('src')

## compiler stuff

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

# message(cc.get_id())
# message(cpp.get_id())

flags = []

if get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized'
    flags += cpp.get_supported_arguments([
        '-ggdb3',
        '-pedantic',
        '-pedantic-errors',
        '-fno-omit-frame-pointer',
        '-mno-omit-leaf-frame-pointer',
        '-fasynchronous-unwind-tables',
        # '-ftime-trace',
        # '-fsave-optimization-record',

        # '-Werror',
        '-Wfatal-errors',
    ])
endif

if get_option('buildtype') == 'release'
    flags += cpp.get_supported_arguments([])
endif

# Default
flags += cpp.get_supported_arguments([
    '-fexceptions',

    '-finput-charset=UTF-8',
    '-fexec-charset=UTF-8',

    '-fno-delete-null-pointer-checks',
    '-fno-strict-aliasing',
    '-fno-strict-overflow',

    '-ftrivial-auto-var-init=zero',
    '-fzero-init-padding-bits=all',
])

# Hardening
flags += cpp.get_supported_arguments([
    '-Wformat=2',
    '-Wformat-overflow=2',
    '-Wformat-truncation',
    '-Werror=format-security',

    '-fstack-protector-strong',
    '-fstack-clash-protection',
    '-fcf-protection=full',

    '-Wp,-U_FORTIFY_SOURCE,-D_FORTIFY_SOURCE=3',

    # GCC libstdc++
    # '-Wp,-D_GLIBCXX_DEBUG',
    '-Wp,-D_GLIBCXX_ASSERTIONS',

    # LLVM libc++
    # '-Wp,-D_LIBCPP_ASSERT',
    # '-Wp,-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST',
])

# Warnings
flags += cpp.get_supported_arguments([
    '-Walloca',
    '-Walloc-zero',
    '-Warray-bounds=2',
    '-Warray-compare',
    '-Wattribute-alias=2',
    '-Wbidi-chars=any',
    '-Wcast-align',
    '-Wcast-qual',
    '-Wchar-subscripts',
    '-Wcomment',
    '-Wconversion',
    '-Wdate-time',
    '-Wdisabled-optimization',
    '-Wdouble-promotion',
    '-Wduplicated-branches',
    '-Wduplicated-cond',
    '-Wextra-semi',
    '-Wfloat-equal',
    '-Wignored-qualifiers',
    '-Wimplicit-fallthrough',
    '-Wimport',
    '-Winit-self',
    '-Wint-conversion',
    '-Wmissing-field-initializers',
    '-Wmissing-format-attribute',
    '-Wmissing-include-dirs',
    '-Wmissing-noreturn',
    '-Wnon-virtual-dtor',
    '-Wnull-dereference',
    '-Wold-style-cast',
    '-Woverloaded-virtual',
    '-Wparentheses',
    '-Wpointer-arith',
    '-Wsequence-point',
    '-Wshadow',
    '-Wsign-compare',
    '-Wsign-conversion',
    '-Wstack-protector',
    '-Wstrict-aliasing',
    '-Wstring-compare',
    '-Wstringop-overflow=4',
    '-Wswitch',
    '-Wswitch-enum',
    '-Wtrampolines',
    '-Wtrigraphs',
    '-Wundef',
    '-Wuninitialized',
    '-Wunknown-pragmas',
    '-Wunreachable-code',
    '-Wunused',
    '-Wunused-function',
    '-Wunused-label',
    '-Wunused-macros',
    '-Wunused-parameter',
    '-Wunused-result',
    '-Wunused-value',
    '-Wunused-variable',
    '-Wvariadic-macros',
    '-Wvla',
    '-Wwrite-strings',
    '-Wzero-length-bounds',
])

# Disabled Warnings
flags += cpp.get_supported_arguments([])

# Disabled GCC Warnings
if cpp.get_id() == 'gcc'
    flags += cpp.get_supported_arguments([])
endif

# Disabled Clang Warnings
if cpp.get_id() == 'clang'
    flags += cpp.get_supported_arguments([])
endif

# Linker

link_flags = []
link_flags += cpp.get_supported_link_arguments([
    '-Wl,-O1',
    '-Wl,--as-needed',
    '-Wl,--sort-common',
    '-Wl,-z,relro',
    '-Wl,-z,now',
    '-Wl,-z,pack-relative-relocs',
    '-Wl,-z,noexecstack',
    '-Wl,-z,defs',
])

add_global_arguments(flags, language: ['c', 'cpp'])
add_global_link_arguments(link_flags, language: ['c', 'cpp'])

## dependencies

doctest_dep = dependency('doctest', required : true)

## preprocessor

preprocessor = [
    '-DZTD_TEST_SUITE',
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
  'src/base/test_fuse.cxx',
  'src/base/test_map.cxx',
  'src/base/test_random.cxx',
  'src/base/test_smart_cache.cxx',
  'src/base/test_string_random.cxx',
  'src/base/test_timer.cxx',
  'src/base/test_types.cxx',
  'src/base/test_utils.cxx',
  'src/base/test_vector_templates.cxx',

  # Python like
  'src/base/string_python/capitalize.cxx',
  'src/base/string_python/center.cxx',
  'src/base/string_python/count.cxx',
  'src/base/string_python/expandtabs.cxx',
  'src/base/string_python/isalnum.cxx',
  'src/base/string_python/isalpha.cxx',
  'src/base/string_python/isascii.cxx',
  'src/base/string_python/isdecimal.cxx',
  'src/base/string_python/isdigit.cxx',
  'src/base/string_python/islower.cxx',
  'src/base/string_python/isnumeric.cxx',
  'src/base/string_python/isspace.cxx',
  'src/base/string_python/istitle.cxx',
  'src/base/string_python/isupper.cxx',
  'src/base/string_python/join.cxx',
  'src/base/string_python/lower.cxx',
  'src/base/string_python/partition.cxx',
  'src/base/string_python/removeprefix.cxx',
  'src/base/string_python/removesuffix.cxx',
  'src/base/string_python/replace.cxx',
  'src/base/string_python/rpartition.cxx',
  'src/base/string_python/rsplit.cxx',
  'src/base/string_python/split.cxx',
  'src/base/string_python/splitlines.cxx',
  'src/base/string_python/strip.cxx',
  'src/base/string_python/swapcase.cxx',
  'src/base/string_python/title.cxx',
  'src/base/string_python/upper.cxx',
  'src/base/string_python/zfill.cxx',

  # BYTE IEC
  'src/byte/iec/arithmetic.cxx',
  'src/byte/iec/assignment.cxx',
  'src/byte/iec/comparison.cxx',
  'src/byte/iec/constructor.cxx',
  'src/byte/iec/functions.cxx',
  'src/byte/iec/literals.cxx',

  # BYTE SI
  'src/byte/si/arithmetic.cxx',
  'src/byte/si/assignment.cxx',
  'src/byte/si/comparison.cxx',
  'src/byte/si/constructor.cxx',
  'src/byte/si/functions.cxx',
  'src/byte/si/literals.cxx',

  # SYS
  'src/sys/test_group.cxx',
  'src/sys/test_passwd.cxx',
  'src/sys/test_stat.cxx',

  # TYPES

  'src/types/concepts.cxx',
  'src/types/custom.cxx',

  'src/types/extra/glaze.cxx',

  # 'src/types/floating/arithmetic.cxx',
  # 'src/types/floating/assignment.cxx',
  # 'src/types/floating/comparison.cxx',
  # 'src/types/floating/constants.cxx',
  # 'src/types/floating/constructor.cxx',
  # 'src/types/floating/functions.cxx',

  'src/types/integer_signed/arithmetic.cxx',
  'src/types/integer_signed/assignment.cxx',
  'src/types/integer_signed/cast.cxx',
  'src/types/integer_signed/comparison.cxx',
  'src/types/integer_signed/constants.cxx',
  'src/types/integer_signed/constructor.cxx',
  'src/types/integer_signed/functions.cxx',
  'src/types/integer_signed/functions_bits.cxx',
  'src/types/integer_signed/functions_checked.cxx',
  'src/types/integer_signed/functions_generic.cxx',
  'src/types/integer_signed/functions_overflowing.cxx',
  'src/types/integer_signed/functions_saturating.cxx',
  'src/types/integer_signed/functions_strict.cxx',
  'src/types/integer_signed/functions_wrapping.cxx',
  'src/types/integer_signed/literals.cxx',
  'src/types/integer_signed/traits.cxx',
  'src/types/integer_signed/unary.cxx',

  'src/types/integer_unsigned/arithmetic.cxx',
  'src/types/integer_unsigned/assignment.cxx',
  'src/types/integer_unsigned/cast.cxx',
  'src/types/integer_unsigned/comparison.cxx',
  'src/types/integer_unsigned/constants.cxx',
  'src/types/integer_unsigned/constructor.cxx',
  'src/types/integer_unsigned/functions.cxx',
  'src/types/integer_unsigned/functions_bits.cxx',
  'src/types/integer_unsigned/functions_checked.cxx',
  'src/types/integer_unsigned/functions_generic.cxx',
  'src/types/integer_unsigned/functions_overflowing.cxx',
  'src/types/integer_unsigned/functions_saturating.cxx',
  'src/types/integer_unsigned/functions_strict.cxx',
  'src/types/integer_unsigned/functions_wrapping.cxx',
  'src/types/integer_unsigned/literals.cxx',
  'src/types/integer_unsigned/traits.cxx',
)

## Build

# Main Test Suite

test_suite = build_target(
    'test_suite',
    sources: sources,
    target_type: 'executable',
    include_directories: incdir,
    install : false,
    dependencies: [
        doctest_dep,
        ztd_dep,
    ],
)

test('ZTD Test Suite', test_suite)

