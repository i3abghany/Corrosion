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
		RSI = 0b0100,
		RDI,
		RBP,
		RSP,
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
constexpr Register rbx_reg{ Register::RegisterName::RBX };
constexpr Register rcx_reg{ Register::RegisterName::RCX };
constexpr Register rdx_reg{ Register::RegisterName::RDX };