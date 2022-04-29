#include "Operand.h"

const Operand rax{ rax_reg };
const Operand rcx{ rcx_reg };
const Operand rdx{ rdx_reg };
const Operand rbx{ rbx_reg };
const Operand rsp{ rsp_reg };
const Operand rbp{ rbp_reg };
const Operand rsi{ rsi_reg };
const Operand rdi{ rdi_reg };
const Operand r8 { r8_reg  };
const Operand r9 { r9_reg  };
const Operand r10{ r10_reg };
const Operand r11{ r11_reg };
const Operand r12{ r12_reg };
const Operand r13{ r13_reg };
const Operand r14{ r14_reg };
const Operand r15{ r15_reg };

const std::vector<Operand> register_operands = {
	rax, rcx, rdx, rbx,
	rsp, rbp, rsi, rdi,
	r8,  r9,  r10, r11,
	r12, r13, r14, r15
};
