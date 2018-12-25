**identiconpp** is a library to generate identicons. Written in C++.

## Features

## Usage

The HTML reference can be generated with build_doc.sh, if doxygen is installed.
It is also available at [doc.schlomp.space/identiconpp/]
(https://doc.schlomp.space/identiconpp/classIdenticonpp.html).

## Install

<!-- ### Gentoo

Gentoo ebuilds are available via my
[repository](https://schlomp.space/tastytea/overlay). -->

### From source

#### Dependencies

* C++ compiler (tested: [gcc](https://gcc.gnu.org/) 5/6/7/8,
  [clang](https://llvm.org/) 5/6)
* [cmake](https://cmake.org/) (at least 3.2)
* [crypto++](https://cryptopp.com) (tested: 7.0 / 5.6)
* [imagemagick](https://www.imagemagick.org/) (tested: 7.0 / 6.7)

On a Debian system, install the packages: `build-essential cmake libcrypto++-dev
libmagick++-dev`.

#### Compile

```SH
mkdir build
cd build
cmake ..
make
make install
```

##### cmake options

* `-DCMAKE_BUILD_TYPE=Debug` for a debug build

## Contributing

Contributions are always welcome. You can submit them as pull requests or via
email to `tastytea`@`tastytea.de`.

## Contact

See https://tastytea.de/

## License & Copyright

```PLAIN
Copyright © 2018 tastytea <tastytea@tastytea.de>.
License GPLv3: GNU GPL version 3 <https://www.gnu.org/licenses/gpl-3.0.html>.
This program comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to redistribute it under certain conditions.
```
