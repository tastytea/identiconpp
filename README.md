**identiconpp** is a library to generate identicons. Written in C++.

You get the images as `Magick::Image`. This allows you to make all kinds of
modifications.

## Features

* [x] Simple identicons
* [ ] libravatar/sigil identicons

## Usage

The HTML reference can be generated with build_doc.sh, if doxygen is installed.
It is also available at [doc.schlomp.space/identiconpp/]
(https://doc.schlomp.space/identiconpp/classIdenticonpp.html).

### Example

```C++
// Compile with g++ $(Magick++-config --cppflags --ldflags) -lidenticonpp
#include <identiconpp.hpp>
#include <Magick++/Image.h>

int main()
{
    Identiconpp identicon(5, 5, Identiconpp::identicon_type::simple,
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
