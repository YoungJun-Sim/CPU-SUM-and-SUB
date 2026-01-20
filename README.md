# CPU-SUM-and-SUB


CPU를 간단히 구현했습니다.

모델이 되는 시스템은 6502cpu 입니다.
olc6502 코드를 참고하여 작성하였습니다.



# 주소를 불러오는 3가지의 모드를 사용합니다.
---
주소가 필요 없는경우
IMP()
---
명령어 다음에 오는 값
IMM()
---
특정 주소의 값
ABS()
---






---

## 📜 Instruction Set (명령어 목록)

### 1. Data Transfer (데이터 이동)

| Opcode | Mnemonic | Mode | Cycles | Description |
| :---: | :---: | :---: | :---: | :--- |
| `0x01` | **LDA** | IMM | - | **Load A**: 상수 값을 A 레지스터에 로드합니다. (`A = Value`) |
| `0x02` | **LDA** | ABS | - | **Load A**: 메모리 값을 A 레지스터에 로드합니다. (`A = Mem[Addr]`) |
| `0x03` | **STA** | ABS | - | **Store A**: A 레지스터의 값을 메모리에 저장합니다. (`Mem[Addr] = A`) |

### 2. Arithmetic (산술 연산)

| Opcode | Mnemonic | Mode | Cycles | Description |
| :---: | :---: | :---: | :---: | :--- |
| `0x10` | **SUM** | IMM | - | **Add**: A 레지스터 값에 상수를 더합니다. (`A = A + Value`) |
| `0x11` | **SUM** | ABS | - | **Add**: A 레지스터 값에 메모리 값을 더합니다. (`A = A + Mem[Addr]`) |
| `0x12` | **SUB** | IMM | - | **Subtract**: A 레지스터 값에서 상수를 뺍니다. (`A = A - Value`) |
| `0x13` | **SUB** | ABS | - | **Subtract**: A 레지스터 값에서 메모리 값을 뺍니다. (`A = A - Mem[Addr]`) |



# 다음은 0부터 9 까지의 덧셈입니다.



	
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

---
# 출력 :
0
1
3
6
10
15
21
28
36
45
---

