#pragma once

#include <cstdint>

struct Register
{
	enum class RegisterName
	{
		RAX = 0b0000,
		RCX = 0b0001,
		RDX = 0b0010,
		RBX = 0b0011,
		RSP = 0b0100,
		RBP = 0b0101,
		RSI = 0b0110,
		RDI = 0b0111,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
	};

	constexpr Register(RegisterName name)
		: m_name(name)
	{
	}

	uint8_t index() const
	{
		return static_cast<uint8_t>(m_name);
	}

private:
	RegisterName m_name;
};

constexpr Register rax_reg{ Register::RegisterName::RAX };
constexpr Register rcx_reg{ Register::RegisterName::RCX };
constexpr Register rdx_reg{ Register::RegisterName::RDX };
constexpr Register rbx_reg{ Register::RegisterName::RBX };
constexpr Register rsp_reg{ Register::RegisterName::RSP };
constexpr Register rbp_reg{ Register::RegisterName::RBP };
constexpr Register rsi_reg{ Register::RegisterName::RSI };
constexpr Register rdi_reg{ Register::RegisterName::RDI };
constexpr Register  r8_reg{ Register::RegisterName::R8  };
constexpr Register  r9_reg{ Register::RegisterName::R9  };
constexpr Register r10_reg{ Register::RegisterName::R10 };
constexpr Register r11_reg{ Register::RegisterName::R11 };
constexpr Register r12_reg{ Register::RegisterName::R12 };
constexpr Register r13_reg{ Register::RegisterName::R13 };
constexpr Register r14_reg{ Register::RegisterName::R14 };
constexpr Register r15_reg{ Register::RegisterName::R15 };
