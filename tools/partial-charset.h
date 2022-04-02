#ifndef PARTIAL_CHARSET_H
#define PARTIAL_CHARSET_H

#include "charset.h"

typedef struct PartialCharset
{
	Charset charset;
	uint8_t numUsedChars;
} PartialCharset;

int partialCharsetFindIndexOrAdd(PartialCharset *charset, CharsetChar charsetChar);

#endif
