project(
    'ztd',
    ['c', 'cpp'],
    version : '0.5.0-dev',
    license : 'GPL3',
    default_options : [
        'c_std=c23',
        'cpp_std=c++23',
        'buildtype=debugoptimized',
        'warning_level=3',
        'optimization=2',
        'prefix=/usr',
        'sysconfdir=/etc',
  ],
  meson_version : '>= 1.0.0'
)

incdir = include_directories('include')

package = meson.project_name()
version = meson.project_version()
prefix = get_option('prefix')

## dependencies
# have required=false to fix this problem when using as a subproject
# WARNING: Subproject 'X' did not override 'X' dependency and no variable name specified
# Dependency X from subproject subprojects/X found: NO
# boost_dep = dependency('boost', required: false)
magic_enum_dep = dependency('magic_enum', required: false, version: '>=0.9.7')

dependencies = [
    # boost_dep,
    magic_enum_dep,
]

## build
if not meson.is_subproject()
    pkg = import('pkgconfig')
    pkg.generate(
        name: 'ztd',
        description: 'ztd header only library',
        version: version,
        subdirs: ['.'],
        requires: dependencies,
    )
endif

## install headers
if not meson.is_subproject()
    install_subdir('include/ztd', install_dir : prefix + '/include')
endif

## meson subproject
ztd_dep = declare_dependency(include_directories : incdir, dependencies : dependencies)

if not meson.is_subproject()
    if get_option('tests')
        subdir('tests')
    endif

    if get_option('benchmarks')
        subdir('benchmarks')
    endif
endif
