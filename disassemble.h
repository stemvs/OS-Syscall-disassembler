
#ifndef DISASSEMBLE_H
#define DISASSEMBLE_H

#include <string.h>
#include <stdio.h>

char* itolh(unsigned int offset, int l, char* stringBuffer);
void disassemble(char* codeBuffer, char* buffer);

#endif

