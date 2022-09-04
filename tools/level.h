#ifndef TOOLS_LEVEL_H
#define TOOLS_LEVEL_H

#include "uncompressed-levels.h"

void levelRemoveInvisibleColorChanges(Level *level);
void levelRemapChars(Level *level, Charset *newCharset);

#endif
