#include "CD.h"
CD::CD(const char* directory) {
	iso = fopen(directory, "r");
	dir = directory;
}

uint8_t CD::ReadDataByte() {
	if (buff_left >= CDXA_DATA_SIZE - 1)
		printf("[All data has been read]\n");
	return DataBuffer[buff_left++];
}

void CD::read(uint32_t loc) {
	//printf("[CD] Read sector %d\n", loc);
	fseek(iso, (loc - 150) * SECTOR_SIZE, SEEK_SET);
	fread(SectorBuffer, sizeof(uint8_t), SECTOR_SIZE, iso);
	memcpy(&DataBuffer, &SectorBuffer[0x18], 0x800);
}