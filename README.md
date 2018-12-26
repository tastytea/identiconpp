**identiconpp** is a library to generate identicons. Written in C++.

You get the images as `Magick::Image`. This allows you to make all kinds of
modifications.

## Features

* [x] Symmetric identicons
* [x] sigil identicons
* [ ] Asymmetric identicons
* [ ] Padding

## Usage

The HTML reference can be generated with build_doc.sh, if doxygen is installed.
It is also available at [doc.schlomp.space/identiconpp/]
(https://doc.schlomp.space/identiconpp/classIdenticonpp.html).

You need to generate hashes yourself, any hexadecimal string will do. Make sure
to use a safe hashing algorithm for sensitive data (**not MD5**). You can select
as many columns and rows as you like, but make sure you have enough entropy.
If something seems to be wrong, exceptions will be thrown.

### Example

```C++
// Compile with g++ $(Magick++-config --cppflags --ldflags) -lidenticonpp
#include <identiconpp.hpp>
#include <Magick++/Image.h>

int main()
{
    Identiconpp identicon(5, 5, Identiconpp::algorithm::ltr_symmetric,
                          "ffffff88", { "800000ff" });
    Magick::Image img;
    img = identicon.generate("55502f40dc8b7c769880b10874abc9d0", 200);
    img.write("identicon.png");
}
```

## Install

### Gentoo

Gentoo ebuilds are available via my
[repository](https://schlomp.space/tastytea/overlay).

### Automatically generated packages

Binary packages are generated automatically for each
[release](https://schlomp.space/tastytea/identiconpp/releases) in the
formats:

* deb
* rpm
* tar.gz

They are generated on Debian Stretch 64 bit and signed with my
[automatic signing key](https://tastytea.de/tastytea_autosign.asc).

### From source

#### Dependencies

* C++ compiler (tested: [gcc](https://gcc.gnu.org/) 5/6/7/8,
  [clang](https://llvm.org/) 5/6)
* [cmake](https://cmake.org/) (at least 3.2)
* [imagemagick](https://www.imagemagick.org/) (tested: 7.0 / 6.7)

On a Debian system, install the packages:
`build-essential cmake libmagick++-dev`.

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
* One of:
    * `-DWITH_DEB=YES` to generate a deb-package
    * `-DWITH_RPM=YES` to generate an rpm-package

To generate a binary package, execute `make package`

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

## Algorithms

### ltr_symmetric

* Create image with width=columns, height=rows.
* Set background color.
* Select half of the columns, or half of the columns + 1 if uneven.
  * `columns / 2 + columns % 2`
* Pixels are drawn from left to right, top to bottom.
* Use bits from digest to determine if a pixel is painted(1) or not(0).
* Mirror the pixels vertically.
* Use the following bits to pick the foreground color.
* Scale image proportionally to requested width.

```PLAIN
 0111 0011 1101 1100 […] 1111 0111 0101 0111
^                            ^
+----------------------------+-------------->
             |                      |
        pixel matrix        foreground color
```

Implemented in [ltr_symmetric.cpp]
(https://schlomp.space/tastytea/identiconpp/src/branch/master/src/ltr_symmetric.cpp)

### sigil

* Create image with width=columns, height=rows.
* Set background color.
* Select half of the columns, or half of the columns + 1 if uneven.
  * `columns / 2 + columns % 2`
* Pixels are drawn from top to bottom, left to right.
* Use the first 8 bits to pick the foreground color.
* Use the following bits to determine if a pixel is painted(1) or not(0).
* Mirror the pixels vertically.
* Scale image proportionally to requested width.

```PLAIN
 0111 0011 1101 1100
^         ^
+---------+--------->
     |            |
foreground color  |
             pixel matrix
```

Implemented in [sigil.cpp]
(https://schlomp.space/tastytea/identiconpp/src/branch/master/src/sigil.cpp)
