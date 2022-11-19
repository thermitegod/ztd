# ZTD

## Build

```bash
mkdir build
cd build
meson setup ..
ninja
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
# libztd use vendored or system
libztd_dep = dependency('ztd', required : false)
if not libztd_dep.found() # using subproject
  libztd_proj = subproject('libztd')
  libztd_dep = libztd_proj.get_variable('libztd_dep')
endif
```
