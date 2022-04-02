#include "partial-charset.h"

int partialCharsetFindIndexOrAdd(PartialCharset *charset, CharsetChar charsetChar)
{
	charsetCharCopy(charsetChar, charset->charset[charset->numUsedChars]);
	return charset->numUsedChars++;
}
