# ZTD

## Required C++ Standard

Requires C++23 or higher.

## Feature Macros

``` ZTD_DISABLE_GLOBAL_TYPES ``` Disable adding global namespaced types

## Installing

## Using

### Gentoo install

ebuild at
<https://github.com/thermitegod/overlay/tree/master/dev-cpp/ztd>

### Use meson wrap

Versioned ztd.wrap files are in the directory ```wraps/```

Example meson usage below, just add to ```meson.build```

#### Use System Version

```meson
# ztd system
ztd_dep = dependency('ztd', required : true)
```

#### Use Meson Subproject

```meson
# ztd subproject
ztd_proj = subproject('ztd')
ztd_dep = ztd_proj.get_variable('ztd_dep')
```

#### Using Either System or Subproject

```meson
# ztd use system or subproject
ztd_dep = dependency('ztd', required : false)
if not ztd_dep.found() # using subproject
  ztd_proj = subproject('ztd')
  ztd_dep = ztd_proj.get_variable('ztd_dep')
endif
```

### Vendor into project

Copy ```include/ztd/``` into your project.

### Install to system, (not recommended)

```sh
mkdir build
cd build
doas ninja install
```

## Running Tests

To build and run tests [here](tests/README.md)

## Running Benchmarks

To build and run benchmarks [here](benchmarks/README.md)
