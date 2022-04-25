#pragma once
#include <stdint.h>
#include <cstdarg>
#include <windows.h>
#include <array>
#include <vector>
#include "cdrom.h"
#include <fstream>
#include "logwindow.h"
#include "pad.h"

class memory
{
public:
	memory();
	~memory();

	uint32_t button_dest = 0;

	Log* logwnd;

	cdrom CDROM = cdrom();
	pad pads;
	std::vector<uint8_t> file;
	std::vector <uint8_t> bios;
	uint32_t adler32bios = 0;

public:
	uint32_t pc = 0;
	uint8_t* ram = new uint8_t[0x200000];
	uint8_t* scratchpad = new uint8_t[1024];
	uint8_t* exp1 = new uint8_t[1024000];
	uint8_t* exp2 = new uint8_t[8000];
	//uint8_t* regs = new uint8_t[0xffffff];
	//uint8_t* mem = new uint8_t[0xffffffff];
	uint32_t RAM_SIZE = 0;
	uint32_t I_MASK = 0;
	uint32_t I_STAT = 0;
	uint32_t CACHE_CONTROL = 0;

	uint32_t exp2_delay_size = 0;

	uint32_t SPUSTAT = 0;

	// dma
	uint32_t DCPR = 0;
	uint32_t DICR = 0;

	// timer
	uint16_t tmr1_stub = 0;


	typedef struct DMA {
		uint32_t MADR;
		uint32_t BCR;
		uint32_t CHCR;
	};

	DMA Ch2, Ch3, Ch4, Ch6;


	uint32_t gpuread = 0;
public:
	bool debug;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	void debug_log(const char* fmt, ...);
	void debug_warn(const char* fmt, ...);
	void debug_err(const char* fmt, ...);
	void loadBios(std::string directory);
	uint32_t loadExec(std::string directory);
	void write(uint32_t addr, uint8_t data, bool log);
	void write16(uint32_t addr, uint16_t data);
	void write32(uint32_t addr, uint32_t data);
	uint8_t read(uint32_t addr);
	uint16_t read16(uint32_t addr);
	uint32_t read32(uint32_t addr);

	uint32_t mask_address(const uint32_t addr);

	// HLE Syscalls
	void read_card_sector(int port, uint32_t sector, uint32_t dst);
};