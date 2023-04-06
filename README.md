# ZTD

## Defines

``` ZTD_DISABLE_GLOBAL_TYPES ``` Disable non-namespaced types
``` ZTD_DISABLE_GLOBAL_LOG_MACROS ``` Disable LOG_* macros

## Building

### Build

```sh
mkdir build
cd build
meson setup ..
ninja
```

### Install

```sh
doas ninja install
```

## Using

Versioned ztd.wrap files are in the directory ```wraps```

Example meson usage below, just add to ```meson.build```

### Use System Version

```meson
# ztd system
ztd_dep = dependency('ztd', required : true)
```

### Use Meson Subproject

```meson
# ztd subproject
ztd_proj = subproject('ztd')
ztd_dep = ztd_proj.get_variable('ztd_dep')
```

### Using Either System or Subproject

```meson
# ztd use system or subproject
ztd_dep = dependency('ztd', required : false)
if not ztd_dep.found() # using subproject
  ztd_proj = subproject('ztd')
  ztd_dep = ztd_proj.get_variable('ztd_dep')
endif
```

## Running Tests

To build and run tests [here](tests/README.md)

## Running Benchmarks

To build and run benchmarks [here](benchmarks/README.md)
