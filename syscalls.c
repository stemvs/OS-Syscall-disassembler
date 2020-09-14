// hejsotnoss
// 3/24/2020
#include "disassemble.h"

#define comp2(binaryBuffer) ((binaryBuffer[0] & 0xFF) << 8 | (binaryBuffer[1] & 0xFF))
#define comp3(binaryBuffer) ((binaryBuffer[0] & 0xFF) << 16 | (binaryBuffer[1] & 0xFF) << 8 | (binaryBuffer[2] & 0xFF))

int main(int argc, char* argv[]) {
	FILE* fp;
	char buffer[3], hexBuffer32[9], instructionHex16[5], instruction[65];
	unsigned int offset, value, i, syscall, syscallLength;
	if(argc < 2) {
		printf("No filename specified\n");
		return 0;
	}
	if(argc < 3) {
		printf("No syscall specified\n");
		return 0;
	}
	fp = fopen(argv[1], "rb");
	if(!fp) {
		printf("File opening failed\n");
		return 0;
	}
	hexBuffer32[8] = 0x0;
	instructionHex16[4] = 0x0;
	instruction[0] = 0x0;
	syscall = 0;
	fseek(fp, 0x1007D, SEEK_SET);
	fread(buffer, 1, 3, fp);
	offset = comp3(buffer);
	itolh(offset | 0x80000000, 8, hexBuffer32);
	printf("Syscall offset table: 0x%s\n", hexBuffer32);
	syscallLength = strlen(argv[2]);
	for(i = 0; i < syscallLength; ++i) {
		syscall += ((argv[2][i] & 0xF) + (9 * ((0x40 == (argv[2][i] & 0xF0)) | (0x60 == (argv[2][i] & 0xF0))))) << ((syscallLength - i - 1) * 4);
	}
	fseek(fp, comp3(buffer) + (syscall * 4) + 1, SEEK_SET);
	fread(buffer, 1, 3, fp);
	offset = comp3(buffer);
	itolh(offset | 0x80000000, 8, hexBuffer32);
	printf("Syscall offset: 0x%s\n\nOffset:         Code:        Instruction:\n...\n", hexBuffer32);
	fseek(fp, offset, SEEK_SET);
	for(i = 0; i < 40; i++) {
		fread(buffer, 1, 2, fp);
		value = comp2(buffer);
		itolh(value, 4, instructionHex16);
		disassemble(buffer, instruction);
		printf("\033[0;32m%s\033[0m:       %s         %s\n", hexBuffer32, instructionHex16, instruction);
		instruction[0] = 0x0;
		offset += 2;
		itolh(offset | 0x80000000, 8, hexBuffer32);
	}
	puts("...");
	fclose(fp);
	return 0;
}
