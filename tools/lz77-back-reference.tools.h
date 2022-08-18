#ifndef LZ77_BACK_REFERENCE_TOOS_H
#define LZ77_BACK_REFERENCE_TOOS_H

#include "../lz77-back-reference.h"
#include "buffer.h"
#include <stddef.h>

void backReferenceEncodeToBuffer(BackReference *backReference, Buffer *buffer);
BackReference backReferenceDecodeFromBuffer(Buffer *buffer);
BackReference backReferenceFind(Buffer *buffer, uint16_t location);

#endif
