#pragma once

#include <helpers.hpp>
#include <BitField.hpp>
#include <queue>
#include <scheduler.hpp>


constexpr u64 cpuSpeed = 33868800;
constexpr u64 readDelay = cpuSpeed / 75;
constexpr u64 readDelayDoubleSpeed = readDelay / 2;
constexpr u64 int3Delay = cpuSpeed / 1000;	// I don't know if this is ok???


class CDROM {
public:
	CDROM(Scheduler* scheduler);
	Scheduler* scheduler;

	void executeCommand(u8 data);
	
	// INTs
	bool shouldFireIRQ();
	static void int3(void* classptr);
	
	void pushParam(u8 data);

	u8 readStatus();
	void writeStatus(u8 data);
	
	void writeIE(u8 data);
	u8 readIF();
	void writeIF(u8 data);

	u8 getIndex();

	u8 getResponseByte();	// This one is public so it can be called from the memory read handlers
private:
	u8 intEnable = 0;
	u8 intFlag = 0;

	std::queue<u8> params;
	u8 getParamByte();

	std::queue<u8> response;

	union {
		u8 raw = 0;
		BitField<0, 2, u8> index;
		BitField<2, 1, u8> adpbusy;
		BitField<3, 1, u8> prmempt;
		BitField<4, 1, u8> prmwrdy;
		BitField<5, 1, u8> rslrrdy;
		BitField<6, 1, u8> drqsts;
		BitField<7, 1, u8> busysts;
	} statusReg;

	union {
		u8 raw = 0;
		BitField<0, 1, u8> error;
		BitField<1, 1, u8> motor;
		BitField<2, 1, u8> seekError;
		BitField<3, 1, u8> idError;
		BitField<4, 1, u8> shellOpen;
		BitField<5, 1, u8> reading;
		BitField<6, 1, u8> seeking;
		BitField<7, 1, u8> playing;
	} statusCode;
};

namespace CDROMCommands {
enum {
	GetStat = 0x01,
	Test	= 0x19
};
}	// End namespace CDROMCommands