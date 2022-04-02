#ifndef CHARSET_H
#define CHARSET_H

#include "charset-char.h"

typedef CharsetChar Charset[256];

int charsetIndexOf(Charset charset, CharsetChar charsetChar);

#endif
