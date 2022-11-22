# ZTD

## Defines

``` ZTD_DISABLE_GLOBAL_TYPES ``` Disable non-namespaced types

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

### Use System Version

Add to **meson.build**

```meson
libztd_dep = dependency('ztd', required : true)
```

### Use Meson Subproject

```meson
libztd_proj = subproject('libztd')
libztd_dep = libztd_proj.get_variable('libztd_dep')
```

### Using Either System or Subproject

```meson
# libztd use subproject or system
libztd_dep = dependency('ztd', required : false)
if not libztd_dep.found() # using subproject
  libztd_proj = subproject('libztd')
  libztd_dep = libztd_proj.get_variable('libztd_dep')
endif
```

## Running Tests

```sh
mkdir tests/build
cd tests/build
meson setup ..
ninja test
```
