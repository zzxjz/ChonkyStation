#include <stdint.h>
#include "Bus.h"
#include "cop0.h"
class cpu
{
public:
	cpu();
	~cpu();
public:
	cop0 COP0 = cop0();
	Bus bus = Bus();
public:
	uint32_t fetch(uint32_t addr);
	void execute(uint32_t instr);
public:
	uint32_t jump; // jump branch delay slot
public:
	// registers
	uint32_t pc;
	uint32_t sp;
	uint32_t zero;
	uint32_t* regs = new uint32_t[27];
public:
	bool debug;
};

