**identiconpp** is a library to generate identicons for C++ and C.

You get the images as `Magick::Image`. This allows you to make all kinds of
modifications.

![](https://doc.schlomp.space/identiconpp/identicon1.png
"4x4 identicon, ltr_symmetric, 20px padding")
![](https://doc.schlomp.space/identiconpp/identicon2.png
"5x5 identicon, sigil")
![](https://doc.schlomp.space/identiconpp/identicon3.png
"5x5 identicon, ltr_asymmetric")
![](https://doc.schlomp.space/identiconpp/identicon4.png
"6x4 identicon, ltr_symmetric, 10px padding")

The example images above are generated using [example.cpp]
(https://schlomp.space/tastytea/identiconpp/src/branch/master/example.cpp).

## Features

* [x] Symmetric identicons
* [x] sigil identicons
* [x] Asymmetric identicons
* [x] Padding

## Usage

The HTML reference can be generated with build_doc.sh, if doxygen is installed.
It is also available at [doc.schlomp.space/identiconpp/]
(https://doc.schlomp.space/identiconpp/classIdenticonpp.html).

You need to generate hashes yourself, any hexadecimal string will do. Make sure
to use a safe hashing algorithm for sensitive data (**not MD5**). You can select
as many columns and rows as you like, but make sure you have enough entropy.
If something seems to be wrong, exceptions will be thrown.

The "sigil" algorithm generates the same results as
[sigil](https://github.com/cupcake/sigil/) and
[pydenticon](https://github.com/azaghal/pydenticon/).

### Example

```C++
// Compile with g++ $(pkg-config --libs --cflags identiconpp)
#include <iostream>
#include <identiconpp.hpp>
#include <Magick++/Image.h>

int main()
{
    Identiconpp identicon(5, 5, Identiconpp::algorithm::ltr_symmetric,
                          "ffffff80", { "800000ff" }, { 10, 10 });
    Magick::Image img;
    img = identicon.generate("55502f40dc8b7c769880b10874abc9d0", 200);
    img.write("identicon.png");

    std::cout << identicon.generate_base64("png", "5550", 200) << std::endl;
}
```

### C interface

This is somewhat experimental. Have a look at [example.c]
(https://schlomp.space/tastytea/identiconpp/src/branch/master/example.c) and
[identiconpp_c.h](https://doc.schlomp.space/identiconpp/identiconpp__c_8h.html).

It seems to be impossible to use `Magick++` and `MagickWand` in the same
library, so the images are returned as base64-encoded strings.

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

* C++ compiler (tested: [gcc](https://gcc.gnu.org/) 6/8/9,
  [clang](https://llvm.org/) 6)
* [cmake](https://cmake.org/) (at least 3.2)
* [imagemagick](https://www.imagemagick.org/) (tested: 7.0 / 6.7)
* Optional:
  * Tests: [Catch](https://github.com/catchorg/Catch2) (tested: 2.3 / 1.2)

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
* `-DWITH_TESTS=YES` to build tests
* One of:
    * `-DWITH_DEB=YES` to generate a deb-package
    * `-DWITH_RPM=YES` to generate an rpm-package

To generate a binary package, execute `make package`

## Contributing

Contributions are always welcome. You can submit them as pull requests on
schlomp.space or via email to `tastytea`@`tastytea.de` (ideally using
`git format-patch` or `git send-email`). Please do not submit them via GitHub,
it is just a mirror.

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
  * You need `floor(log2(n_colors)) + 1` bits.
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

### ltr_asymmetric

* Create image with width=columns, height=rows.
* Set background color.
* Pixels are drawn from left to right, top to bottom.
* Use bits from digest to determine if a pixel is painted(1) or not(0).
* Use the following bits to pick the foreground color.
  * * You need `floor(log2(n_colors)) + 1` bits.
* Scale image proportionally to requested width.

```PLAIN
 0111 0011 1101 1100 […] 1111 0111 0101 0111
^                            ^
+----------------------------+-------------->
             |                      |
        pixel matrix        foreground color
```

Implemented in [ltr_asymmetric.cpp]
(https://schlomp.space/tastytea/identiconpp/src/branch/master/src/ltr_asymmetric.cpp)

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
