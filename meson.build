project(
    'ztd',
    ['c', 'cpp'],
    version : '0.6.0-dev',
    license : 'GPL3',
    default_options : [
        'c_std=c23',
        'cpp_std=c++26',
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

dependencies = []

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
