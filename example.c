/*  This file is part of identiconpp.
 *  Public Domain / CC-0
 *
 *   Compile with gcc --std=c99 $(pkg-config --cflags --libs MagickWand) \
 *   $(pkg-config --cflags --libs openssl) -lidenticonpp
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "identiconpp_c.h"
#include <MagickWand/MagickWand.h>
#include <openssl/evp.h>
#include <openssl/bio.h>

char *b64decode(char *input, int length)
{
    BIO *b64, *bmem;

    char *buffer = (char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);

    BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return buffer;
}

int main(int argc, char *argv[])
{
    char digest[65] = "973dfe463ec85785f5f95af5ba3906ee"
                      "db2d931c24e69824a89ea65dba4e813b";
    const char colors[6][9] =
    {
        "800000ff",
        "008000ff",
        "000080ff",
        "808000ff",
        "008080ff",
        "800080ff"
    };

    if (argc > 1)
    {
        strncpy(digest, argv[1], 64);
    }

    MagickWand *mw = NULL;
    MagickWandGenesis();
    mw = NewMagickWand();

    {
        const uint8_t padding[2] = { 20, 20 };
        identiconpp_setup(4, 4, identiconpp_ltr_symmetric,
                          "ffffffff", colors, 6, padding);
        uint64_t len = identiconpp_generate("png", digest, 200);
        char base64[len];
        strcpy(base64, identiconpp_base64());
        MagickReadImageBlob(mw, b64decode(base64, len), len);
        MagickWriteImage(mw, "identicon1.png");
    }

    {
        const uint8_t padding[2] = { 0, 0 };
        identiconpp_setup(5, 5, identiconpp_sigil,
                          "00000080", colors, 6, padding);
        uint64_t len = identiconpp_generate("png", digest, 200);
        char base64[len];
        strcpy(base64, identiconpp_base64());
        MagickReadImageBlob(mw, b64decode(base64, len), len);
        MagickWriteImage(mw, "identicon2.png");
    }

    {
        const uint8_t padding[2] = { 0, 0 };
        identiconpp_setup(5, 5, identiconpp_ltr_asymmetric,
                          "000000ff", colors, 6, padding);
        uint64_t len = identiconpp_generate("png", digest, 200);
        char base64[len];
        strcpy(base64, identiconpp_base64());
        MagickReadImageBlob(mw, b64decode(base64, len), len);
        MagickWriteImage(mw, "identicon3.png");
    }

    {
        const uint8_t padding[2] = { 10, 10 };
        identiconpp_setup(6, 4, identiconpp_ltr_symmetric,
                          "000000c0", colors, 6, padding);
        uint64_t len = identiconpp_generate("png", digest, 200);
        char base64[len];
        strcpy(base64, identiconpp_base64());
        MagickReadImageBlob(mw, b64decode(base64, len), len);
        MagickWriteImage(mw, "identicon4.png");
    }

    DestroyMagickWand(mw);
    MagickWandTerminus();
}
