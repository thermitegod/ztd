# ZTD

## Required C++ Standard

Requires C++26 or higher.

## Features

### Python string functions

List of all python like [functions](./docs/string_python.md).

### ztd::integer

Custom integer types.

```cpp
using i8    = ztd::integer<std::int8_t>;
using i16   = ztd::integer<std::int16_t>;
using i32   = ztd::integer<std::int32_t>;
using i64   = ztd::integer<std::int64_t>;
using isize = ztd::integer<std::ptrdiff_t>;

using u8    = ztd::integer<std::uint8_t>;
using u16   = ztd::integer<std::uint16_t>;
using u32   = ztd::integer<std::uint32_t>;
using u64   = ztd::integer<std::uint64_t>;
using usize = ztd::integer<std::size_t>;

// NOTE: ztd::floating is still a work in progress.
using f32   = ztd::floating<std::float_t>;
using f64   = ztd::floating<std::double_t>;
```

```cpp
u32 x = 1_u32;
u32 y = 2_u32;

u32 z = x + y;
assert(z == 3_u32);
```

Add a custom integer type. Currently needs to have both a signed and unsigned type, they both have to be the same size.

```cpp
struct custom_int{};
struct custom_uint{};

template<> struct ztd::integer_type<custom_int>
{
    using type = std::int32_t;
    using sign_conversion = custom_uint;
};

template<> struct ztd::integer_type<custom_uint>
{
    using type = std::uint32_t;
    using sign_conversion = custom_int;
};

using cint = ztd::integer<custom_int>;
using cuint = ztd::integer<custom_uint>;
```

### ztd::byte

Custom filesize types.

```cpp
using namespace ztd::byte_iec_literals;

ztd::byte_iec x = 1_MiB;
ztd::byte_iec y = 2_MiB;

ztd::byte_iec z = x + y;
assert(z == 3_MiB);
```

List of all integer [functions](./docs/integer.md).

## Feature Macros

``` ZTD_DISABLE_GLOBAL_TYPES ``` Disable global namespaced types
``` ZTD_DEFAULT_MATH_MODE ``` Set the default math mode for ztd::integer, setting to ```1``` enables strict mode (default), setting to ```2``` enables overflowing mode.

## Installing

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
meson setup ./build
ninja -C ./build
ninja -C ./build install
```

## Running Tests

```sh
meson setup --buildtype=debug -Dtests=true -Db_sanitize=address,undefined ./build
ninja -C ./build test

# run the test suite
./build/tests/test_suite
```
