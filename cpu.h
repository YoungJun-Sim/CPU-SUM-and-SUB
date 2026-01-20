#pragma once
#include<vector>
#include<cstdint>
#include<string>

class cpu
{
public:
	cpu();
	~cpu();
	void run();


private:

	std::vector<uint8_t> memory;

	int16_t regA = 0;
	uint16_t PC = 0;
	uint8_t regStatus = 0;
	enum flag {
		Z = (1 << 0),
		T = (1 << 1)
	};



	struct INSTRUCTION {
		std::string name;
		void (cpu::* opcode)(void);
		void (cpu::* mode)(void);
	};
	std::vector<INSTRUCTION> lookup;

private:

	uint16_t fetched = 0;
	uint16_t addr_abs = 0;
	uint8_t opcode = 0;
	uint16_t fetch();

	uint8_t readByte(uint16_t addr);
	void writeByte(uint16_t addr, uint8_t data);
	int16_t readInt16(uint16_t addr);
	void writeInt16(uint16_t addr, int16_t data);



private:
	void IMP(); void IMM();
	void ABS();

private:
	void NOP();
	void LDA(); void STA();
	void SUM(); void SUB();
	//void CMP(); void JMP();
	//void ZVR(); void TVR();
	//void ZCZ(); void TCF();
	//unsigned int BRK(); unsigned int WAI();
};

