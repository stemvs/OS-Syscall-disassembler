// hejsotnoss
// 3/25/2020
#include "disassemble.h"

char* itolh(unsigned int offset, int l, char* stringBuffer) {
	unsigned char nibble;
	int i;
	l = l - 1
	for(i = 0; i < l; ++i) {
		nibble = (0xF & (offset >> (i * 4)));
		stringBuffer[l - i] = nibble > 0x9 ? 0x37 + nibble : 0x30 | nibble;
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
			case 0x8: /* 10001000iiiiiiii */
				sprintf(buffer, "\033[0;94mcmp/eq\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x9: /* 10001001dddddddd */
				sprintf(buffer, "\033[0;94mbt\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xB: /* 10001011dddddddd */
				sprintf(buffer, "\033[0;94mbf\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xD: /* 10001101dddddddd */
				sprintf(buffer, "\033[0;94mbt/s\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xF: /* 10001111dddddddd */
				sprintf(buffer, "\033[0;94mbf/s\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x0: /* 10000000nnnndddd */
				sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m)", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
				break;
			case 0x1: /* 10000001nnnndddd */
				sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m)", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
				break;
			case 0x4: /* 10000100mmmmdddd */
				sprintf(buffer, "\033[0;94mmov.b\033[0m @(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR0\033[0m", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
				break;
			case 0x5: /* 10000101mmmmdddd */
				sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR0\033[0m", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2]);
				break;
		}
		break;
	case 0x9: /* 1001nnnndddddddd */
		sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;92m0x%s\033[0m,PC),\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
		break;
	case 0xA: /* 1010dddddddddddd */
		sprintf(buffer, "\033[0;94mbra\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[1] << 8 | nibble[2] << 4 | nibble[3], 3, hexBuffer12));
		break;
	case 0xB: /* 1011dddddddddddd */
		sprintf(buffer, "\033[0;94mbsr\033[0m \033[0;92m0x%s\033[0m", itolh(nibble[1] << 8 | nibble[2] << 4 | nibble[3], 3, hexBuffer12));
		break;
	case 0xC:
		switch(nibble[1]) {
			case 0x8: /* 11001000iiiiiiii */
				sprintf(buffer, "\033[0;94mtst\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x9: /* 11001001iiiiiiii */
				sprintf(buffer, "\033[0;94mand\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xA: /* 11001010iiiiiiii */
				sprintf(buffer, "\033[0;94mxor\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xB: /* 11001011iiiiiiii */
				sprintf(buffer, "\033[0;94mor\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xC: /* 11001100iiiiiiii */
				sprintf(buffer, "\033[0;94mtst.b\033[0m \033[0;92m#0x%s\033[0m,@(\033[0;91mR0\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xD: /* 11001101iiiiiiii */
				sprintf(buffer, "\033[0;94mand.b\033[0m \033[0;92m#0x%s\033[0m,@(\033[0;91mR0\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xE: /* 11001110iiiiiiii */
				sprintf(buffer, "\033[0;94mxor.b\033[0m \033[0;92m#0x%s\033[0m,@(\033[0;91mR0\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0xF: /* 11001111iiiiiiii */
				sprintf(buffer, "\033[0;94mor.b\033[0m \033[0;92m#0x%s\033[0m,@(\033[0;91mR0\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x0: /* 11000000dddddddd */
				sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%s\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x1: /* 11000001dddddddd */
				sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%s\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x2: /* 11000010dddddddd */
				sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR0\033[0m,@(\033[0;92m0x%s\033[0m,GBR)", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x3: /* 11000011iiiiiiii */
				sprintf(buffer, "\033[0;94mtrapa\033[0m \033[0;92m#0x%s\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x4: /* 11000100dddddddd */
				sprintf(buffer, "\033[0;94mmov.b\033[0m @(\033[0;92m0x%s\033[0m,GBR),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x5: /* 11000101dddddddd */
				sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;92m0x%s\033[0m,GBR),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x6: /* 11000110dddddddd */
				sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;92m0x%s\033[0m,GBR),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
			case 0x7: /* 11000111dddddddd */
				sprintf(buffer, "\033[0;94mmova\033[0m @(\033[0;92m0x%s\033[0m,PC),\033[0;91mR0\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8));
				break;
		}
		break;
	case 0xD: /* 1101nnnndddddddd */
		sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;92m0x%s\033[0m,PC),\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
		break;
	case 0xE: /* 1110nnnniiiiiiii */
		sprintf(buffer, "\033[0;94mmov\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
		break;
	case 0x0:
		switch(nibble[3]) {
			case 0x8:
				switch(nibble[2]) {
					case 0x2: /* 0000000000101000 */
						strcpy(buffer, "\033[0;94mclrmac\033[0m");
						break;
					case 0x4: /* 0000000001001000 */
						strcpy(buffer, "\033[0;94mclrs\033[0m");
						break;
					case 0x0: /* 0000000000001000 */
						strcpy(buffer, "\033[0;94mclrt\033[0m");
						break;
					case 0x3: /* 0000000000111000 */
						strcpy(buffer, "\033[0;94mldtlb\033[0m");
						break;
					case 0x5: /* 0000000001011000 */
						strcpy(buffer, "\033[0;94msets\033[0m");
						break;
					case 0x1: /* 0000000000011000 */
						strcpy(buffer, "\033[0;94msett\033[0m");
						break;
				}
				break;
			case 0x9:
				switch(nibble[2]) {
					case 0x2: /* 0000nnnn00101001 */
						sprintf(buffer, "\033[0;94mmovt\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x1: /* 0000000000011001 */
						strcpy(buffer, "\033[0;94mdiv0u\033[0m");
						break;
					case 0x0: /* 0000000000001001 */
						strcpy(buffer, "\033[0;94mnop\033[0m");
						break;
				}
				break;
			case 0xA:
				switch(nibble[2]) {
					case 0xF: /* 0000nnnn11111010 */
						sprintf(buffer, "\033[0;94mstc\033[0m DBR,\033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x3: /* 0000nnnn00111010 */
						sprintf(buffer, "\033[0;94mstc\033[0m SGR,\033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x0: /* 0000nnnn00001010 */
						sprintf(buffer, "\033[0;94msts\033[0m MACH,\033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x1: /* 0000nnnn00011010 */
						sprintf(buffer, "\033[0;94msts\033[0m MACL,\033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0000nnnn00101010 */
						sprintf(buffer, "\033[0;94msts\033[0m PR,\033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0xB:
				switch(nibble[2]) {
					case 0xA: /* 0000000010101011 */
						strcpy(buffer, "\033[0;94msynco\033[0m");
						break;
					case 0x0: /* 0000000000001011 */
						strcpy(buffer, "\033[0;94mrts\033[0m");
						break;
					case 0x2: /* 0000000000101011 */
						strcpy(buffer, "\033[0;94mrte\033[0m");
						break;
					case 0x1: /* 0000000000011011 */
						strcpy(buffer, "\033[0;94msleep\033[0m");
						break;
				}
				break;
			case 0xC: /* 0000nnnnmmmm1100 */
				sprintf(buffer, "\033[0;94mmov.b\033[0m @(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xD: /* 0000nnnnmmmm1101 */
				sprintf(buffer, "\033[0;94mmov.w\033[0m @(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xE: /* 0000nnnnmmmm1110 */
				sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xF: /* 0000nnnnmmmm1111 */
				sprintf(buffer, "\033[0;94mmac.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;91m@R%i+\033[0m", nibble[2], nibble[1]);
				break;
			case 0x2:
				if(nibble[2] & 0x8) { /* 0000nnnn1mmm0010 */
					sprintf(buffer, "\033[0;94mstc\033[0m \033[0;31mR%i_BANK\033[0m,\033[0;91mR%i\033[0m", nibble[2] | 0x7, nibble[1]);
				} else {
					switch(nibble[2]) {
						case 0x0: /* 0000nnnn00000010 */
							sprintf(buffer, "\033[0;94mstc\033[0m SR,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x1: /* 0000nnnn00010010 */
							sprintf(buffer, "\033[0;94mstc\033[0m GBR,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x2: /* 0000nnnn00100010 */
							sprintf(buffer, "\033[0;94mstc\033[0m VBR,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x3: /* 0000nnnn00110010 */
							sprintf(buffer, "\033[0;94mstc\033[0m SSR,\033[0;91mR%i\033[0m", nibble[1]);
							break;
						case 0x4: /* 0000nnnn01000010 */
							sprintf(buffer, "\033[0;94mstc\033[0m SPC,\033[0;91mR%i\033[0m", nibble[1]);
							break;
					}
				}
				break;
			case 0x3:
				switch(nibble[2]) {
					case 0x8: /* 0000nnnn10000011 */
						sprintf(buffer, "\033[0;94mpref\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0x9: /* 0000nnnn10010011 */
						sprintf(buffer, "\033[0;94mocbi\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0xA: /* 0000nnnn10100011 */
						sprintf(buffer, "\033[0;94mocbp\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0xB: /* 0000nnnn10110011 */
						sprintf(buffer, "\033[0;94mocbwb\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0xC: /* 0000nnnn11000011 */
						sprintf(buffer, "\033[0;94mmovca.l\033[0m \033[0;91mR0\033[0m,\033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0xD: /* 0000nnnn11010011 */
						sprintf(buffer, "\033[0;94mprefi\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0xE: /* 0000nnnn11100011 */
						sprintf(buffer, "\033[0;94micbi\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0x7: /* 0000nnnn01110011 */
						sprintf(buffer, "\033[0;94mmovco.l\033[0m \033[0;91mR0\033[0m,\033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0x6: /* 0000mmmm01100011 */
						sprintf(buffer, "\033[0;94mmovli.l\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR0\033[0m", nibble[1]);
						break;
					case 0x2: /* 0000nnnn00100011 */
						sprintf(buffer, "\033[0;94mbraf\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x0: /* 0000nnnn00000011 */
						sprintf(buffer, "\033[0;94mbsrf\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0x4: /* 0000nnnnmmmm0100 */
				sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR%i\033[0m,@(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m)", nibble[2], nibble[1]);
				break;
			case 0x5: /* 0000nnnnmmmm0101 */
				sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR%i\033[0m,@(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m)", nibble[2], nibble[1]);
				break;
			case 0x6: /* 0000nnnnmmmm0110 */
				sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,@(\033[0;91mR0\033[0m,\033[0;91mR%i\033[0m)", nibble[2], nibble[1]);
				break;
			case 0x7: /* 0000nnnnmmmm0111 */
				sprintf(buffer, "\033[0;94mmul.l\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
		}
		break;
	case 0x1: /* 0001nnnnmmmmdddd */
		sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,@(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m)", nibble[2], *(itolh(nibble[3], 1, hexBuffer8)), nibble[1]);
		break;
	case 0x2:
		switch(nibble[3]) {
			case 0x8: /* 0010nnnnmmmm1000 */
				sprintf(buffer, "\033[0;94mtst\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x9: /* 0010nnnnmmmm1001 */
				sprintf(buffer, "\033[0;94mand\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xA: /* 0010nnnnmmmm1010 */
				sprintf(buffer, "\033[0;94mxor\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xB: /* 0010nnnnmmmm1011 */
				sprintf(buffer, "\033[0;94mor\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xC: /* 0010nnnnmmmm1100 */
				sprintf(buffer, "\033[0;94mcmp/str\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xD: /* 0010nnnnmmmm1101 */
				sprintf(buffer, "\033[0;94mxtrct\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xE: /* 0010nnnnmmmm1110 */
				sprintf(buffer, "\033[0;94mmulu.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xF: /* 0010nnnnmmmm1111 */
				sprintf(buffer, "\033[0;94mmuls.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x0: /* 0010nnnnmmmm0000 */
				sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR%i\033[0m,\033[0;91m@R%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x1: /* 0010nnnnmmmm0001 */
				sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR%i\033[0m,\033[0;91m@R%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x2: /* 0010nnnnmmmm0010 */
				sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,\033[0;91m@R%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x4: /* 0010nnnnmmmm0100 */
				sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91mR%i\033[0m,\033[0;91m@-R%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x5: /* 0010nnnnmmmm0101 */
				sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91mR%i\033[0m,\033[0;91m@-R%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x6: /* 0010nnnnmmmm0110 */
				sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91mR%i\033[0m,\033[0;91m@-R%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x7: /* 0010nnnnmmmm0111 */
				sprintf(buffer, "\033[0;94mdiv0s\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
		}
		break;
	case 0x3:
		switch(nibble[3]) {
			case 0x8: /* 0011nnnnmmmm1000 */
				sprintf(buffer, "\033[0;94msub\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xA: /* 0011nnnnmmmm1010 */
				sprintf(buffer, "\033[0;94msubc\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xB: /* 0011nnnnmmmm1011 */
				sprintf(buffer, "\033[0;94msubv\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xC: /* 0011nnnnmmmm1100 */
				sprintf(buffer, "\033[0;94madd\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xD: /* 0011nnnnmmmm1101 */
				sprintf(buffer, "\033[0;94mdmuls.l\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xE: /* 0011nnnnmmmm1110 */
				sprintf(buffer, "\033[0;94maddc\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xF: /* 0011nnnnmmmm1111 */
				sprintf(buffer, "\033[0;94maddv\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x0: /* 0011nnnnmmmm0000 */
				sprintf(buffer, "\033[0;94mcmp/eq\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x2: /* 0011nnnnmmmm0010 */
				sprintf(buffer, "\033[0;94mcmp/hs\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x3: /* 0011nnnnmmmm0011 */
				sprintf(buffer, "\033[0;94mcmp/ge\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x4: /* 0011nnnnmmmm0100 */
				sprintf(buffer, "\033[0;94mdiv1\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x5: /* 0011nnnnmmmm0101 */
				sprintf(buffer, "\033[0;94mdmulu.l\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x6: /* 0011nnnnmmmm0110 */
				sprintf(buffer, "\033[0;94mcmp/hi\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x7: /* 0011nnnnmmmm0111 */
				sprintf(buffer, "\033[0;94mcmp/gt\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
		}
		break;
	case 0x4:
		switch(nibble[3]) {
			case 0x8:
				switch(nibble[2]) {
					case 0x0: /* 0100nnnn00001000 */
						sprintf(buffer, "\033[0;94mshll2\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x1: /* 0100nnnn00011000 */
						sprintf(buffer, "\033[0;94mshll8\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00101000 */
						sprintf(buffer, "\033[0;94mshll16\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0x9:
				switch(nibble[2]) {
					case 0xA: /* 0100mmmm10101001 */
						sprintf(buffer, "\033[0;94mmovua.l\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR0\033[0m", nibble[1]);
						break;
					case 0xE: /* 0100mmmm11101001 */
						sprintf(buffer, "\033[0;94mmovua.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR0\033[0m", nibble[1]);
						break;
					case 0x0: /* 0100nnnn00001001 */
						sprintf(buffer, "\033[0;94mshlr2\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x1: /* 0100nnnn00011001 */
						sprintf(buffer, "\033[0;94mshlr8\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00101001 */
						sprintf(buffer, "\033[0;94mshlr16\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0xA:
				switch(nibble[2]) {
					case 0xF: /* 0100mmmm11111010 */
						sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,DBR", nibble[1]);
						break;
					case 0x3: /* 0100mmmm00111010 */
						sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SGR", nibble[1]);
						break;
					case 0x0: /* 0100mmmm00001010 */
						sprintf(buffer, "\033[0;94mlds\033[0m \033[0;91mR%i\033[0m,MACH", nibble[1]);
						break;
					case 0x1: /* 0100mmmm00011010 */
						sprintf(buffer, "\033[0;94mlds\033[0m \033[0;91mR%i\033[0m,MACL", nibble[1]);
						break;
					case 0x2: /* 0100mmmm00101010 */
						sprintf(buffer, "\033[0;94mlds\033[0m \033[0;91mR%i\033[0m,PR", nibble[1]);
						break;
				}
				break;
			case 0xB:
				switch(nibble[2]) {
					case 0x1: /* 0100nnnn00011011 */
						sprintf(buffer, "\033[0;94mtas.b\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00101011 */
						sprintf(buffer, "\033[0;94mjmp\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
					case 0x0: /* 0100nnnn00001011 */
						sprintf(buffer, "\033[0;94mjsr\033[0m \033[0;91m@R%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0xC: /* 0100nnnnmmmm1100 */
				sprintf(buffer, "\033[0;94mshad\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xD: /* 0100nnnnmmmm1101 */
				sprintf(buffer, "\033[0;94mshld\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xE:
				if(nibble[2] & 0x8) { /* 0100mmmm1nnn1110 */
					sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,\033[0;31mR%i_BANK\033[0m", nibble[1], nibble[2] | 0x7);
				} else {
					switch(nibble[2]) {
						case 0x0: /* 0100mmmm00001110 */
							sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SR", nibble[1]);
							break;
						case 0x1: /* 0100mmmm00011110 */
							sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,GBR", nibble[1]);
							break;
						case 0x2: /* 0100mmmm00101110 */
							sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,VBR", nibble[1]);
							break;
						case 0x3: /* 0100mmmm00111110 */
							sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SSR", nibble[1]);
							break;
						case 0x4: /* 0100mmmm01001110 */
							sprintf(buffer, "\033[0;94mldc\033[0m \033[0;91mR%i\033[0m,SPC", nibble[1]);
							break;
					}
				}
				break;
			case 0xF: /* 0100nnnnmmmm1111 */
				sprintf(buffer, "\033[0;94mmac.w\033[0m \033[0;91m@R%i+\033[0m,\033[0;91m@R%i+\033[0m", nibble[2], nibble[1]);
				break;
			case 0x0:
				switch(nibble[2]) {
					case 0x1: /* 0100nnnn00010000 */
						sprintf(buffer, "\033[0;94mdt\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00100000 */
						sprintf(buffer, "\033[0;94mshal\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x0: /* 0100nnnn00000000 */
						sprintf(buffer, "\033[0;94mshll\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0x1:
				switch(nibble[2]) {
					case 0x1: /* 0100nnnn00010001 */
						sprintf(buffer, "\033[0;94mcmp/pz\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00100001 */
						sprintf(buffer, "\033[0;94mshar\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x0: /* 0100nnnn00000001 */
						sprintf(buffer, "\033[0;94mshlr\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0x2:
				switch(nibble[2]) {
					case 0xF: /* 0100nnnn11110010 */
						sprintf(buffer, "\033[0;94mstc.l\033[0m DBR,\033[0;91m@-R%i\033[0m", nibble[1]);
						break;
					case 0x3: /* 0100nnnn00110010 */
						sprintf(buffer, "\033[0;94mstc.l\033[0m SGR,\033[0;91m@-R%i\033[0m", nibble[1]);
						break;
					case 0x0: /* 0100nnnn00000010 */
						sprintf(buffer, "\033[0;94msts.l\033[0m MACH,\033[0;91m@-R%i\033[0m", nibble[1]);
						break;
					case 0x1: /* 0100nnnn00010010 */
						sprintf(buffer, "\033[0;94msts.l\033[0m MACL,\033[0;91m@-R%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00100010 */
						sprintf(buffer, "\033[0;94msts.l\033[0m PR,\033[0;91m@-R%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0x3:
				if(nibble[2] & 0x8) { /* 0100nnnn1mmm0011 */
					sprintf(buffer, "\033[0;94mstc.l\033[0m \033[0;31mR%i_BANK\033[0m,\033[0;91m@-R%i\033[0m", nibble[2] | 0x7, nibble[1]);
				} else {
					switch(nibble[2]) {
						case 0x0: /* 0100nnnn00000011 */
							sprintf(buffer, "\033[0;94mstc.l\033[0m SR,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x1: /* 0100nnnn00010011 */
							sprintf(buffer, "\033[0;94mstc.l\033[0m GBR,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x2: /* 0100nnnn00100011 */
							sprintf(buffer, "\033[0;94mstc.l\033[0m VBR,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x3: /* 0100nnnn00110011 */
							sprintf(buffer, "\033[0;94mstc.l\033[0m SSR,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
						case 0x4: /* 0100nnnn01000011 */
							sprintf(buffer, "\033[0;94mstc.l\033[0m SPC,\033[0;91m@-R%i\033[0m", nibble[1]);
							break;
					}
				}
				break;
			case 0x4:
				switch(nibble[2]) {
					case 0x0: /* 0100nnnn00000100 */
						sprintf(buffer, "\033[0;94mrotl\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00100100 */
						sprintf(buffer, "\033[0;94mrotcl\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0x5:
				switch(nibble[2]) {
					case 0x1: /* 0100nnnn00010101 */
						sprintf(buffer, "\033[0;94mcmp/pl\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x0: /* 0100nnnn00000101 */
						sprintf(buffer, "\033[0;94mrotr\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
					case 0x2: /* 0100nnnn00100101 */
						sprintf(buffer, "\033[0;94mrotcr\033[0m \033[0;91mR%i\033[0m", nibble[1]);
						break;
				}
				break;
			case 0x6:
				switch(nibble[2]) {
					case 0xF: /* 0100mmmm11110110 */
						sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,DBR", nibble[1]);
						break;
					case 0x3: /* 0100mmmm00110110 */
						sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SGR", nibble[1]);
						break;
					case 0x0: /* 0100mmmm00000110 */
						sprintf(buffer, "\033[0;94mlds.l\033[0m \033[0;91m@R%i+\033[0m,MACH", nibble[1]);
						break;
					case 0x1: /* 0100mmmm00010110 */
						sprintf(buffer, "\033[0;94mlds.l\033[0m \033[0;91m@R%i+\033[0m,MACL", nibble[1]);
						break;
					case 0x2: /* 0100mmmm00100110 */
						sprintf(buffer, "\033[0;94mlds.l\033[0m \033[0;91m@R%i+\033[0m,PR", nibble[1]);
						break;
				}
				break;
			case 0x7:
				if(nibble[2] & 0x8) { /* 0100mmmm1nnn0111 */
					sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;31mR%i_BANK\033[0m", nibble[1], nibble[2] | 0x7);
				} else {
					switch(nibble[2]) {
						case 0x0: /* 0100mmmm00000111 */
							sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SR", nibble[1]);
							break;
						case 0x1: /* 0100mmmm00010111 */
							sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,GBR", nibble[1]);
							break;
						case 0x2: /* 0100mmmm00100111 */
							sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,VBR", nibble[1]);
							break;
						case 0x3: /* 0100mmmm00110111 */
							sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SSR", nibble[1]);
							break;
						case 0x4: /* 0100mmmm01000111 */
							sprintf(buffer, "\033[0;94mldc.l\033[0m \033[0;91m@R%i+\033[0m,SPC", nibble[1]);
							break;
					}
				}
				break;
		}
		break;
	case 0x5: /* 0101nnnnmmmmdddd */
		sprintf(buffer, "\033[0;94mmov.l\033[0m @(\033[0;92m0x%c\033[0m,\033[0;91mR%i\033[0m),\033[0;91mR%i\033[0m", *(itolh(nibble[3], 1, hexBuffer8)), nibble[2], nibble[1]);
		break;
	case 0x6:
		switch(nibble[3]) {
			case 0x8: /* 0110nnnnmmmm1000 */
				sprintf(buffer, "\033[0;94mswap.b\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x9: /* 0110nnnnmmmm1001 */
				sprintf(buffer, "\033[0;94mswap.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xA: /* 0110nnnnmmmm1010 */
				sprintf(buffer, "\033[0;94mnegc\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xB: /* 0110nnnnmmmm1011 */
				sprintf(buffer, "\033[0;94mneg\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xC: /* 0110nnnnmmmm1100 */
				sprintf(buffer, "\033[0;94mextu.b\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xD: /* 0110nnnnmmmm1101 */
				sprintf(buffer, "\033[0;94mextu.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xE: /* 0110nnnnmmmm1110 */
				sprintf(buffer, "\033[0;94mexts.b\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0xF: /* 0110nnnnmmmm1111 */
				sprintf(buffer, "\033[0;94mexts.w\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x0: /* 0110nnnnmmmm0000 */
				sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x1: /* 0110nnnnmmmm0001 */
				sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x2: /* 0110nnnnmmmm0010 */
				sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91m@R%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x3: /* 0110nnnnmmmm0011 */
				sprintf(buffer, "\033[0;94mmov\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x4: /* 0110nnnnmmmm0100 */
				sprintf(buffer, "\033[0;94mmov.b\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x5: /* 0110nnnnmmmm0101 */
				sprintf(buffer, "\033[0;94mmov.w\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x6: /* 0110nnnnmmmm0110 */
				sprintf(buffer, "\033[0;94mmov.l\033[0m \033[0;91m@R%i+\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
			case 0x7: /* 0110nnnnmmmm0111 */
				sprintf(buffer, "\033[0;94mnot\033[0m \033[0;91mR%i\033[0m,\033[0;91mR%i\033[0m", nibble[2], nibble[1]);
				break;
		}
		break;
	case 0x7: /* 0111nnnniiiiiiii */
		sprintf(buffer, "\033[0;94madd\033[0m \033[0;92m#0x%s\033[0m,\033[0;91mR%i\033[0m", itolh(nibble[2] << 4 | nibble[3], 2, hexBuffer8), nibble[1]);
		break;
}
	if(!*buffer) {
		sprintf(buffer, ".word 0x%s", itolh(nibble[0] << 12 | nibble[1] << 8 | nibble[2] << 4 | nibble[3], 4, hexBuffer16));
	}
}
