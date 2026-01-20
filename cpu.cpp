#include "cpu.h"


cpu::cpu() {
	regA = 0x00;
	PC = 0x00;
	regStatus = 0x0;
	memory.resize(65536, 0x00);

	using a = cpu;
	lookup.assign(256, { "NOP", &a::NOP,&a::IMP });

	lookup[0x01] = { "LDA", &a::LDA, &a::IMM };
	lookup[0x02] = { "LDA", &a::LDA, &a::ABS };
	lookup[0x03] = { "STA", &a::STA, &a::ABS };
	lookup[0x10] = { "SUM", &a::SUM, &a::IMM };
	lookup[0x11] = { "SUM", &a::SUM, &a::ABS };
	lookup[0x12] = { "SUB", &a::SUB, &a::IMM };
	lookup[0x13] = { "SUB", &a::SUB, &a::ABS };
	//lookup[0x20] = { "JMP", &a::JMP, &a::ABS };
	//lookup[0x21] = { "ZVR", &a::ZVR, &a::ABS };
	//lookup[0x22] = { "TVR", &a::TVR, &a::ABS };
	//lookup[0x30] = { "ZCZ", &a::ZCZ, &a::IMP };
	//lookup[0x31] = { "TCF", &a::TCF, &a::IMP };
	
	fetched = 0x00;
	addr_abs = 0x00;
	opcode = 0x00;
}

cpu::~cpu(){}
void cpu::IMP() {
	fetched = 0x00;
}
void cpu::IMM() {
	addr_abs = PC;
	PC += 2;
	
}
void cpu::ABS() {
	uint16_t lo = readByte(PC);
	PC++;
	uint16_t hi = readByte(PC);
	PC++;
	addr_abs = (hi << 8) | lo;
}


uint8_t cpu::readByte(uint16_t addr) {
	return memory[addr];
}
void cpu::writeByte(uint16_t addr, uint8_t data) {
	memory[addr] = data;
}
int16_t cpu::readInt16(uint16_t addr) {

	uint16_t lo = readByte(addr);
	addr++;
	uint16_t hi = readByte(addr);
	addr++;
	return (int16_t)((hi << 8) | lo);
}
void cpu::writeInt16(uint16_t addr, int16_t data) {
	uint8_t lo = data & 0xFF;
	uint8_t hi = (data >> 8) & 0xFF;
	memory[addr++] = lo;
	memory[addr] = hi;
}

uint16_t  cpu::fetch() {
	if (lookup[opcode].mode != &cpu::IMP) fetched = readInt16(addr_abs);
	return fetched;
}


void cpu::NOP(){}
void cpu::LDA() {
	regA = fetched;
}
void cpu::STA() {
	writeInt16(addr_abs, regA);
}
void cpu::SUM() {
	regA = regA + fetched;
}
void cpu::SUB() {
	regA = regA - fetched;
}
//void cpu::CMP(){}
//void cpu::JMP(){}
//void cpu::ZVR(){}
//void cpu::TVR(){}
//void cpu::ZCZ(){}
//void cpu::TCF(){}


#include<iostream>

void cpu::run() {

	
	std::vector<uint8_t> input = { 
		0x01, 0x00 ,0x00, 
		0x10, 0x01, 0x00,
		0x10, 0x02, 0x00,
		0x10, 0x03, 0x00,
		0x10, 0x04, 0x00,
		0x10, 0x05, 0x00,
		0x10, 0x06, 0x00,
		0x10, 0x07, 0x00,
		0x10, 0x08, 0x00,
		0x10, 0x09, 0x00
	};
	std::copy(input.begin(), input.end(), memory.begin());
	PC = 0x00;

	for (int i = 0; i < 10; i++) {
		opcode = readByte(PC);
		PC++;

		(this->*lookup[opcode].mode)();
		fetch();
		(this->*lookup[opcode].opcode)();
		std::cout << regA << std::endl;
	}

	

}
