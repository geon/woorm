#ifndef LZ77_H
#define LZ77_H

#include "buffer.h"

void lz77Compress(Buffer *uncompressed, Buffer *compressed);
void lz77Decompress(Buffer *compressed, Buffer *decompressed);

#endif
