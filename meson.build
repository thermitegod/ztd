project(
  'ztd', ['c', 'cpp'],
  version : '0.1.0',
  license : 'GPL3',
  default_options : [
    'cpp_std=c++23',
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
fmt_dep = dependency('fmt', required : true)
spdlog_dep = dependency('spdlog', required : true)
openssl_dep = dependency('openssl', required : true)

dependencies = [
  fmt_dep,
  spdlog_dep,
  openssl_dep,
]

## build
target_name = 'ztd'

if not meson.is_subproject()
  pkg = import('pkgconfig')
  pkg.generate(
    name: target_name,
    description: 'ztd header only library',
    version: version,
    subdirs: ['.'],
    requires: dependencies,
  )
endif

## install headers
install_subdir('include/ztd', install_dir : prefix + '/include')

## meson subproject
ztd_dep = declare_dependency(include_directories : incdir, dependencies : dependencies)
