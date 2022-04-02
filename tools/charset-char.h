#ifndef CHARSET_CHAR_H
#define CHARSET_CHAR_H

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t CharsetChar[8];

bool charsetCharEquals(CharsetChar a, CharsetChar b);
void charsetCharCopy(CharsetChar source, CharsetChar destination);

#endif
