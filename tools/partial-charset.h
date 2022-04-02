#ifndef PARTIAL_CHARSET_H
#define PARTIAL_CHARSET_H

#include "charset.h"

typedef struct PartialCharset
{
	Charset charset;
	// uint8_t is too small to store a count of 256.
	uint16_t numUsedChars;
} PartialCharset;

int partialCharsetFindIndexOrAdd(PartialCharset *charset, CharsetChar charsetChar);

#endif
