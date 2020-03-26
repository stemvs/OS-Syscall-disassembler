// hejsotnoss
// 3/25/2020
#include "disassemble.h"

char* itolh(unsigned int offset, int l, char* stringBuffer) {
	unsigned char nibble;
	int i;
	for(i = 0; i < l; ++i) {
		nibble = (0xF & (offset >> (i * 4)));
		stringBuffer[l - i - 1] = nibble > 0x9 ? 0x37 + nibble : 0x30 | nibble;
	}
	return stringBuffer;
}

void disassemble(char* codeBuffer, char* buffer) {
	char hexBuffer8[3], hexBuffer12[4], hexBuffer16[5];
	unsigned int nibble[4] = {(codeBuffer[0] & 0x000000F0) >> 4, codeBuffer[0] & 0x0000000F, (codeBuffer[1] & 0x000000F0) >> 4, codeBuffer[1] & 0x0000000F};
	hexBuffer8[2] = 0x0;
	hexBuffer12[3] = 0x0;
	hexBuffer16[4] = 0x0;
	switch(nibble[0]) {
		case 0x8:
			switch(nibble[1]) {
				case 0x8:
					sprintf(buffer, "\033[0;94mcmp/eq\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x9:
					sprintf(buffer, "\033[0;94mbt\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xB:
					sprintf(buffer, "\033[0;94mbf\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xD:
					sprintf(buffer, "\033[0;94mbt/s\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xF:
					sprintf(buffer, "\033[0;94mbf/s\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x0:
					sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m)", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
					break;
				case 0x1:
					sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m)", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
					break;
				case 0x4:
					sprintf(buffer, "\033[0;94mmov.b\033[0m @(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR0\033[0m", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
					break;
				case 0x5:
					sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR0\033[0m", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
					break;
			}
			break;
		case 0x9:
			sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;92m0x%s\033[0m,PC),\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
			break;
		case 0xA:
			sprintf(buffer, "\033[0;94mbra\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[1] << 8 | nibble[2] << 4 | nibble[3], 3, hexBuffer12));
			break;
		case 0xB:
			sprintf(buffer, "\033[0;94mbsr\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[1] << 8 | nibble[2] << 4 | nibble[3], 3, hexBuffer12));
			break;
		case 0xC:
			switch(nibble[1]) {
				case 0x8:
					sprintf(buffer, "\033[0;94mtst\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x9:
					sprintf(buffer, "\033[0;94mand\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xA:
					sprintf(buffer, "\033[0;94mxor\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xB:
					sprintf(buffer, "\033[0;94mor\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xC:
					sprintf(buffer, "\033[0;94mtst.b\033[0m \033[0;92m#0x%s\033[0m,@(R0,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xD:
					sprintf(buffer, "\033[0;94mand.b\033[0m \033[0;92m#0x%s\033[0m,@(R0,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xE:
					sprintf(buffer, "\033[0;94mxor.b\033[0m \033[0;92m#0x%s\033[0m,@(R0,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0xF:
					sprintf(buffer, "\033[0;94mor.b\033[0m \033[0;92m#0x%s\033[0m,@(R0,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x0:
					sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%s\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x1:
					sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%s\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x2:
					sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%s\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x3:
					sprintf(buffer, "\033[0;94mtrapa\033[0m \033[0;92m#0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x4:
					sprintf(buffer, "\033[0;94mmov.b\033[0m @(\033[0;92m0x%s\033[0m,GBR),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x5:
					sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;92m0x%s\033[0m,GBR),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x6:
					sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;92m0x%s\033[0m,GBR),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
				case 0x7:
					sprintf(buffer, "\033[0;94mmova\033[0m @(\033[0;92m0x%s\033[0m,PC),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
					break;
			}
			break;
		case 0xD:
			sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;92m0x%s\033[0m,PC),\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
			break;
		case 0xE:
			sprintf(buffer, "\033[0;94mmov\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
			break;
		case 0x0:
			switch(nibble[3]) {
				case 0x8:
					switch(nibble[2]) {
						case 0x2:
							strcpy(buffer, "\033[0;94mclrmac\033[0m");
							break;
						case 0x4:
							strcpy(buffer, "\033[0;94mclrs\033[0m");
							break;
						case 0x0:
							strcpy(buffer, "\033[0;94mclrt\033[0m");
							break;
						case 0x3:
							strcpy(buffer, "\033[0;94mldtlb\033[0m");
							break;
						case 0x5:
							strcpy(buffer, "\033[0;94msets\033[0m");
							break;
						case 0x1:
							strcpy(buffer, "\033[0;94msett\033[0m");
							break;
					}
					break;
				case 0x9:
					switch(nibble[2]) {
						case 0x2:
							sprintf(buffer, "\033[0;94mmovt\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x1:
							strcpy(buffer, "\033[0;94mdiv0u\033[0m");
							break;
						case 0x0:
							strcpy(buffer, "\033[0;94mnop\033[0m");
							break;
					}
					break;
				case 0xA:
					switch(nibble[2]) {
						case 0xF:
							sprintf(buffer, "\033[0;94mstc\033[0m DBR,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x3:
							sprintf(buffer, "\033[0;94mstc\033[0m SGR,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94msts\033[0m MACH,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x1:
							sprintf(buffer, "\033[0;94msts\033[0m MACL,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94msts\033[0m PR,\033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0xB:
					switch(nibble[2]) {
						case 0xA:
							strcpy(buffer, "\033[0;94msynco\033[0m");
							break;
						case 0x0:
							strcpy(buffer, "\033[0;94mrts\033[0m");
							break;
						case 0x2:
							strcpy(buffer, "\033[0;94mrte\033[0m");
							break;
						case 0x1:
							strcpy(buffer, "\033[0;94msleep\033[0m");
							break;
					}
					break;
				case 0xC:
					sprintf(buffer, "\033[0;94mmov.b\033[0m @(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xD:
					sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xE:
					sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xF:
					sprintf(buffer, "\033[0;94mmac.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;91m@R%i+\033[0m", nibble[2], nibble[1]);
					break;
				case 0x2:
					if(nibble[2] & 0x8) {
						sprintf(buffer, "\033[0;94mstc\033[0m \033[0;31mR%i_BANK\033[0m,\033[0;91mR%i\033[0m", nibble[2] | 0x7, nibble[1]);
					} else {
						switch(nibble[2]) {
							case 0x0:
								sprintf(buffer, "\033[0;94mstc\033[0m SR,\033[0;91mR%i\033[0m", nibble[1]);
								break;
							case 0x1:
								sprintf(buffer, "\033[0;94mstc\033[0m GBR,\033[0;91mR%i\033[0m", nibble[1]);
								break;
							case 0x2:
								sprintf(buffer, "\033[0;94mstc\033[0m VBR,\033[0;91mR%i\033[0m", nibble[1]);
								break;
							case 0x3:
								sprintf(buffer, "\033[0;94mstc\033[0m SSR,\033[0;91mR%i\033[0m", nibble[1]);
								break;
							case 0x4:
								sprintf(buffer, "\033[0;94mstc\033[0m SPC,\033[0;91mR%i\033[0m", nibble[1]);
								break;
						}
					}
					break;
				case 0x3:
					switch(nibble[2]) {
						case 0x8:
							sprintf(buffer, "\033[0;94mpref\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0x9:
							sprintf(buffer, "\033[0;94mocbi\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0xA:
							sprintf(buffer, "\033[0;94mocbp\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0xB:
							sprintf(buffer, "\033[0;94mocbwb\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0xC:
							sprintf(buffer, "\033[0;94mmovca.l\033[0m \033[0;91mR0\033[0m,\033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0xD:
							sprintf(buffer, "\033[0;94mprefi\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0xE:
							sprintf(buffer, "\033[0;94micbi\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0x7:
							sprintf(buffer, "\033[0;94mmovco.l\033[0m \033[0;91mR0\033[0m,\033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0x6:
							sprintf(buffer, "\033[0;94mmovli.l\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR0\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mbraf\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mbsrf\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0x4:
					sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR%i\033[0m,@(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m)", nibble[2], nibble[1]);
					break;
				case 0x5:
					sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR%i\033[0m,@(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m)", nibble[2], nibble[1]);
					break;
				case 0x6:
					sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,@(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m)", nibble[2], nibble[1]);
					break;
				case 0x7:
					sprintf(buffer, "\033[0;94mmul.l\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
			}
			break;
		case 0x1:
			sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,@(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m)", nibble[2], *(itolh(nibble[3], 1, hexBuffer8)), nibble[1]);
			break;
		case 0x2:
			switch(nibble[3]) {
				case 0x8:
					sprintf(buffer, "\033[0;94mtst\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x9:
					sprintf(buffer, "\033[0;94mand\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xA:
					sprintf(buffer, "\033[0;94mxor\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xB:
					sprintf(buffer, "\033[0;94mor\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xC:
					sprintf(buffer, "\033[0;94mcmp/str\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xD:
					sprintf(buffer, "\033[0;94mxtrct\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xE:
					sprintf(buffer, "\033[0;94mmulu.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xF:
					sprintf(buffer, "\033[0;94mmuls.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x0:
					sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR%i\033[0m,\033[0;91m@R%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x1:
					sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR%i\033[0m,\033[0;91m@R%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x2:
					sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,\033[0;91m@R%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x4:
					sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR%i\033[0m,\033[0;91m@-R%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x5:
					sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR%i\033[0m,\033[0;91m@-R%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x6:
					sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,\033[0;91m@-R%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x7:
					sprintf(buffer, "\033[0;94mdiv0s\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
			}
			break;
		case 0x3:
			switch(nibble[3]) {
				case 0x8:
					sprintf(buffer, "\033[0;94msub\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xA:
					sprintf(buffer, "\033[0;94msubc\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xB:
					sprintf(buffer, "\033[0;94msubv\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xC:
					sprintf(buffer, "\033[0;94madd\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xD:
					sprintf(buffer, "\033[0;94mdmuls.l\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xE:
					sprintf(buffer, "\033[0;94maddc\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xF:
					sprintf(buffer, "\033[0;94maddv\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x0:
					sprintf(buffer, "\033[0;94mcmp/eq\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x2:
					sprintf(buffer, "\033[0;94mcmp/hs\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x3:
					sprintf(buffer, "\033[0;94mcmp/ge\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x4:
					sprintf(buffer, "\033[0;94mdiv1\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x5:
					sprintf(buffer, "\033[0;94mdmulu.l\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x6:
					sprintf(buffer, "\033[0;94mcmp/hi\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x7:
					sprintf(buffer, "\033[0;94mcmp/gt\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
			}
			break;
		case 0x4:
			switch(nibble[3]) {
				case 0x8:
					switch(nibble[2]) {
						case 0x0:
							sprintf(buffer, "\033[0;94mshll2\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x1:
							sprintf(buffer, "\033[0;94mshll8\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mshll16\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0x9:
					switch(nibble[2]) {
						case 0xA:
							sprintf(buffer, "\033[0;94mmovua.l\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR0\033[0m", nibble[1]);
							break;
						case 0xE:
							sprintf(buffer, "\033[0;94mmovua.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR0\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mshlr2\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x1:
							sprintf(buffer, "\033[0;94mshlr8\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mshlr16\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0xA:
					switch(nibble[2]) {
						case 0xF:
							sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,DBR", nibble[1]);
							break;
						case 0x3:
							sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SGR", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mlds\033[0m \033[0;91mR%i\033[0m,MACH", nibble[1]);
							break;
						case 0x1:
							sprintf(buffer, "\033[0;94mlds\033[0m \033[0;91mR%i\033[0m,MACL", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mlds\033[0m \033[0;91mR%i\033[0m,PR", nibble[1]);
							break;
					}
					break;
				case 0xB:
					switch(nibble[2]) {
						case 0x1:
							sprintf(buffer, "\033[0;94mtas.b\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mjmp\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mjsr\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0xC:
					sprintf(buffer, "\033[0;94mshad\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xD:
					sprintf(buffer, "\033[0;94mshld\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xE:
					if(nibble[2] & 0x8) {
						sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,\033[0;31mR%i_BANK\033[0m", nibble[1], nibble[2] | 0x7);
					} else {
						switch(nibble[2]) {
							case 0x0:
								sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SR", nibble[1]);
								break;
							case 0x1:
								sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,GBR", nibble[1]);
								break;
							case 0x2:
								sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,VBR", nibble[1]);
								break;
							case 0x3:
								sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SSR", nibble[1]);
								break;
							case 0x4:
								sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SPC", nibble[1]);
								break;
						}
					}
					break;
				case 0xF:
					sprintf(buffer, "\033[0;94mmac.w\033[0m \033[0;91m@R%i+\033[0m,\033[0;91m@R%i+\033[0m", nibble[2], nibble[1]);
					break;
				case 0x0:
					switch(nibble[2]) {
						case 0x1:
							sprintf(buffer, "\033[0;94mdt\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mshal\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mshll\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0x1:
					switch(nibble[2]) {
						case 0x1:
							sprintf(buffer, "\033[0;94mcmp/pz\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mshar\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mshlr\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0x2:
					switch(nibble[2]) {
						case 0xF:
							sprintf(buffer, "\033[0;94mstc.l\033[0m DBR,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x3:
							sprintf(buffer, "\033[0;94mstc.l\033[0m SGR,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94msts.l\033[0m MACH,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x1:
							sprintf(buffer, "\033[0;94msts.l\033[0m MACL,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94msts.l\033[0m PR,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0x3:
					if(nibble[2] & 0x8) {
						sprintf(buffer, "\033[0;94mstc.l\033[0m \033[0;31mR%i_BANK\033[0m,\033[0;91m@-R%i\033[0m", nibble[2] | 0x7, nibble[1]);
					} else {
						switch(nibble[2]) {
							case 0x0:
								sprintf(buffer, "\033[0;94mstc.l\033[0m SR,\033[0;91m@-R%i\033[0m", nibble[1]);
								break;
							case 0x1:
								sprintf(buffer, "\033[0;94mstc.l\033[0m GBR,\033[0;91m@-R%i\033[0m", nibble[1]);
								break;
							case 0x2:
								sprintf(buffer, "\033[0;94mstc.l\033[0m VBR,\033[0;91m@-R%i\033[0m", nibble[1]);
								break;
							case 0x3:
								sprintf(buffer, "\033[0;94mstc.l\033[0m SSR,\033[0;91m@-R%i\033[0m", nibble[1]);
								break;
							case 0x4:
								sprintf(buffer, "\033[0;94mstc.l\033[0m SPC,\033[0;91m@-R%i\033[0m", nibble[1]);
								break;
						}
					}
					break;
				case 0x4:
					switch(nibble[2]) {
						case 0x0:
							sprintf(buffer, "\033[0;94mrotl\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mrotcl\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0x5:
					switch(nibble[2]) {
						case 0x1:
							sprintf(buffer, "\033[0;94mcmp/pl\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mrotr\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mrotcr\033[0m \033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
					break;
				case 0x6:
					switch(nibble[2]) {
						case 0xF:
							sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,DBR", nibble[1]);
							break;
						case 0x3:
							sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SGR", nibble[1]);
							break;
						case 0x0:
							sprintf(buffer, "\033[0;94mlds.l\033[0m \033[0;91m@R%i+\033[0m,MACH", nibble[1]);
							break;
						case 0x1:
							sprintf(buffer, "\033[0;94mlds.l\033[0m \033[0;91m@R%i+\033[0m,MACL", nibble[1]);
							break;
						case 0x2:
							sprintf(buffer, "\033[0;94mlds.l\033[0m \033[0;91m@R%i+\033[0m,PR", nibble[1]);
							break;
					}
					break;
				case 0x7:
					if(nibble[2] & 0x8) {
						sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;31mR%i_BANK\033[0m", nibble[1], nibble[2] | 0x7);
					} else {
						switch(nibble[2]) {
							case 0x0:
								sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SR", nibble[1]);
								break;
							case 0x1:
								sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,GBR", nibble[1]);
								break;
							case 0x2:
								sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,VBR", nibble[1]);
								break;
							case 0x3:
								sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SSR", nibble[1]);
								break;
							case 0x4:
								sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SPC", nibble[1]);
								break;
						}
					}
					break;
			}
			break;
		case 0x5:
			sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2], nibble[1]);
			break;
		case 0x6:
			switch(nibble[3]) {
				case 0x8:
					sprintf(buffer, "\033[0;94mswap.b\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x9:
					sprintf(buffer, "\033[0;94mswap.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xA:
					sprintf(buffer, "\033[0;94mnegc\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xB:
					sprintf(buffer, "\033[0;94mneg\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xC:
					sprintf(buffer, "\033[0;94mextu.b\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xD:
					sprintf(buffer, "\033[0;94mextu.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xE:
					sprintf(buffer, "\033[0;94mexts.b\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0xF:
					sprintf(buffer, "\033[0;94mexts.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x0:
					sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x1:
					sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x2:
					sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x3:
					sprintf(buffer, "\033[0;94mmov\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x4:
					sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x5:
					sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x6:
					sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
				case 0x7:
					sprintf(buffer, "\033[0;94mnot\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
					break;
			}
			break;
		case 0x7:
			sprintf(buffer, "\033[0;94madd\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
			break;
	}
	if(!*buffer) {
		sprintf(buffer, ".word %s", itolh(nibble[0] << 12 | nibble[1] << 8 | nibble[2] << 4 | nibble[3], 4, hexBuffer16));
	}
}
