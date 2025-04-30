# Python string function status

| Function     | Implemented | Notes
| ------------ | ----------- | -----
| casefold     | Maybe
| capitalize   | Full
| center       | Full
| count        | Full
| encode       | No
| endswith     | No          | use std::string::ends_with
| expandtabs   | Full
| find         | No          | use std::string::find
| format       | No          | use std::format
| format_map   | No          | use std::format
| index        | No          | use std::string::find
| isalnum      | Full
| isalpha      | Full
| isascii      | Disabled    | llvm libc++ has a macro with the same name
| isdecimal    | Full
| isdigit      | Partial     | Only supports base10
| isidentifier | No
| islower      | Full
| isnumeric    | Partial     | Only supports base10
| isprintable  | No
| isspace      | Full
| istitle      | Full
| isupper      | Full
| join         | Full
| ljust        | Full
| lower        | Full
| lstrip       | Full
| maketrans    | No
| partition    | Full        | Note, for empty 'sep', Python throws ValueError, We return {"str", "", ""}
| removeprefix | Full
| removesuffix | Full
| replace      | Full        | a empty 'find' does not cause 'replace' to be inserted between every character in 'str', Just returns the original string.
| rfind        | No          | use std::string::rfind
| rjust        | Full
| rindex       | No          | use std::string::rfind
| rpartition   | Full        | Note, for empty 'sep', Python throws ValueError, We return {"", "", "str"}
| rsplit       | Full
| rstrip       | Full
| split        | Full
| splitlines   | Full
| startswith   | No          | use std::string::starts_with
| strip        | Full
| swapcase     | Full
| title        | Full
| translate    | No
| upper        | Full
| zfill        | Full
